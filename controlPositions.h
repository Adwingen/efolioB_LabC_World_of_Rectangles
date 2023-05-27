/**
*
* LEI - UAB
*
* @classroom Laboratório de Programação (turma 3)
* @brief Atv 3  - world of rectangles
* @author Carlos Romão
* @module  controlPositions.h
* @date 06/05/2023
*
*/

#include "commands.h"

// function to print the plane with rectangles
void printPlane(RECTANGLE rectangles[], int num_rectangles);

// function to reset rectangles
void resetRectangles(RECTANGLE rectangles[], int* num_rectangles);

// function to calculate the instability level
double calculateInstability(RECTANGLE rectangles[], int num_rectangles);

// function to read the coordinates
int readInteger();