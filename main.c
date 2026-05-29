#include <stdio.h>

#define WIDTH 50
#define HEIGHT 35

void initializeScreen(char screen[HEIGHT][WIDTH]){
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            screen[y][x] = '.';
        }
    }
    screen[0][0] = 'A';
    screen[17][25] = 'B';
    screen[34][49] = 'C';
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
    displayScreen(screen);

    printf("screen initialized and displayed successfully.\n");
    
    return 0;
}