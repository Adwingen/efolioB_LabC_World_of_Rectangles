/**
*
* LEI - UAB
*
* @classroom Laboratório de Programação (turma 3)
* @brief Atv 3  - world of rectangles
* @author Carlos Romão
* @module  commands.c
* @date 06/05/2023
*
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "commands.h"

// function to create a rectangle on the plane
void createRectangle(RECTANGLE rectangles[], int* num_rectangles, int x, int y, int w, int h)
{
    
    if (*num_rectangles >= MAX_RECTANGLES)
    {
        printf("Error: maximum number of rectangles reached.\n");
        return;
    }
    // validate bounds
    if (x < 1 || x + w - 1 > COLS || y < 1 || y + h - 1 > ROWS)
    {
        printf("Error: rectangle is out of bounds.\n");
        return;
    }

    int y_min = 1;
    // validate intersection
    for (int i = 0; i < *num_rectangles; i++)
    {
        if (x < rectangles[i].x + rectangles[i].w
            && x + w > rectangles[i].x
            && y < rectangles[i].y + rectangles[i].h
            && y + h > rectangles[i].y)
        {
            printf("Error: rectangles intersect.\n");
            return;
        }
        if (rectangles[i].x < x + w
            && rectangles[i].x + rectangles[i].w > x
            && rectangles[i].y + rectangles[i].h >= y
            && rectangles[i].y + rectangles[i].h <= y + h)
        {
            y_min = rectangles[i].y + rectangles[i].h;
        }
    }


    // validates the "fall"
    while (y > y_min)
    {
        int can_move_down = 1;

        for (int i = 0; i < *num_rectangles; i++)
        {
            if (x < rectangles[i].x + rectangles[i].w && x + w > rectangles[i].x &&
                y - 1 < rectangles[i].y + rectangles[i].h && y - 1 + h > rectangles[i].y)
            {
                can_move_down = 0;
                break;
            }
        }
        if (can_move_down)
        {
            y--;
        }
        else
        {
            break;
        }
    }
    rectangles[*num_rectangles].x = x;
    rectangles[*num_rectangles].y = y;
    rectangles[*num_rectangles].w = w;
    rectangles[*num_rectangles].h = h;
    (*num_rectangles)++;
}

// function to validate the bottom line
int getBottom(RECTANGLE rectangles[], int num_rectangles)
{
    int bottom = ROWS;
    for (int i = 0; i < num_rectangles; i++)
    {
        int rect_bottom = rectangles[i].y;

        if (rect_bottom < bottom)
        {
            bottom = rect_bottom;
        }
    }

    return bottom;
}

// function to apply the effect of gravity
void applyGravity(RECTANGLE rectangles[], int num_rectangles)
{
    int bottom = getBottom(rectangles, num_rectangles);

    for (int i = 0; i < num_rectangles; i++)
    {
        int can_move = 1;
        while (can_move && rectangles[i].y > bottom)
        {
            for (int j = 0; j < num_rectangles; j++)
            {
                if (i == j)
                {
                    continue;
                }
                if (rectangles[i].x < rectangles[j].x + rectangles[j].w &&
                    rectangles[i].x + rectangles[i].w > rectangles[j].x &&
                    rectangles[i].y - 1 < rectangles[j].y + rectangles[j].h &&
                    rectangles[i].y - 1 + rectangles[i].h > rectangles[j].y)
                {
                    can_move = 0;
                    break;
                }
            }
            if (can_move)
            {
                rectangles[i].y--;
            }
        }
    }
}

// function to move to the left
void moveRectangleLeft(RECTANGLE rectangles[], int num_rectangles, int x, int y, int p)
{
    // Find the rectangle that contains the point(x, y)
    int index = -1;
    for (int i = 0; i < num_rectangles; i++)
    {
        if (x >= rectangles[i].x && x < rectangles[i].x + rectangles[i].w &&
            y >= rectangles[i].y && y < rectangles[i].y + rectangles[i].h)
        {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("No rectangle found at (%d, %d)\n", x, y);
        return;
    }

    // Calculate the new x-coordinate of the moved rectangle
    int new_x = rectangles[index].x - p;

    // Check if the new x-coordinate is valid
    if (new_x < 1) {
        printf("Rectangle cannot be moved outside the plane\n");
        return;
    }

    // Apply gravity to all rectangles
    applyGravity(rectangles, num_rectangles);

    // Check if the moved rectangle can move down without overlapping any other rectangles
    int new_y = rectangles[index].y;
    while (new_y > 1)
    {
        int can_move_down = 1;
        for (int i = 0; i < num_rectangles; i++)
        {
            if (i == index)
            {
                continue;
            }
            if (new_x < rectangles[i].x + rectangles[i].w
                && new_x + rectangles[index].w > rectangles[i].x
                && new_y - 1 < rectangles[i].y + rectangles[i].h
                && new_y - 1 + rectangles[index].h > rectangles[i].y)
            {
                can_move_down = 0;
                break;
            }
        }
        if (can_move_down)
        {
            new_y--;
        }
        else
        {
            break;
        }
    }

    // Apply the new position to the rectangle
    rectangles[index].x = new_x;
    rectangles[index].y = new_y;

    // Apply gravity to all rectangles again
    applyGravity(rectangles, num_rectangles);
}

// function to move to the right
void moveRectangleRight(RECTANGLE rectangles[], int num_rectangles, int x, int y, int p)
{
    // Find the rectangle that contains the point(x, y)
    int index = -1;
    for (int i = 0; i < num_rectangles; i++)
    {
        if (x >= rectangles[i].x
            && x < rectangles[i].x + rectangles[i].w
            && y >= rectangles[i].y && y < rectangles[i].y + rectangles[i].h)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("No rectangle found at (%d, %d)\n", x, y);
        return;
    }

    // Calculate the new x-coordinate of the moved rectangle
    int new_x = rectangles[index].x + p;

    // Check if the new x-coordinate is valid
    if (new_x + rectangles[index].w - 1 > COLS)
    {
        printf("Rectangle cannot be moved outside the plane\n");
        return;
    }

    // Apply gravity to all rectangles
    applyGravity(rectangles, num_rectangles);

    // Check if the moved rectangle can move down without overlapping any other rectangles
    int new_y = rectangles[index].y;
    while (new_y > 1)
    {
        int can_move_down = 1;
        for (int i = 0; i < num_rectangles; i++)
        {
            if (i == index)
            {
                continue;
            }
            if (new_x < rectangles[i].x + rectangles[i].w
                && new_x + rectangles[index].w > rectangles[i].x
                && new_y - 1 < rectangles[i].y + rectangles[i].h
                && new_y - 1 + rectangles[index].h > rectangles[i].y)
            {
                can_move_down = 0;
                break;
            }
        }
        if (can_move_down)
        {
            new_y--;
        }
        else 
        {
            break;
        }
    }

    // Apply the new position to the rectangle
    rectangles[index].x = new_x;
    rectangles[index].y = new_y;

    // Apply gravity to all rectangles again
    applyGravity(rectangles, num_rectangles);
}






















