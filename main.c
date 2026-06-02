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

    drawHorizontalLine(screen, 5, 10, 40);
    drawVerticalLine(screen, 25, 10, 30);

    displayScreen(screen);

    printf("Canvas rendered successfully.\n");
    
    return 0;
}