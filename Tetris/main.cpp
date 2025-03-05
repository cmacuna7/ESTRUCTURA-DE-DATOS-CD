/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Archivo principal de proyecto                            *
 * Autor:                          Abner Arboleda                                           *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <cstdlib>  // para rand() si se desea extender más adelante
#include <ctime>
#include <sstream>

using namespace std;

const int blockSize = 30;
const int boardWidth = 10;
const int boardHeight = 20;

// Estructura DynamicBoard
struct DynamicBoard {
    int rows, cols;
    int **data;
    DynamicBoard(int r, int c) : rows(r), cols(c) {
        data = new int*[r];
        for (int i = 0; i < r; i++){
            data[i] = new int[c];
            for (int j = 0; j < c; j++){
                data[i][j] = -1;
            }
        }
    }
    ~DynamicBoard() {
        for (int i = 0; i < rows; i++){
            delete [] data[i];
        }
        delete [] data;
    }
};

int main() {
    srand(time(0));
    initwindow(boardWidth * blockSize, boardHeight * blockSize, "Tetris");
    // Reemplaza la creación de board con vectores por una instancia de DynamicBoard:
    DynamicBoard board(boardHeight, boardWidth);

    // Función para dibujar un bloque con número dentro
    auto drawNumberBlock = [&](int x, int y, int number) {
        setfillstyle(SOLID_FILL, RED); // fondo de bloque
        bar(x, y, x+blockSize, y+blockSize);
        setcolor(WHITE);
        rectangle(x, y, x+blockSize, y+blockSize);
        // Dibuja el dígito en el centro
        std::stringstream ss; ss << number;
        int textX = x + blockSize/3;
        int textY = y + blockSize/3;
        {
            std::string s = ss.str();
            outtextxy(textX, textY, &s[0]);
        }
    };

    // Función de eliminación de pares (horizontal y vertical)
    auto processElimination = [&](DynamicBoard &b) {
        bool changed;
        do {
            changed = false;
            for(int i = 0; i < boardHeight; i++){
                for(int j = 0; j < boardWidth; j++){
                    if(b.data[i][j] == -1) continue;
                    // Chequea derecha
                    if(j+1 < boardWidth && b.data[i][j] == b.data[i][j+1]){
                        b.data[i][j] = b.data[i][j+1] = -1;
                        changed = true;
                    }
                    // Chequea abajo
                    if(i+1 < boardHeight && b.data[i][j] == b.data[i+1][j]){
                        b.data[i][j] = b.data[i+1][j] = -1;
                        changed = true;
                    }
                }
            }
        } while(changed);
    };

    // MODIFICACIÓN: función applyGravity
    auto applyGravity = [&](DynamicBoard &b) {
        bool moved;
        do {
            moved = false;
            for (int j = 0; j < boardWidth; j++){
                for (int i = boardHeight - 2; i >= 0; i--){
                    if(b.data[i][j] != -1 && b.data[i+1][j] == -1){
                        swap(b.data[i][j], b.data[i+1][j]);
                        moved = true;
                    }
                }
            }
        } while(moved);
    };

    // MODIFICACIÓN: función applyHorizontalCompression
    auto applyHorizontalCompression = [&](DynamicBoard &b) {
        for (int i = 0; i < boardHeight; i++){
            int count = 0;
            for (int j = 0; j < boardWidth; j++){
                if(b.data[i][j] != -1)
                    count++;
            }
            // Si solo hay un número en la fila, no comprimir horizontalmente.
            if(count <= 1) continue;
            for (int j = 1; j < boardWidth; j++){
                int k = j;
                while(k > 0 && b.data[i][k] != -1 && b.data[i][k-1] == -1){
                    swap(b.data[i][k], b.data[i][k-1]);
                    k--;
                }
            }
        }
    };

    // Variables para el "número" que cae
    int fallingValue = rand() % 10;
    int fallingX = boardWidth / 2; // posición inicial (columna)
    int fallingY = 0;            // fila inicial

    // Variables para tiempo y doble buffering
    unsigned long lastFall = clock();
    const int fallInterval = 500; // milisegundos
    int page = 0;

    // Bucle principal del juego (modificado para números)
    while (true) {
        // Proceso de entrada
        if(kbhit()){
            int key = getch();
            if(key == 27) break; // ESC para salir
            // Si se ingresa un dígito, se actualiza fallingValue
            if(key >= '0' && key <= '9'){
                fallingValue = key - '0';
            } else if(key == 'a' || key == 'A'){
                if(fallingX > 0 && board.data[fallingY][fallingX-1] == -1)
                    fallingX--;
            } else if(key == 'd' || key == 'D'){
                if(fallingX < boardWidth-1 && board.data[fallingY][fallingX+1] == -1)
                    fallingX++;
            } else if(key == 's' || key == 'S'){
                // Forzar caída
                if(fallingY < boardHeight-1 && board.data[fallingY+1][fallingX] == -1)
                    fallingY++;
            }
        }

        // Control de la caída automática
        unsigned long current = clock();
        if(((current - lastFall) * 1000 / CLOCKS_PER_SEC) >= fallInterval) {
            if(fallingY < boardHeight-1 && board.data[fallingY+1][fallingX] == -1) {
                fallingY++;
            } else {
                // Coloca el número en board
                board.data[fallingY][fallingX] = fallingValue;
                // Procesa eliminación y efectos de gravedad y compresión
                processElimination(board);
                applyGravity(board);
                applyHorizontalCompression(board);
                // Genera nuevo número
                fallingValue = rand() % 10;
                fallingX = boardWidth / 2;
                fallingY = 0;
                // Si ya no hay espacio, termina el juego
                if(board.data[fallingY][fallingX] != -1) break;
            }
            lastFall = current;
        }

        // Doble buffering: dibuja en página activa (off-screen)
        setactivepage(page);
        cleardevice();
        // Dibuja fondo negro
        setfillstyle(SOLID_FILL, BLACK);
        bar(0, 0, boardWidth*blockSize, boardHeight*blockSize);
        
        // Dibuja cuadrícula (líneas entrecortadas)
        setcolor(LIGHTGRAY);
        setlinestyle(DASHED_LINE, 0, 1);
        for(int i = 0; i <= boardWidth; i++){
            line(i*blockSize, 0, i*blockSize, boardHeight*blockSize);
        }
        for(int i = 0; i <= boardHeight; i++){
            line(0, i*blockSize, boardWidth*blockSize, i*blockSize);
        }
        setlinestyle(SOLID_LINE, 0, 1);
        setcolor(WHITE);
        
        // Dibuja los números ya colocados en el tablero
        for(int i = 0; i < boardHeight; i++){
            for(int j = 0; j < boardWidth; j++){
                if(board.data[i][j] != -1)
                    drawNumberBlock(j * blockSize, i * blockSize, board.data[i][j]);
            }
        }
        // Dibuja el número que cae
        drawNumberBlock(fallingX * blockSize, fallingY * blockSize, fallingValue);

        setvisualpage(page);
        delay(50);
        page = 1 - page;
    }
    
    getch();
    closegraph();
    return 0;
}
