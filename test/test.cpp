// 挠头.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include "GL/glut.h"

// 将立方体的八个顶点保存到一个数组里面
static const GLfloat vertex_list[][3] = {
    {-0.5f, -0.5f, -0.5f},
    { 0.5f, -0.5f, -0.5f},
    {-0.5f,  0.5f, -0.5f},
    { 0.5f,  0.5f, -0.5f},
    {-0.5f, -0.5f,  0.5f},
    { 0.5f, -0.5f,  0.5f},
    {-0.5f,  0.5f,  0.5f},
    { 0.5f,  0.5f,  0.5f},
};

// 将要使用的顶点的序号保存到一个数组里面
static const GLint index_list[][2] = 
{ 
    {2, 3},
    {4, 5},
    {6, 7},
    {0, 2},
    {4, 6},
    {5, 7},
    {0, 4},
    {7, 3},
    {2, 6}
};

static const GLint dotted[][2] =
{
    {0, 1},
    {1, 3},
    {1, 5}
};
void Show()
{
    glMatrixMode(GL_PROJECTION);
    glBegin(GL_LINES);
    int i, j;
    for(i=0; i<9; ++i) // 12 条线段
    {
        for(j=0; j<2; ++j) // 每条线段 2个顶点
        {
            glVertex3fv(vertex_list[index_list[i][j]]);
        }
    }
    glEnd();

    // glMatrixMode(GL_PROJECTION);
    glLineStipple(2, 0x5555);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    for(i = 0; i<3; i++){
        for(j=0; j<2; ++j) // 每条线段 2个顶点
        {
            glVertex3fv(vertex_list[dotted[i][j]]);
        }
    }
    glEnd();
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("OpenGL-ONE");
    glRotatef(15, 1, 0, 0);
    glRotatef(15, 0, 1, 0);
    glutDisplayFunc(Show);
    glutMainLoop();
    return 0;
}