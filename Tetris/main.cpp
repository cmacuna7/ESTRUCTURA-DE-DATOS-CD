#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <cstdlib>  // para rand() si se desea extender más adelante
#include <ctime>

using namespace std;

const int blockSize = 30;
const int boardWidth = 10;
const int boardHeight = 20;

// Añadimos lista de piezas de Tetris
vector<vector<vector<int>>> pieces = {
    // T
    {
        {0,1,0},
        {1,1,1}
    },
    // I
    {
        {1,1,1,1}
    },
    // O
    {
        {1,1},
        {1,1}
    },
    // L
    {
        {1,0},
        {1,0},
        {1,1}
    },
    // J
    {
        {0,1},
        {0,1},
        {1,1}
    },
    // S
    {
        {0,1,1},
        {1,1,0}
    },
    // Z
    {
        {1,1,0},
        {0,1,1}
    }
};

void drawBlock(int x, int y, int color) {
    setfillstyle(SOLID_FILL, color);
    bar(x, y, x + blockSize, y + blockSize);
    setcolor(WHITE);
    rectangle(x, y, x + blockSize, y + blockSize);
}

// Función para verificar si la pieza se puede mover a (newX, newY)
bool canMove(int newX, int newY, const vector<vector<int>> &tetromino, const vector<vector<int>> &board) {
    for (int i = 0; i < tetromino.size(); i++) {
        for (int j = 0; j < tetromino[i].size(); j++) {
            if (tetromino[i][j]) {
                int posX = newX + j;
                int posY = newY + i;
                if (posX < 0 || posX >= board[0].size() || posY >= board.size())
                    return false;
                if(board[posY][posX] != 0)
                    return false;
            }
        }
    }
    return true;
}

// Función para eliminar líneas completas
void clearLines(vector<vector<int>> &board) {
    for (int y = board.size()-1; y >= 0; y--) {
        bool full = true;
        for (int x = 0; x < board[0].size(); x++) {
            if(board[y][x] == 0) {
                full = false;
                break;
            }
        }
        if(full) {
            board.erase(board.begin() + y);
            board.insert(board.begin(), vector<int>(board[0].size(), 0));
            // Vuelve a analizar la misma fila tras bajar
            y++;
        }
    }
}

int main() {
    srand(time(0)); // Inicializa semilla para números aleatorios
    // Inicializa la ventana gráfica
    initwindow(boardWidth * blockSize, boardHeight * blockSize, "Tetris");

    // Inicializa el tablero (sin uso completo en este ejemplo)
    vector<vector<int>> board(boardHeight, vector<int>(boardWidth, 0));

    // Modificamos newPiece para elegir piezas de la lista
    auto newPiece = [&]() -> vector<vector<int>> {
        return pieces[rand() % pieces.size()];
    };

    vector<vector<int>> tetromino = newPiece();
    int tetroX = boardWidth / 2 - 1;
    int tetroY = 0;

    // Lambda para rotar el tetromino (rotación 90°)
    auto rotate = [&tetromino, &board, &tetroX, &tetroY]() {
        vector<vector<int>> rotated(tetromino[0].size(), vector<int>(tetromino.size(), 0));
        for (int i = 0; i < tetromino.size(); i++) {
            for (int j = 0; j < tetromino[0].size(); j++) {
                rotated[j][tetromino.size() - 1 - i] = tetromino[i][j];
            }
        }
        // Solo rota si no causa colisión
        if(canMove(tetroX, tetroY, rotated, board))
            tetromino = rotated;
    };

    // Variables para control de tiempo y doble buffering
    unsigned long lastFall = clock();
    const int fallInterval = 500; // milisegundos
    int page = 0;  // para doble buffering

    // Bucle principal del juego (fluido con doble buffering)
    while (true) {

        // Procesa entrada del usuario
        if (kbhit()){
            int key = getch();
            if(key == 27) { // ESC para salir
                break;
            }
            if(key == 'a' || key == 'A') {
                if(canMove(tetroX - 1, tetroY, tetromino, board))
                    tetroX--;
            } else if(key == 'd' || key == 'D') {
                if(canMove(tetroX + 1, tetroY, tetromino, board))
                    tetroX++;
            } else if(key == 'w' || key == 'W') {
                rotate();
            } else if(key == 's' || key == 'S') {
                if(canMove(tetroX, tetroY + 1, tetromino, board))
                    tetroY++;
            }
        }

        // Controla la caída automática según el tiempo transcurrido
        unsigned long current = clock();
        if(((current - lastFall) * 1000 / CLOCKS_PER_SEC) >= fallInterval) {
            if(canMove(tetroX, tetroY + 1, tetromino, board)) {
                tetroY++;
            } else {
                for (int i = 0; i < tetromino.size(); i++) {
                    for (int j = 0; j < tetromino[i].size(); j++) {
                        if(tetromino[i][j]) {
                            board[tetroY + i][tetroX + j] = RED;
                        }
                    }
                }
                clearLines(board);
                tetromino = newPiece();
                tetroX = boardWidth / 2 - 1;
                tetroY = 0;
                if(!canMove(tetroX, tetroY, tetromino, board)) {
                    break;
                }
            }
            lastFall = current;
        }

        // Empieza a dibujar en la página activa (off-screen)
        setactivepage(page);
        cleardevice(); // Limpia esta página

        // Dibuja fondo negro y el tablero (piezas congeladas)
        setfillstyle(SOLID_FILL, BLACK);
        bar(0, 0, boardWidth * blockSize, boardHeight * blockSize);
        for (int y = 0; y < board.size(); y++) {
            for (int x = 0; x < board[0].size(); x++) {
                if(board[y][x] != 0) {
                    drawBlock(x * blockSize, y * blockSize, board[y][x]);
                }
            }
        }
        // Dibuja el tetromino activo
        for (int i = 0; i < tetromino.size(); i++) {
            for (int j = 0; j < tetromino[i].size(); j++) {
                if (tetromino[i][j]) {
                    drawBlock((tetroX + j) * blockSize, (tetroY + i) * blockSize, RED);
                }
            }
        }

        // Muestra la página ya dibujada
        setvisualpage(page);
        delay(50);  // Pequeña espera para fluidez
        page = 1 - page; // Alterna la página para el siguiente frame
    }

    getch();
    closegraph();
    return 0;
}
