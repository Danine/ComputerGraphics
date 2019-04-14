#include <iostream>
#include <GL/glut.h>

void Midpoint(int x0, int y0, int x1, int y1){
    int a, b, d1, d2, d, x, y;
    a = y0 - y1, b = x1 - x0, d = 2 * a + b;
    d1 = 2 * a, d2 = 2 * (a + b);
    x = x0, y = y0;
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(x, y);
    while(x < x1){
        if(d < 0){
            x++, y++, d += d2;
        }else{
            x++, d += d1;
        }
        glVertex2f(x, y);
    }
}

void test(int x0, int y0, int x1, int y1){
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2d(x0, y0);
    glVertex2d(x1, y1); 
}

void Show(){
    int x0, y0, x1, y1;
    printf("please input double points:\n");
    scanf("%d %d %d %d", &x0, &y0, &x1, &y1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);
    glClear(GL_COLOR_BUFFER_BIT); // 清空颜色缓冲池
    // glPointSize(5);
    glBegin(GL_POINTS);
    Midpoint(x0, y0, x1, y1);
    glEnd();
    glFlush();
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Midpoint");
    glutDisplayFunc(Show);
    glutMainLoop();
    return 0;
}