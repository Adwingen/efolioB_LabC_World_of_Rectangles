/**
*
* LEI - UAB
*
* @classroom Laboratório de Programação (turma 3)
* @brief Atv 3  - world of rectangles
* @author Carlos Romão
* @module  controlPositions.c
* @date 06/05/2023
*
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "controlPositions.h"

// function to print the plane with rectangles
void printPlane(RECTANGLE rectangles[], int num_rectangles)
{
    char plane[ROWS][COLS];
    // initialize the plane array with blank spaces
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            plane[i][j] = ' ';
        }
    }

    // draw the rectangles on the plane
    for (int i = 0; i < num_rectangles; i++)
    {
        // draw the top and bottom sides of the rectangle
        for (int j = 0; j < rectangles[i].w; j++)
        {
            int y1 = ROWS - rectangles[i].y; // y-coordinate of the top side of the rectangle
            int y2 = ROWS - rectangles[i].y - rectangles[i].h + 1; // y-coordinate of the bottom side of the rectangle
            int x = rectangles[i].x + j - 1; // x-coordinate of the current position
            // check if the current position is within the plane
            if (y1 >= 0 && y1 < ROWS && x >= 0 && x < COLS)
            {
                plane[y1][x] = 'x'; // draw the top side of the rectangle
            }
            if (y2 >= 0 && y2 < ROWS && x >= 0 && x < COLS)
            {
                plane[y2][x] = 'x'; // draw the bottom side of the rectangle
            }
        }
        // draw the left and right sides of the rectangle
        for (int j = 0; j < rectangles[i].h; j++)
        {
            int y = ROWS - rectangles[i].y - j; // y-coordinate of the current position
            int x1 = rectangles[i].x - 1; // x-coordinate of the left side of the rectangle
            int x2 = rectangles[i].x + rectangles[i].w - 2; // x-coordinate of the right side of the rectangle
            // check if the current position is within the plane
            if (y >= 0 && y < ROWS && x1 >= 0 && x1 < COLS)
            {
                plane[y][x1] = 'x'; // draw the left side of the rectangle
            }
            if (y >= 0 && y < ROWS && x2 >= 0 && x2 < COLS)
            {
                plane[y][x2] = 'x'; // draw the right side of the rectangle
            }
        }
    }
    // print the plane
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%c", plane[i][j]);
        }
        printf("\n");
    }
}

// function to reset rectangles
void resetRectangles(RECTANGLE rectangles[], int* num_rectangles)
{
    *num_rectangles = 0;
}

// function to calculate the instability level
double calculateInstability(RECTANGLE rectangles[], int num_rectangles)
{
    double instability_sum = 0.0;
    int on_the_ground = 0; //track the number of rectangles on the ground
    int it_is_unstable = 0;

    for (int i = 1; i < num_rectangles; i++)
    {
        int unsupported_spaces = 0;
        int supported_spaces = rectangles[i].w;

        // Check if the rectangle is on the ground (no rectangles below it)
        if (rectangles[i].y == 1)
        {
            on_the_ground++;
            continue;
        }

        // Calculate the index adjustment based on the number of rectangles on the ground
        int index_adjustment = on_the_ground > 0 ? on_the_ground : 0;

        // Check if there is a rectangle directly below
        bool has_rectangle_below = false;
        for (int j = i - 1 - index_adjustment; j >= 0; j--)
        {
            if (rectangles[j].x <= rectangles[i].x &&
                rectangles[i].x + rectangles[i].w <= rectangles[j].x + rectangles[j].w &&
                rectangles[i].y - 1 == rectangles[j].y + rectangles[j].h)
            {
                has_rectangle_below = true;
                break;
            }
        }

        if (!has_rectangle_below && i >= 1 + index_adjustment)
        {
            unsupported_spaces = rectangles[i - 1 - index_adjustment].w - rectangles[i].x + rectangles[i - 1 - index_adjustment].x;
        }

        double instability_level = 0.0;
        if (supported_spaces + unsupported_spaces > 0)
        {
            instability_level = ((double)(supported_spaces - (unsupported_spaces)) / (supported_spaces)) * 100.0;
        }


        // Check instability level (greater than 50%)
        if (instability_level > 50.0)
        {
            instability_sum += instability_level;
            it_is_unstable++;
        }

    }

    return instability_sum / (it_is_unstable);
}

// function to read the coordinates
int readInteger()
{
    int value;
    while (scanf("%d", &value) != 1)
    {
        printf("Error: Invalid input. Please enter an integer.\n");
        while (getchar() != '\n') {} // Clear the input buffer
    }
    return value;
}


