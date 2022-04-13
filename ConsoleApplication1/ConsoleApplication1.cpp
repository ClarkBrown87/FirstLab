﻿// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _USE_MATH_DEFINES // для C++
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

GLuint VBO; //создание переменной для хранения указателя на буфер вершин
float Scale = 0.0f;
const int width = 300;
const int height = 150;

glm::mat4 Conversion(glm::mat4& m) {
    m[0][0] = sinf(Scale); m[0][1] = 0.0f;        m[0][2] = 0.0f;        m[0][3] = 0.0f;
    m[1][0] = 0.0f;        m[1][1] = cosf(Scale); m[1][2] = 0.0f;        m[1][3] = 0.0f;
    m[2][0] = 0.0f;        m[2][1] = 0.0f;        m[2][2] = sinf(Scale); m[2][3] = 0.0f;
    m[3][0] = 0.0f;        m[3][1] = 0.0f;        m[3][2] = 0.0f;        m[3][3] = 1.0f;
    return m;
}

glm::mat4 Rotation(glm::mat4& m) {
    m[0][0] = cosf(Scale); m[0][1] = -sinf(Scale); m[0][2] = 0.0f; m[0][3] = 0.0f;
    m[1][0] = sinf(Scale); m[1][1] = cosf(Scale);  m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = 0.0f;        m[2][1] = 0.0f;         m[2][2] = 1.0f; m[2][3] = 0.0f;
    m[3][0] = 0.0f;        m[3][1] = 0.0f;         m[3][2] = 0.0f; m[3][3] = 1.0f;
    return m;
}

glm::mat4 Moving(glm::mat4& m) {
    m[0][0] = 1.0f;  m[0][1] = 0.0f;  m[0][2] = 0.0f; m[0][3] = sinf(Scale);
    m[1][0] = 0.0f;  m[1][1] = 1.0f;  m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = 0.0f;  m[2][1] = 0.0f;  m[2][2] = 1.0f; m[2][3] = 0.0f;
    m[3][0] = 0.0f;  m[3][1] = 0.0f;  m[3][2] = 0.0f; m[3][3] = 1.0f;
    return m;
}

glm::mat4 InitPerspectiveProj(float fovy, float aspect, float znear, float zfar){
    glm::mat4 m;
    const float zRange = znear - zfar;
    const float tanHalfFOV = tanf(fovy / 2.0 * M_PI / 180);

    m[0][0] = 1.0f / (tanHalfFOV * aspect);
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;

    m[1][0] = 0.0f;
    m[1][1] = 1.0f / tanHalfFOV;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;

    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = (-znear - zfar) / zRange;
    m[2][3] = 2.0f * zfar * znear / zRange;

    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 1.0f;
    m[3][3] = 0.0f;

    return m;
}

void RenderSceneCB() {
    glClear(GL_COLOR_BUFFER_BIT); //очистка буфера кадра

    glm::vec3 Vertices[3];
    Vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
    Vertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);
    Vertices[2] = glm::vec3(0.0f, 1.0f, 0.0f);

    Scale += 0.001f;

    glm::mat4 mtconv = Conversion(mtconv); //создаем матрицу
    glm::mat4 mtrotation = Rotation(mtrotation);
    glm::mat4 mtmove = Moving(mtmove);
    //glm::mat4 proj = glm::perspective(10.0f, (float)width / (float)height, 1.0f, 100.0f);
    glm::mat4 proj = InitPerspectiveProj(120.0f, (float)width / (float)height, 1.0f, 2000.0f);


    Vertices[0] = glm::vec4(Vertices[0], 1.0f) * proj * mtmove * mtrotation * mtconv;
    Vertices[1] = glm::vec4(Vertices[1], 1.0f) * proj * mtmove * mtrotation * mtconv;
    Vertices[2] = glm::vec4(Vertices[2], 1.0f) * proj * mtmove * mtrotation * mtconv;

    glGenBuffers(1, &VBO); //генерация объектов переменных типов(кол-во, ссылка на массив)
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //привязываем указатель к названию цели и затем запускаем команду на цель(массив вершин, )
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW); //наполняем данными(название цели, размер массива, массив, не изменяем)

    glEnableVertexAttribArray(0); //
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //привязываем буфер для приготавливая его для отрисовки
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //как воспринимать данные внутри буфера(шейдеры, кол-во компон, тип данных, нормализация атрибута)
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
    glutSwapBuffers(); //меняем фоновый буфер и буфер кадра местами
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); //инициализация glut

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //настройка опций двойная буферизация и буфер цвета

    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(width, height);
    glutCreateWindow("Tutorial 01");

    glutDisplayFunc(RenderSceneCB); //очистка буфера
    glutIdleFunc(RenderSceneCB); //очистка буфера

    glClearColor(0.0, 0.0f, 0.0f, 0.0f);

    GLenum res = glewInit(); //инициализация Glew, допустимый контекст рендеринга
    if (res != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    glutMainLoop();

    return 0;
}