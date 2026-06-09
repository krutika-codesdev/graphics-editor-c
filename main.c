#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 50
#define HEIGHT 35
#define MAX_SHAPES 50

typedef struct {
    int id;
    char type; // 'L' = Line, 'R' = Rectangle, 'T' = Triangle, 'C' = Circle
    int x1, y1;
    int x2, y2;
    int x3, y3;
    int active;
} Shape;

Shape scene[MAX_SHAPES];
int scene_count = 0;
int next_id = 1;

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

void plotCirclePoints(char screen[HEIGHT][WIDTH], int xc, int yc, int x, int y) {
    int px[8] = { xc + x, xc - x, xc + x, xc - x, xc + y, xc - y, xc + y, xc - y };
    int py[8] = { yc + y, yc + y, yc - y, yc - y, yc + x, yc + x, yc - x, yc - x };

    for (int i = 0; i < 8; i++) {
        if (px[i] >= 0 && px[i] < WIDTH && py[i] >= 0 && py[i] < HEIGHT) {
            screen[py[i]][px[i]] = '*';
        }
    }
}

void drawCircle(char screen[HEIGHT][WIDTH], int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    plotCirclePoints(screen, xc, yc, x, y);

    while (x < y) {
        x++;
        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        plotCirclePoints(screen, xc, yc, x, y);
    }
}

void addShape(char type, int x1, int y1, int x2, int y2, int x3, int y3) {
    if (scene_count < MAX_SHAPES) {
        scene[scene_count].id = next_id++;
        scene[scene_count].type = type;
        scene[scene_count].x1 = x1;
        scene[scene_count].y1 = y1;
        scene[scene_count].x2 = x2;
        scene[scene_count].y2 = y2;
        scene[scene_count].x3 = x3;
        scene[scene_count].y3 = y3;
        scene[scene_count].active = 1;
        scene_count++;
    }
}

void deleteShape(int id) {
    for (int i = 0; i < scene_count; i++) {
        if (scene[i].id == id) {
            scene[i].active = 0;
            break;
        }
    }
}

void modifyShape(int id, int x1, int y1, int x2, int y2, int x3, int y3) {
    for (int i = 0; i < scene_count; i++) {
        if (scene[i].id == id && scene[i].active) {
            scene[i].x1 = x1;
            scene[i].y1 = y1;
            scene[i].x2 = x2;
            scene[i].y2 = y2;
            scene[i].x3 = x3;
            scene[i].y3 = y3;
            break;
        }
    }
}

void renderScene(char screen[HEIGHT][WIDTH]) {
    initializeScreen(screen);
    for (int i = 0; i < scene_count; i++) {
        if (scene[i].active) {
            if (scene[i].type == 'L') {
                drawLine(screen, scene[i].x1, scene[i].y1, scene[i].x2, scene[i].y2);
            } else if (scene[i].type == 'R') {
                drawRectangle(screen, scene[i].x1, scene[i].y1, scene[i].x2, scene[i].y2);
            } else if (scene[i].type == 'T') {
                drawTriangle(screen, scene[i].x1, scene[i].y1, scene[i].x2, scene[i].y2, scene[i].x3, scene[i].y3);
            } else if (scene[i].type == 'C') {
                drawCircle(screen, scene[i].x1, scene[i].y1, scene[i].x2);
            }
        }
    }
}

