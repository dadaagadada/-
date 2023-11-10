#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define WIDTH 50
#define HEIGHT 25

void initLife(int life[WIDTH][HEIGHT]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            life[x][y] = 0;
        }
    }
}

void randomizeLife(int life[WIDTH][HEIGHT], int density) {
    srand(time(NULL));
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            life[x][y] = (rand() % 100 < density) ? 1 : 0;
        }
    }
}

void updateLife(int life[WIDTH][HEIGHT]) {
    int nextLife[WIDTH][HEIGHT];
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int neighbors = 0;

            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (dx != 0 || dy != 0) {
                        int nx = (x + dx + WIDTH) % WIDTH;
                        int ny = (y + dy + HEIGHT) % HEIGHT;
                        neighbors += life[nx][ny];
                    }
                }
            }

            if (life[x][y]) {
                if (neighbors < 2 || neighbors > 3) {
                    nextLife[x][y] = 0; // клетка умирает
                }
                else {
                    nextLife[x][y] = 1; // выжившие клетки
                }
            }
            else {
                if (neighbors == 3) {
                    nextLife[x][y] = 1; // клетка рождается
                }
                else {
                    nextLife[x][y] = 0; // клетка остается мертвой
                }
            }
        }
    }

    // копирование следующего поколения в текущее поколение
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            life[x][y] = nextLife[x][y];
        }
    }
}

void drawLife(int life[WIDTH][HEIGHT]) {
    system("cls"); // очистить консоль

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", life[x][y] ? '#' : ' ');
        }
        printf("\n");
    }
}

int main() {
    int life[WIDTH][HEIGHT];

    initLife(life);
    randomizeLife(life, 25);

    while (1) {
        drawLife(life);
        updateLife(life);
        Sleep(100); // задержка 100 миллисекунд
    }

    return 0;
}
