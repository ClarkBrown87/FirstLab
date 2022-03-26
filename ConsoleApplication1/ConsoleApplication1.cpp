// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <GL/freeglut.h>

int main(int argc, char** argv)
{
    glutInit(&argc, argv); //инициализация glut

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //двойная буферизация и буфер цвета
}