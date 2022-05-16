#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <time.h>
#include "eng.h"
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#define str_size 128


int score;
bool food = true;
int snake_len = 5;
short snake_dir = RIGHT;
bool gameOver;
int posX[60] = { 20,20,20,20,20 }, posY[60] = { 20,19,18,17,16 };

coords Grid;
coords Food;

//

void initGrid(int x, int y)
{
    Grid.x = x;
    Grid.y = y;
}

//

//---------- Рандомайзер ----------
coords randomizer()
{
    int maxX = Grid.x - 2;
    int maxY = Grid.y - 2;
    int minV = 1;
    srand(time(NULL));
    return (coords) { (minV + rand() % (maxX - minV)),(minV + rand() % (maxY - minV)) };
}
//---------- Рандомайзер ----------


//---------- Отрисовка -----------

//=== Сетка ===
void drawGrid()
{
    for (int x = 0; x < Grid.x; x++)
    {
        for (int y = 0; y < Grid.y; y++)
        {
            if (x == 0 || y == 0 || x == Grid.x - 1 || y == Grid.y - 1)
            {
                glLineWidth(3.0);
                glColor3f(1.0, 0.0, 0.0);
            }
            else
            {
                glLineWidth(1.0);
                glColor3f(0.0, 0.4, 0.0);

            }

            glBegin(GL_LINE_LOOP);

            glVertex2f(x, y);
            glVertex2f(x + 1, y);
            glVertex2f(x + 1, y + 1);
            glVertex2f(x, y + 1);

            glEnd();
        }
    }

}

//=== Еда ===
void drawFood()
{
    if (food)
        Food = randomizer();
    food = false;
    glColor3f(1.0, 1.0, 1.0);
    glRectf(Food.x, Food.y, Food.x + 1, Food.y + 1);

}

//=== Змейка ===
void drawSnake()
{
    for (int i = snake_len - 1; i > 0; i--)
    {
        posX[i] = posX[i - 1];
        posY[i] = posY[i - 1];

    }

    if (snake_dir == UP)
        posY[0]++;
    else if (snake_dir == DOWN)
        posY[0]--;
    else if (snake_dir == RIGHT)
        posX[0]++;
    else if (snake_dir == LEFT)
        posX[0]--;

    for (int i = 0; i < snake_len; i++)
    {
        if (i == 0)
            glColor3f(0.0, 1.0, 0.0);
        else

            glColor3f(1.0, 0.0, 0.0);

        glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1);


    }


    if (posX[0] == 0 || posY[0] == Grid.x - 1 || posY[0] == 0 || posY[0] == Grid.y - 1)
        gameOver = true;
    if (posX[0] == Food.x && posY[0] == Food.y)
    {
        score++;
        snake_len++;
        if (snake_len > MAX)
            snake_len = MAX;
        food = true;

    }

}

//---------- Отрисовка -----------

//---------- Управление -----------

void keyboard(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        if (snake_dir != DOWN)
            snake_dir = UP;
        break;
    case GLUT_KEY_DOWN:
        if (snake_dir != UP)
            snake_dir = DOWN;
        break;
    case GLUT_KEY_RIGHT:
        if (snake_dir != LEFT)
            snake_dir = RIGHT;
        break;
    case GLUT_KEY_LEFT:
        if (snake_dir != RIGHT)
            snake_dir = LEFT;
        break;
    }

}

//---------- Управление -----------

//---------- Дисплей мини-игры -----------

void display()
{

    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawSnake();
    drawFood();
    glutSwapBuffers();
    if (gameOver)
    {

        char c_score[10];
        _itoa(score, c_score, 10);
        char text[50] = "Score: ";
        strcat(text, c_score);
        MessageBox(NULL, text, "GAME OVER", 0);
        exit(0);

    }

}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

}
void timer()
{
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, timer, 0);

}

//---------- Дисплей мини-игры -----------
void initgame()
{
    //glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("SNAKE");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutSpecialFunc(keyboard);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    initGrid(COLUMNS, ROWS);
    glutMainLoop();
}


enum { UPAR = GLUT_KEY_UP, DOWNAR = GLUT_KEY_DOWN, ENTER = 13 };

