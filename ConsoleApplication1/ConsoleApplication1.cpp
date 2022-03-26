// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <GL/freeglut.h>

void RenderSceneCB() {
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); //инициализация glut

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //двойная буферизация и буфер цвета

    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 01");

    glutDisplayFunc(RenderSceneCB); //очистка буфера
}