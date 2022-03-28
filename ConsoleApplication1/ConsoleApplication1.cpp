// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <GL/glew.h>
#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint VBO; //создание переменной для хранения указателя на буфер вершин
void RenderSceneCB() {
    glClear(GL_COLOR_BUFFER_BIT); //очистка буфера кадра
    glEnableVertexAttribArray(0); //
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //привязываем буфер для приготавливая его для отрисовки
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //как воспринимать данные внутри буфера(шейдеры, кол-во компон, тип данных, нормализация атрибута)
    //glDrawArrays(GL_POINTS, 0, 1);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
    glutSwapBuffers(); //меняем фоновый буфер и буфер кадра местами
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); //инициализация glut

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //настройка опций двойная буферизация и буфер цвета

    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 01");

    glutDisplayFunc(RenderSceneCB); //очистка буфера

    glClearColor(0.0, 0.0f, 0.0f, 0.0f);

    GLenum res = glewInit(); //инициализация Glew, допустимый контекст рендеринга
    if (res != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    glm::vec3 Vertices[3];
    Vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
    Vertices[1] = glm::vec3(-1.0f, 1.0f, 0.0f);
    Vertices[2] = glm::vec3(1.0f, 0.0f, 0.5f);

    glGenBuffers(1, &VBO); //генерация объектов переменных типов(кол-во, ссылка на массив)
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //привязываем указатель к названию цели и затем запускаем команду на цель(массив вершин, )
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW); //наполняем данными(название цели, размер массива, массив, не изменяем)

    

    glutMainLoop();

    return 0;
}