#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;
GLint set[50][2];//最多50个点
int point = 0;//记录当前点的个数
bool canpoint = true, movepoint = false;
int MouseX, MouseY, oldx, oldy, moved;

void draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    for (int i = 0; i < point; i++) {
        glVertex2d(set[i][0], set[i][1]);
    }
    glEnd();
    glFlush();
}

//鼠标点击事件
void OnMouse(int button, int state, int x, int y) {
    y = 1000 - y;
    MouseX = x;
    MouseY = y;
    oldx = MouseX, oldy = MouseY;
    //设置顶点坐标
    if (canpoint && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        set[point][0] = x;
        set[point][1] = y;
        point++;
        glEnd();
        glFlush();
    }
    //判断鼠标点击位置是否是顶点，以便拖动
    for (int i = 0; i < point; i++){
        if (!canpoint && x - set[i][0] < 10 && x - set[i][0] > -10 && y - set[i][1] < 10 && y - set[i][1] > -10){
            movepoint = true;
            moved = i;
        }
    }
    //拖动完放开鼠标左键时将拖动flag重置
    if(!canpoint && movepoint && button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        movepoint = false;
    // if(!canpoint && button == GLUT_MIDDLE_BUTTON && state == GLU)
}

//判断是否在多边形里（待完善）
bool isInner(int x, int y) {
    GLfloat color;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &color);
    cout << (int)color << endl;
    if (int(color) == 0)
        return true;
    return true;
}

//鼠标按下事件（拖）
void pressMouse(int x, int y) {
    y = 1000 - y;
    //拖动点
    if(!canpoint && movepoint){
        int dx = x - oldx;
        int dy = y - oldy;
        set[moved][0] += dx;
        set[moved][1] += dy;
        glutPostRedisplay();
        oldx = x, oldy = y;
        draw();
    }else{
        if (!canpoint && isInner(x, y)) {
            int dx = x - oldx;
            int dy = y - oldy;
            for (int i = 0; i < point; i++) {
                set[i][0] += dx;
                set[i][1] += dy;
            }
            glutPostRedisplay();
            oldx = x, oldy = y;
            draw();
        }
    }
}

void suofang(int x,int y,float zoom){
    for (int i = 0; i < point; i++){
        int dx = set[i][0] - x;
        int dy = set[i][1] - y;
        set[i][0] = x + dx * zoom;
        set[i][1] = y + dy * zoom;
    }
    glutPostRedisplay();
    draw();
}

void roll(int x, int y, int dir)    //旋转操作
{
    printf("into the roll process\n");

    float min = dir/10.0;
    float a;

    for (int i = 0; i < point; i++)    {
        float r= sqrt(pow(set[i][0] - x, 2) + pow(set[i][1] - y, 2));//r为顶点到鼠标点距离
        if (set[i][1] >= y)//alpha用于表示旋转前顶点的位置，例如顶点相对鼠标点位于一二象限时，alpha是鼠标点顶点连线与x正半轴的夹角
            a = acos((set[i][0] - x) / r);
        else//顶点相对鼠标点位于三四象限时，alpha对于位于一二象限的情况下计算得出的角度需要+/-180度
            a = -acos((set[i][0] - x) / r);
        
        //此处为旋转后点坐标的计算公式
        set[i][0] = x + r * cos(a + min);
        set[i][1] = y + r * sin(a + min);
    }
    draw();
}

//键盘点击事件
void KeyBoard(unsigned char key, int x, int y) {
    y = 1000 - y;
    switch (key) {
        case 'd'://按下d的时候把点连成多边形
            glBegin(GL_POLYGON);
            for (int i = 0; i < point; i++) {
                glVertex2d(set[i][0], set[i][1]);
            }
            glEnd();
            glFlush();
            canpoint = false;
            break;
    }
}

void SpecialKey(GLint key, int x, int y){
    y = 1000 - y;
    int centerx = 500, centery = 500;
    int dir = 0;
    float zoom = 1;
    if(key == GLUT_KEY_LEFT){
        dir--;
        roll(x, y, dir);
    }
    if(key == GLUT_KEY_RIGHT){
        dir++;
        roll(x, y, dir);
    }
    if(key == GLUT_KEY_UP){
        zoom += 0.1;
        suofang(centerx, centery, zoom);
    }
    if(key == GLUT_KEY_DOWN){
        zoom -= 0.1;
        suofang(centerx, centery, zoom);
    }
}

void show() {
    // glClearColor(0.6,0.6,0.6,0);
    glPointSize(6);
    glMatrixMode(GL_PROJECTION);//对接下来要做什么进行一下声明。GL_PROJECTION 投影, GL_MODELVIEW 模型视图, GL_TEXTURE 纹理
    glLoadIdentity();//把矩阵设为单位矩阵
    gluOrtho2D(0, 1000, 0, 1000);
    glClear(GL_COLOR_BUFFER_BIT);//清空颜色缓冲池
    glFlush();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Assignment3");
    glutDisplayFunc(show);
    glutMouseFunc(OnMouse);//注册鼠标事件
    glutMotionFunc(pressMouse);//注册鼠标按下事件
    glutKeyboardFunc(KeyBoard);//注册键盘事件
    glutSpecialFunc(SpecialKey);
    glutMainLoop();
    return 0;
}