void listShapes() {
    printf("\n=== Active Shapes ===\n");
    int active_found = 0;
    for (int i = 0; i < scene_count; i++) {
        if (scene[i].active) {
            active_found = 1;
            printf("ID %d: ", scene[i].id);
            if (scene[i].type == 'L') {
                printf("Line from (%d, %d) to (%d, %d)\n", scene[i].x1, scene[i].y1, scene[i].x2, scene[i].y2);
            } else if (scene[i].type == 'R') {
                printf("Rectangle at (%d, %d) size %dx%d\n", scene[i].x1, scene[i].y1, scene[i].x2, scene[i].y2);
            } else if (scene[i].type == 'T') {
                printf("Triangle at (%d, %d), (%d, %d), (%d, %d)\n", scene[i].x1, scene[i].y1, scene[i].x2, scene[i].y2, scene[i].x3, scene[i].y3);
            } else if (scene[i].type == 'C') {
                printf("Circle at (%d, %d) radius %d\n", scene[i].x1, scene[i].y1, scene[i].x2);
            }
        }
    }
    if (!active_found) {
        printf("No active shapes.\n");
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
    int choice;

    initializeScreen(screen);

    while (1) {
        printf("\n--- Terminal Graphics Editor Menu ---\n");
        printf("1. Add a Shape\n");
        printf("2. List Shapes\n");
        printf("3. Delete Shape by ID\n");
        printf("4. Modify Shape by ID\n");
        printf("5. Render and Display Canvas\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // clear bad input
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        if (choice == 1) {
            char type;
            printf("Enter shape type (L = Line, R = Rectangle, T = Triangle, C = Circle): ");
            scanf(" %c", &type);
            if (type == 'L' || type == 'l') {
                int x1, y1, x2, y2;
                printf("Enter x1 y1 x2 y2: ");
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                addShape('L', x1, y1, x2, y2, 0, 0);
            } else if (type == 'R' || type == 'r') {
                int x, y, w, h;
                printf("Enter top-left x, y and width, height: ");
                scanf("%d %d %d %d", &x, &y, &w, &h);
                addShape('R', x, y, w, h, 0, 0);
            } else if (type == 'T' || type == 't') {
                int x1, y1, x2, y2, x3, y3;
                printf("Enter x1 y1 x2 y2 x3 y3: ");
                scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
                addShape('T', x1, y1, x2, y2, x3, y3);
            } else if (type == 'C' || type == 'c') {
                int xc, yc, r;
                printf("Enter center x, y and radius: ");
                scanf("%d %d %d", &xc, &yc, &r);
                addShape('C', xc, yc, r, 0, 0, 0);
            } else {
                printf("Unknown shape type.\n");
            }
        } else if (choice == 2) {
            listShapes();
        } else if (choice == 3) {
            int id;
            listShapes();
            printf("Enter Shape ID to delete: ");
            scanf("%d", &id);
            deleteShape(id);
            printf("Shape ID %d marked as deleted.\n", id);
        } else if (choice == 4) {
            int id;
            listShapes();
            printf("Enter Shape ID to modify: ");
            scanf("%d", &id);
            int found = -1;
            for (int i = 0; i < scene_count; i++) {
                if (scene[i].id == id && scene[i].active) {
                    found = i;
                    break;
                }
            }
            if (found == -1) {
                printf("Shape ID %d not found or inactive.\n", id);
            } else {
                char type = scene[found].type;
                if (type == 'L') {
                    int x1, y1, x2, y2;
                    printf("Current: Line from (%d, %d) to (%d, %d)\n", scene[found].x1, scene[found].y1, scene[found].x2, scene[found].y2);
                    printf("Enter new x1 y1 x2 y2: ");
                    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                    modifyShape(id, x1, y1, x2, y2, 0, 0);
                } else if (type == 'R') {
                    int x, y, w, h;
                    printf("Current: Rectangle at (%d, %d) size %dx%d\n", scene[found].x1, scene[found].y1, scene[found].x2, scene[found].y2);
                    printf("Enter new top-left x, y and width, height: ");
                    scanf("%d %d %d %d", &x, &y, &w, &h);
                    modifyShape(id, x, y, w, h, 0, 0);
                } else if (type == 'T') {
                    int x1, y1, x2, y2, x3, y3;
                    printf("Current: Triangle at (%d, %d), (%d, %d), (%d, %d)\n", scene[found].x1, scene[found].y1, scene[found].x2, scene[found].y2, scene[found].x3, scene[found].y3);
                    printf("Enter new x1 y1 x2 y2 x3 y3: ");
                    scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
                    modifyShape(id, x1, y1, x2, y2, x3, y3);
                } else if (type == 'C') {
                    int xc, yc, r;
                    printf("Current: Circle at (%d, %d) radius %d\n", scene[found].x1, scene[found].y1, scene[found].x2);
                    printf("Enter new center x, y and radius: ");
                    scanf("%d %d %d", &xc, &yc, &r);
                    modifyShape(id, xc, yc, r, 0, 0, 0);
                }
                printf("Shape ID %d updated.\n", id);
            }
        } else if (choice == 5) {
            renderScene(screen);
            displayScreen(screen);
        } else if (choice == 6) {
            printf("Exiting Graphics Editor.\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}