/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:       Tetris                                                                  *
 * Autor:           Abner Arboleda                                                          *
 * Fecha de creacion: 01/12/2024                                                            *
 * Fecha de modificacion: 08/11/2024                                                        *
 * Materia:         Estructura de datos                                                     *
 * NRC :            1992                                                                    *
 ********************************************************************************************/
#include "GameLogic.h"
#include <iostream>
#include <windows.h>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;

void processElimination(Board &b) {
    bool changed = false;
    int rows = b.getRows(), cols = b.getCols();
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            int val = b.cell(i,j);
            if(val == -1) continue;
            // Eliminación horizontal: 
            if(j+1 < cols && b.cell(i,j+1) == val) {
                bool leftOK = (j-1 < 0) || (b.cell(i,j-1) != val);
                bool rightOK = (j+2 >= cols) || (b.cell(i,j+2) != val);
                if(leftOK && rightOK) {
                    b.cell(i,j) = b.cell(i,j+1) = -1;
                    changed = true;
                }
            }
            // Eliminación vertical:
            if(i+1 < rows && b.cell(i+1,j) == val) {
                bool aboveOK = (i-1 < 0) || (b.cell(i-1,j) != val);
                bool belowOK = (i+2 >= rows) || (b.cell(i+2,j) != val);
                if(aboveOK && belowOK) {
                    b.cell(i,j) = b.cell(i+1,j) = -1;
                    changed = true;
                }
            }
        }
    }
    if(changed)
        processElimination(b); // repetir para encontrar nuevas eliminaciones
}

void applyGravity(Board &b) {
    int rows = b.getRows(), cols = b.getCols();
    bool moved;
    do {
        moved = false;
        for (int i = rows - 1; i > 0; i--) {
            for (int j = 0; j < cols; j++) {
                if(b.cell(i, j) == -1) {
                    // Primero, intenta bajar la celda directamente arriba.
                    if(b.cell(i-1, j) != -1) {
                        b.cell(i, j) = b.cell(i-1, j);
                        b.cell(i-1, j) = -1;
                        moved = true;
                    }
                    // Si no pudo bajar de la misma columna, intenta la diagonal izquierda.
                    else if(j > 0 && b.cell(i-1, j-1) != -1) {
                        b.cell(i, j) = b.cell(i-1, j-1);
                        b.cell(i-1, j-1) = -1;
                        moved = true;
                    }
                    // No se usa la diagonal derecha.
                }
            }
        }
    } while(moved);
}

void applyHorizontalCompression(Board &b) {
    int rows = b.getRows(), cols = b.getCols();
    for (int i = 0; i < rows; i++){
        int count = 0;
        for (int j = 0; j < cols; j++){
            if(b.cell(i,j) != -1)
                count++;
        }
        if(count <= 1) continue;
        for (int j = 1; j < cols; j++){
            int k = j;
            while(k > 0 && b.cell(i,k) != -1 && b.cell(i,k-1) == -1){
                swap(b.cell(i,k), b.cell(i,k-1));
                k--;
            }
        }
    }
}

void displayCentered(Board &board, int fallingX, int fallingY, int fallingValue) {
    int rows = board.getRows();
    int cols = board.getCols();
    int gameWidth = cols * 3 + 2;
    int gameHeight = rows + 2;
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    
    int leftMargin = (consoleWidth - gameWidth) / 2;
    int topMargin = (consoleHeight - gameHeight) / 2;
    
    string border = "+";
    for (int j = 0; j < cols; j++){
        border += "---";
    }
    border += "+";
    string boardLines[gameHeight];
    boardLines[0] = border;
    for (int i = 0; i < rows; i++){
        string line = "|";
        for (int j = 0; j < cols; j++){
            int val = board.cell(i,j);
            if(i == fallingY && j == fallingX && val == -1)
                val = fallingValue;
            if(val == -1)
                line += "   ";
            else
                line += " " + to_string(val) + " ";
        }
        line += "|";
        boardLines[i+1] = line;
    }
    boardLines[gameHeight-1] = border;
    
    system("cls");
    for (int i = 0; i < topMargin; i++){
        cout << "\n";
    }
    for (int i = 0; i < gameHeight; i++){
        cout << string(leftMargin, ' ') << boardLines[i] << "\n";
    }
}
