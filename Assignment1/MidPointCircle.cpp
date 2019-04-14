#include <iostream>
#include <GL/glut.h>

void circlepoints(int x,int y){
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(x, y);
    glVertex2f(y, x);
    glVertex2f(-x, y);
    glVertex2f(y, -x);
    glVertex2f(x, -y);
    glVertex2f(-y, x);
    glVertex2f(-x, -y);
    glVertex2f(-y, -x);
}

void MidPointCircle(int r){
    int x, y;
    float d;
    x = 0;
    y = r;
    d = 1.25 - r;
    circlepoints(x, y);
    while(x <= y){
        if(d < 0)
            d += 2 * x + 3;
        else{
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        circlepoints(x, y);
    }
    // glVertex2f(r, r);
}

void Show(){
    int r;
    printf("please input r:\n");
    scanf("%d",&r);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);
    glClear(GL_COLOR_BUFFER_BIT); // 清空颜色缓冲池
    glBegin(GL_POINTS);
    // glPointSize(20);
    MidPointCircle(r);
    glEnd();
    glFlush();
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("MidPointCircle");
    glutDisplayFunc(Show);
    glutMainLoop();
    return 0;
}