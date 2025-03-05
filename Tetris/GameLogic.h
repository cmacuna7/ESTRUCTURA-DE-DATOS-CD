/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:       Tetris                                                                  *
 * Autor:           Abner Arboleda                                                          *
 * Fecha de creacion: 01/12/2024                                                            *
 * Fecha de modificacion: 08/11/2024                                                        *
 * Materia:         Estructura de datos                                                     *
 * NRC :            1992                                                                    *
 ********************************************************************************************/
#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Board.h"

// Declara las funciones de la lógica del juego.
void processElimination(Board &b);
void applyGravity(Board &b);
void applyHorizontalCompression(Board &b);
void displayCentered(Board &board, int fallingX, int fallingY, int fallingValue);

#endif // GAMELOGIC_H
