#ifndef TASK4_BASE_ENG_H
#define TASK4_BASE_ENG_H

#define COLUMNS 40
#define ROWS 40
#define FPS 10
#define MAX 60

enum {LEFT = -2, RIGHT = 2, UP = 1, DOWN = -1};

typedef struct
{
    int x, y;
} coords;

struct Color {
    float r;
    float g;
    float b;
};

struct Pos {
    int x;
    int y;
};

struct Button {
    struct Pos position;
    struct Color button_color;
    struct Color hl_color;
    char* button_name;
};

struct Window {
    struct Pos position;
    struct Color window_color;
    struct Button* button_array;
    int but_cnt;
    int win_id;
    int but_id;
};

void SystemInitialise(char* file_name, int argc, char** argv);
void SystemRelease();
char* SystemUpdate();
void renderScene();
void keys(int key, int x, int y);
void key_enter(int key, int x, int y);

void initGrid(int x, int y);
void drawGrid();
void drawSnake();
void drawFood();
coords randomizer();
void keyboard(int key, int x, int y);
void display();
void reshape(int w, int h);
void timer();
void initgame();
#endif