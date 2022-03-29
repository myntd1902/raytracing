#include "RT.h"
#include <iostream>
using namespace std;

double W_step = 2.0 / WIDTH;
double H_step = 2.0 / HEIGHT;
int POS_X, POS_Y;
vector<Sphere<double>*> spheres;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
    glLoadIdentity();
}

void draw()
{
    render<double>(spheres);
    float x, y;
    int i = 0;
    glBegin(GL_POINTS);
    for (y = 1.0f; y > -1.0; y -= H_step)
    {
        for (x = 1.0f; x > -1.0; x -= W_step)
        {
            glColor3f(image[i].x, image[i].y, image[i].z);
            glVertex3f(x, y, 1);
            if (i < sumPixel)
                i++;
        }
    }
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw();
    glutSwapBuffers();
}

void drawAgainA()
{
    draw();
    spheres.push_back(new Sphere<double>(Vec3<double>(0, -10010, -20), 10002, Vec3<double>(0.5, 0.5, 0.5)));
    spheres.push_back(new Sphere<double>(Vec3<double>(0, 0, -25), 1.5, Vec3<double>(0.2, 0.2, 0.2)));
    spheres.push_back(new Sphere<double>(Vec3<double>(15, 10, 0), 0, Vec3<double>(0), Vec3<double>(0.4))); //sáng
    glutSwapBuffers();
    glutPostRedisplay();
}

void drawAgainD()
{
    draw();
    spheres.push_back(new Sphere<double>(Vec3<double>(0, -10010, -20), 10002, Vec3<double>(0.5, 0.5, 0.5)));
    spheres.push_back(new Sphere<double>(Vec3<double>(0, 0, -25), 1.5, Vec3<double>(0.2, 0.2, 0.2)));
    spheres.push_back(new Sphere<double>(Vec3<double>(-15, 10, 0), 0, Vec3<double>(0), Vec3<double>(0.4))); //sáng
    glutSwapBuffers();
    glutPostRedisplay();
}

void drawAgainS()
{
    draw();
    spheres.push_back(new Sphere<double>(Vec3<double>(0, -10010, -20), 10002, Vec3<double>(0.5, 0.5, 0.5)));
    spheres.push_back(new Sphere<double>(Vec3<double>(0, 0, -25), 1.5, Vec3<double>(0.2, 0.2, 0.2)));
    spheres.push_back(new Sphere<double>(Vec3<double>(0, 15, 20), 0, Vec3<double>(0), Vec3<double>(0.4))); //sáng
    glutSwapBuffers();
    glutPostRedisplay();
}

void drawAgainW()
{
    draw();
    spheres.push_back(new Sphere<double>(Vec3<double>(0, -10010, -20), 10002, Vec3<double>(0.5, 0.5, 0.5)));
    spheres.push_back(new Sphere<double>(Vec3<double>(0, 0, -25), 1.5, Vec3<double>(0.2, 0.2, 0.2)));
    spheres.push_back(new Sphere<double>(Vec3<double>(0, 15, -20), 0, Vec3<double>(0), Vec3<double>(0.4))); //sáng
    glutSwapBuffers();
    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a': //huong10h
        spheres.clear();
        glutIdleFunc(drawAgainA);
        break;
    case 'd': //huong2h
        spheres.clear();
        glutIdleFunc(drawAgainD);
        break;
    case 's': //huong5h30
        spheres.clear();
        glutIdleFunc(drawAgainS);
        break;
    case 'w': //huong11h30
        spheres.clear();
        glutIdleFunc(drawAgainW);
        break;
    default:
        exit(1);
    }
}

int main(int argc, char** argv)
{
    cout << "Su dung ban phim de thay doi vi tri nguon sang: \n";
    cout << "\t phim a: cho nguon sang chech 9h \n";
    cout << "\t phim d: cho nguon sang chech 3h \n";
    cout << "\t phim s: cho nguon sang chech 6h \n";
    cout << "\t phim w: cho nguon sang chech 12h \n";
    cout << "\t phim khac: thoat";

    spheres.push_back(new Sphere<double>(Vec3<double>(0, -10010, -20), 10002, Vec3<double>(0.5, 0.5, 0.5))); //hình cầu rất lớn
    spheres.push_back(new Sphere<double>(Vec3<double>(0, 0, -25), 1.5, Vec3<double>(0.2, 0.2, 0.2))); //hình cầu nhỏ ở trên

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    POS_X = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH) >> 1;
    POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) >> 1;
    glutInitWindowPosition(POS_X, POS_Y);
    glutCreateWindow("Ray Tracing");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}