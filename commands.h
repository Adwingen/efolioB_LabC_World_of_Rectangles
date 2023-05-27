/**
*
* LEI - UAB
*
* @classroom Laboratório de Programação (turma 3)
* @brief Atv 3  - world of rectangles
* @author Carlos Romão
* @module  commmands.h
* @date 06/05/2023
*
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dataStructure.h"


// function to create a rectangle on the plane
void createRectangle(RECTANGLE rectangles[], int* num_rectangles, int x, int y, int w, int h);

// function to validate the bottom line
int getBottom(RECTANGLE rectangles[], int num_rectangles);

// function to apply the effect of gravity
void applyGravity(RECTANGLE rectangles[], int num_rectangles);

// function to move to the left
void moveRectangleLeft(RECTANGLE rectangles[], int num_rectangles, int x, int y, int p);

// function to move to the right
void moveRectangleRight(RECTANGLE rectangles[], int num_rectangles, int x, int y, int p);