int cnt_of_windows = 0;
struct Window* windows;
struct Window* work_window;

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < work_window->but_cnt; i++) {
        //Отрисовка кнопок
        glColor3f(work_window->button_array[i].button_color.r, work_window->button_array[i].button_color.g, work_window->button_array[i].button_color.b);
        glBegin(GL_QUADS);
        glVertex2d(work_window->button_array[i].position.x, work_window->button_array[i].position.y);
        glVertex2d(work_window->button_array[i].position.x + 200, work_window->button_array[i].position.y);
        glVertex2d(work_window->button_array[i].position.x + 200, work_window->button_array[i].position.y + 200);
        glVertex2d(work_window->button_array[i].position.x, work_window->button_array[i].position.y + 200);
        glEnd();
        //Отрисовка текста кнопки
        glColor3f(work_window->button_array[i].hl_color.r, work_window->button_array[i].hl_color.g, work_window->button_array[i].hl_color.b);
        int n = 0;
        glRasterPos2i(work_window->button_array[i].position.x + 4, work_window->button_array[i].position.y + (200 / 4));
        while (work_window->button_array[i].button_name[n]) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, work_window->button_array[i].button_name[n]);
            n++;
        }
    }

    glutSwapBuffers();
}


char* SystemUpdate() {
    for (int i = 0; i < cnt_of_windows; i++) {
        work_window = &windows[i];
        glutInitWindowPosition(work_window->position.x, work_window->position.y);
        glutInitWindowSize(800, 800);
        work_window->win_id = glutCreateWindow("window");
        gluOrtho2D(0, 800, 800, 0);
        glClearColor(work_window->window_color.r, work_window->window_color.g, work_window->window_color.b, 1.0);
        glutDisplayFunc(renderScene);
        glutSpecialFunc(keys);
        glutKeyboardFunc(key_enter);
    }

    glutMainLoop();
}


void SystemInitialise(char* file_name, int argc, char** argv)
{
    glutInit(&argc, argv);

    char file_txt[str_size];

    FILE* menu = fopen(file_name, "r");
    fgets(file_txt, str_size, menu);

    while (strcmp(file_txt, "MenuEnd")) {
        //Параметры окна
        if (!strcmp(file_txt, "WindowBegin\n")) {

            //Выделение памяти под новое окно
            windows = realloc(windows, (cnt_of_windows + 1) * sizeof(struct Window));
            work_window = &windows[cnt_of_windows];
            work_window->but_cnt = 0;
            work_window->but_id = -1;
            work_window->button_array = 0;
            cnt_of_windows++;

            //Считывание положения окна
            fgets(file_txt, str_size, menu);
            sscanf(file_txt, "\tPosition=(%d,%d)\n", &work_window->position.x, &work_window->position.y);
            //Считывание цвета окна
            fgets(file_txt, str_size, menu);
            sscanf(file_txt, "\tColor=(%f,%f,%f)\n", &work_window->window_color.r, &work_window->window_color.g, &work_window->window_color.b);
        }
        //Параметры кнопки
        if (!strcmp(file_txt, "ButtonBegin\n")) {
            //Выделение памяти под кнопку
            work_window->button_array = realloc(work_window->button_array, (work_window->but_cnt + 1) * sizeof(struct Button));
            work_window->but_cnt++;
            struct Button* work_button = &work_window->button_array[(work_window->but_cnt - 1)];

            //Считывание положения кнопки
            fgets(file_txt, str_size, menu);
            sscanf(file_txt, "\tPosition=(%d,%d)\n", &work_button->position.x, &work_button->position.y);

            //Считывание цвета кнопки
            fgets(file_txt, str_size, menu);
            sscanf_s(file_txt, "\tColor=(%f,%f,%f)\n", &work_button->button_color.r, &work_button->button_color.g, &work_button->button_color.b);

            //Считывание цвета окантовки кнопки
            fgets(file_txt, str_size, menu);
            sscanf(file_txt, "\tHighlightColor=(%f,%f,%f)\n", &work_button->hl_color.r, &work_button->hl_color.g, &work_button->hl_color.b);

            //Считывание текста на кнопке
            fgets(file_txt, str_size, menu);
            file_txt[strlen(file_txt) - 1] = '\0';
            work_button->button_name = malloc(0);
            work_button->button_name = strncpy(work_button->button_name, file_txt + 9, strlen(file_txt) - 9);

        }
        fgets(file_txt, str_size, menu);
    }
    SystemUpdate();

}
void SystemRelease() {
    for (int i = 0; i < cnt_of_windows; i++) {
        work_window = &windows[i];
        glutDestroyWindow(work_window->win_id);
        free(work_window->button_array);
        free(work_window);
    }
    free(windows);
}

void get_work_wind()
{
    for (int i = 0; i < cnt_of_windows; i++) {
        struct Window* temp_window = &windows[i];
        if (work_window->win_id == glutGetWindow())
        {
            work_window = temp_window;
        }
    }
}


void keys(int key, int x, int y) {
    get_work_wind();
    switch (key) {
    case UPAR:
        work_window->but_id--;
        break;
    case DOWNAR:
        work_window->but_id++;
        break;

    }
}
void key_enter(int key, int x, int y)
{
    if (key == ENTER)
    {

        initgame();
    }
}

