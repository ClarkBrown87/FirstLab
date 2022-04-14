# FirstLab && SecLab
glm::mat4 InitCameraTransform(const glm::vec3& Target, const glm::vec3& Up) //Эта функция генерирует преобразования камеры
glm::vec3 Normalize(glm::vec3 v) //Для генерации матрицы UVN мы должны сделать вектора единичной длины. Это называется 'нормировать вектор', заключается в том, что все компоненты вектора делятся на его длину
glm::vec3 Cross(const glm::vec3 v1, const glm::vec3 v2) //функция озвращает вектор, перпендикулярный плоскости, определяемой исходными векторами.
glm::mat4 InitPerspectiveProj(float fovy, float aspect, float znear, float zfar) //функция для проецирования перспективы
GLuint VBO; //создание переменной для хранения указателя на буфер вершин
glClear(GL_COLOR_BUFFER_BIT); //очистка буфера кадра
glEnableVertexAttribArray(0); //включить или выключить общий массив вершинных атрибутов(передаем индекс)
glBindBuffer(GL_ARRAY_BUFFER, VBO); //привязываем буфер для приготавливая его для отрисовки
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);//как воспринимать данные внутри буфера(шейдеры, кол-во компон, тип данных, нормализация атрибута)
glDrawArrays(GL_TRIANGLES, 0, 3); //визуализировать примитивы из данных массива
glDisableVertexAttribArray(0); //Включить или отключить универсальный массив атрибутов вершин(передаем индекс)
glutSwapBuffers(); //меняем фоновый буфер и буфер кадра местами

glutInit(&argc, argv); //инициализация glut
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //настройка опций двойная буферизация и буфер цвета

//задаем параметры окна
glutInitWindowSize(1024, 768);
glutInitWindowPosition(100, 100);
glutCreateWindow("Tutorial 01");

glutDisplayFunc(RenderSceneCB); //очистка буфера
glClearColor(0.0, 0.0f, 0.0f, 0.0f); //задаем цвет открывшегося окна

GLenum res = glewInit(); //инициализация Glew, допустимый контекст рендеринга

//проверка на ошибки инициализированного Glew
if (res != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

//создаем вектор из 3-х вершин
glm::vec3 Vertices[3];
Vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
Vertices[1] = glm::vec3(-1.0f, 1.0f, 0.0f);
Vertices[2] = glm::vec3(1.0f, 0.0f, 0.5f);

glGenBuffers(1, &VBO); //генерация объектов переменных типов(кол-во, ссылка на массив)
glBindBuffer(GL_ARRAY_BUFFER, VBO); //привязываем указатель к названию цели и затем запускаем команду на цель(массив вершин, )
glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW); //наполняем данными(название цели, размер массива, массив, не изменяем)

glutMainLoop(); //входит в цикл обработки событий GLUT

В данной лабораторной работе я научился создавать окно различных фоновых цветов и рисовать треугольник из заданных точек
