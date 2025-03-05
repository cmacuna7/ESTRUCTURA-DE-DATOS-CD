/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:       Versión en consola del juego (números cayendo y eliminándose)          *
 * Autor:           Abner Arboleda                                                        *
 * Fecha de creacion: 01/12/2024                                                      *
 * Fecha de modificacion: 08/11/2024                                                  *
 * Materia:         Estructura de datos                                                   *
 * NRC :            1992                                                                  *
 ********************************************************************************************/
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "Board.cpp"
#include "GameLogic.cpp"

using namespace std;

int main() {
    srand(time(0));
    system("mode con: cols=120 lines=40");
    
    Board board(boardHeight, boardWidth);
    
    int fallingValue = rand() % 10;
    int fallingX = boardWidth / 2;
    int fallingY = 0;
    
    unsigned long lastFall = clock();
    const int fallInterval = 500;
    
    while (true) {
        if(kbhit()){
            int key = getch();
            if(key == 27) break;
            if(key >= '0' && key <= '9'){
                fallingValue = key - '0';
            } else if(key == 'a' || key == 'A'){
                if(fallingX > 0 && board.cell(fallingY, fallingX-1) == -1)
                    fallingX--;
            } else if(key == 'd' || key == 'D'){
                if(fallingX < boardWidth-1 && board.cell(fallingY, fallingX+1) == -1)
                    fallingX++;
            } else if(key == 's' || key == 'S'){
                if(fallingY < boardHeight-1 && board.cell(fallingY+1, fallingX) == -1)
                    fallingY++;
            }
        }
        
        // Verificación inmediata si vecinos son iguales:
        if(board.cell(fallingY, fallingX) == -1) {
            bool immediateElim = false;
            if(fallingX > 0 && board.cell(fallingY, fallingX-1) == fallingValue){ board.cell(fallingY, fallingX-1) = -1; immediateElim = true; }
            if(fallingX < boardWidth-1 && board.cell(fallingY, fallingX+1) == fallingValue){ board.cell(fallingY, fallingX+1) = -1; immediateElim = true; }
            if(fallingY > 0 && board.cell(fallingY-1, fallingX) == fallingValue){ board.cell(fallingY-1, fallingX) = -1; immediateElim = true; }
            if(fallingY < boardHeight-1 && board.cell(fallingY+1, fallingX) == fallingValue){ board.cell(fallingY+1, fallingX) = -1; immediateElim = true; }
            if(immediateElim) {
                fallingValue = rand() % 10;
                fallingX = boardWidth / 2;
                fallingY = 0;
                processElimination(board);
                applyGravity(board);
                applyHorizontalCompression(board);
                lastFall = clock();
                continue;
            }
        }
        
        unsigned long current = clock();
        if(((current - lastFall) * 1000 / CLOCKS_PER_SEC) >= fallInterval) {
            if(fallingY < boardHeight-1 && board.cell(fallingY+1, fallingX) == -1) {
                fallingY++;
            } else {
                board.cell(fallingY, fallingX) = fallingValue;
                processElimination(board);
                applyGravity(board);
                applyHorizontalCompression(board);
                fallingValue = rand() % 10;
                fallingX = boardWidth / 2;
                fallingY = 0;
                if(board.cell(fallingY, fallingX) != -1) break;
            }
            lastFall = current;
        }
        
        processElimination(board);
        applyGravity(board);
        applyHorizontalCompression(board);
        
        displayCentered(board, fallingX, fallingY, fallingValue);
        Sleep(50);
    }
    
    cout << "\nGame Over!" << endl;
    return 0;
}
