/**
*
* LEI - UAB
*
* @classroom Laboratório de Programação (turma 3)
* @brief Atv 3  - world of rectangles
* @author Carlos Romão
* @module  main.c
* @date 06/05/2023
*
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include "controlPositions.h"


int main()
{
    RECTANGLE rectangles[MAX_RECTANGLES];
    int num_rectangles = 0;
    char command;
    int x, y, w, h, p;

    double instability_degree = 0.0;

    do
    {
        printf("Enter command (c to create, r to move right, l to move left, x to clear, q to quit): ");
        scanf(" %c", &command); 
        while (getchar() != '\n') {} // Clear the input buffer

        switch (command)
        {
        case 'c':
            printf("Enter coordinates and size (x y width height): ");
            x = readInteger();
            y = readInteger();
            w = readInteger();
            h = readInteger();
            createRectangle(rectangles, &num_rectangles, x, y, w, h);
            break;

        case 'r':
            printf("Enter coordinates and distance (x y distance): ");
            x = readInteger();
            y = readInteger();
            p = readInteger();
            moveRectangleRight(rectangles, num_rectangles, x, y, p);
            break;

        case 'l':
            printf("Enter coordinates and distance (x y distance): ");
            x = readInteger();
            y = readInteger();
            p = readInteger();
            moveRectangleLeft(rectangles, num_rectangles, x, y, p);
            break;

        case 'x':
            resetRectangles(rectangles, &num_rectangles);
            printf("Plane clear!\n");
            break;

        case 'q':
            printf("Goodbye!\n");
            break;

        default:
            printf("Invalid command.\n");
            break;
        }

        // Calculate instability degree
        instability_degree = calculateInstability(rectangles, num_rectangles);

        // Check if instability degree is greater than or equal to 70%
        if (instability_degree >= 70.0)
        {
            printf("Instability Alert! Instability level: %.1lf%%\n", instability_degree);
        }

        printPlane(rectangles, num_rectangles);

    } while (command != 'q');

    return 0;
}

