#include <stdio.h>

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

    drawRectangle(screen, 10, 5, 16, 11);

    displayScreen(screen);

    printf("Rectangle rendered successfully.\n");
    
    return 0;
}