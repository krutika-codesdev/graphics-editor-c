#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 50
#define HEIGHT 35

void initializeScreen(char screen[HEIGHT][WIDTH]){
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            screen[y][x] = '.';
        }
    }
}

void drawHorizontalLine(char screen[HEIGHT][WIDTH], int y, int x1, int x2) {
    for (int x = x1; x <= x2; x++) {
        screen[y][x] = '_';
    }
}

void drawVerticalLine(char screen[HEIGHT][WIDTH], int x, int y1, int y2) {
    for (int y = y1; y <= y2; y++) {
        screen[y][x] = '|';
    }
}

void drawRectangle(char screen[HEIGHT][WIDTH], int x, int y, int width, int height) {
    int x2 = x + width - 1;
    int y2 = y + height - 1;

    // Draw left and right vertical borders
    drawVerticalLine(screen, x, y, y2);
    drawVerticalLine(screen, x2, y, y2);

    // Draw top and bottom horizontal borders
    drawHorizontalLine(screen, y, x, x2);
    drawHorizontalLine(screen, y2, x, x2);
}

void drawLine(char screen[HEIGHT][WIDTH],
              int x1, int y1,
              int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    
    if (steps == 0) {
        if (x1 >= 0 && x1 < WIDTH &&
            y1 >= 0 && y1 < HEIGHT) {
            screen[y1][x1] = '*';
        }
        return;
    }

    float x_inc = (float) dx / steps;
    float y_inc = (float) dy / steps;

    float x = x1;
    float y = y1;
    for (int i = 0; i <= steps; i++) {
        int plotX = (int)round(x);
        int plotY = (int)round(y);

        if (plotX >= 0 && plotX < WIDTH &&
            plotY >= 0 && plotY < HEIGHT) {
            screen[plotY][plotX] = '*';
        }

        x += x_inc;
        y += y_inc;
    }
}

void drawTriangle(char screen[HEIGHT][WIDTH],
                  int x1, int y1,
                  int x2, int y2,
                  int x3, int y3)
{
    drawLine(screen, x1, y1, x2, y2);
    drawLine(screen, x2, y2, x3, y3);
    drawLine(screen, x3, y3, x1, y1);
}

void displayScreen(char screen[HEIGHT][WIDTH]){
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", screen[y][x]);
        }
        printf("\n");
    }
}

int main() {
    char screen[HEIGHT][WIDTH];

    initializeScreen(screen);

    // Triangle test: arbitrary acute triangle
    drawTriangle(screen,
             25, 5,
             10, 25,
             40, 20);
    
    displayScreen(screen);

    printf("Canvas rendered successfully.\n");
    
    return 0;
}