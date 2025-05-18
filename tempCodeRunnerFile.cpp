#include <windows.h>
#include<GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float pos = 0.0, x = 0, col = 0, i, p, c, cf = 0, pr, pl = 0;
int screen = 0;
float wingAngle = 0;
int flapDirection = 1; // 1 for up, -1 for down

//Introduction Page
char name[35] = "Titanium Ship";
char college[100] = "Thapar institute of Technology,Patiala";
char dept[100] = "Department of Computer Science & Engineering";
char heading[100] = "Made by Kashish Seth and Sanat Gupta";
char row1[100] = "Prof. Nitin Arora";
char emsg[100] = "Press ENTER to start";
char title[50] = "Sailing of Ship Day And Night...!";

void frontscreen(void)
{
    glPushMatrix();
    glTranslatef(50, 100, 0);
    glClearColor(0.8, 0.8, 1.0, 1.0);
    int s;
    glClear(GL_COLOR_BUFFER_BIT);

    glRasterPos2i(184, 480);                                                    //displays college name
    for (s = 0; college[s] != '\0'; s++)
    {
        glColor3f(0.0, 0.0, 1.0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, college[s]);
    }

    glRasterPos2i(180, 450);                                                     //displays dept.
    for (s = 0; dept[s] != '\0'; s++)
    {
        glColor3f(1.0, 0.0, 0.0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, dept[s]);
    }

    glRasterPos2i(210, 380);                                                    //displays project name
    for (s = 0; title[s] != '\0'; s++)
    {
        glColor3f(0.0, 0.0, 0.0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, title[s]);
    }

   
    glRasterPos2i(170, 340);                                                    //displays heading of table
    for (s = 0; heading[s] != '\0'; s++)
    {
        glColor3f(0.0, 0.0, 0.0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, heading[s]);
    }

   

    glRasterPos2i(170, 310);                                                    //displays 1st row in table
    for (s = 0; row1[s] != '\0'; s++)
    {
        glColor3f(0.0, 0.0, 0.0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, row1[s]);
    }

   

    glRasterPos2i(200, 100);                                                    //displays "enter msg"
    for (s = 0; emsg[s] != '\0'; s++)
    {
        glColor3f(1.0, 0.0, 0.5);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, emsg[s]);
    }

    glPopMatrix();
    glFlush();
}

//sun/moon
void Drawarc(float sa, float ea, float cx, float cy, float rd)
{
    float PI = 3.14;
    float step = 1.0;
    float angle, x = 0, y = 0, centerX = cx, centerY = cy, radius = rd;

    glBegin(GL_POLYGON);
    for (angle = sa; angle < ea; angle += step)
    {
        float rad;
        rad = PI * angle / 180;
        x = centerX + radius * cos(rad);
        y = centerY + radius * sin(rad);
        glVertex2f(x, y);
    }
    glEnd();
    glFlush();
}
void drawBird(float x, float y);
void drawBird(float x, float y)
{
    glPushMatrix();

    // 1. Translate to position
    glTranslatef(x, y, 0.0f);

    // 2. Simulate 3D rotation (e.g., slight tilt while flying)
    glRotatef(sin(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 10, 1.0f, 0.0f, 0.0f); // X-axis tilt
    glRotatef(sin(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 5, 0.0f, 1.0f, 0.0f);  // Y-axis swing

    // 3. Scale to look dynamic
    glScalef(1.2f, 1.2f, 1.0f);  // Slight zoom

    // Body
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(10, 5);
    glVertex2f(20, 0);
    glVertex2f(10, -5);
    glEnd();

    // Wings with flapping
    glPushMatrix();
    glTranslatef(5, 0, 0);
    glRotatef(wingAngle, 0, 0, 1);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(-10, 10);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, 0, 0);
    glRotatef(-wingAngle, 0, 0, 1);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(10, 10);
    glEnd();
    glPopMatrix();

    glPopMatrix();
}





//smoke
void cloud(int m, int n)
{
    for (c = p = 0; c < 31; c += 10, p -= 1)
    {
        glColor3f(0.5, 0.5, 0.5);
        Drawarc(0, 360, m + c, n, 10 + p);
    }
}

void ship(float x)
{
    glPushMatrix();
    glTranslatef(x, 0, 0);
    //base
    glColor3f(0.2 + col, 0.2 + col, 0.2 + col);
    glBegin(GL_POLYGON);
    glVertex2f(10, 119);
    glVertex2f(10, 110);
    glVertex2f(41, 70);
    glColor3f(0.3 + col, 0.3 + col, 0.8 + col);
    glVertex2f(219, 42);
    glVertex2f(292, 98);
    glVertex2f(300, 110);
    glEnd();

    //p1
    glColor3f(1.0 + col, 1.0 + col, 1.0 + col);
    glBegin(GL_POLYGON);
    glVertex2f(35, 118);
    glVertex2f(35, 128);
    glColor3f(0.5 + col, 0.5 + col, 0.5 + col);
    glVertex2f(239, 131);
    glVertex2f(239, 111);
    glVertex2f(35, 119);
    glEnd();
    //side
    glBegin(GL_POLYGON);
    glColor3f(0.8 + col, 0.8 + col, 0.8 + col);
    glVertex2f(239, 131);
    glVertex2f(239, 111);
    glVertex2f(257, 110);
    glVertex2f(257, 127);
    glEnd();

    //p2
    glColor3f(0.0 + col, 0.0 + col, 0.5 + col);
    glBegin(GL_POLYGON);
    glVertex2f(45, 129);
    glVertex2f(45, 140);
    glVertex2f(233, 149);
    glVertex2f(233, 131);
    glEnd();
    //side
    glBegin(GL_POLYGON);
    glColor3f(0.1 + col, 0.1 + col, 0.8 + col);
    glVertex2f(233, 149);
    glVertex2f(233, 131);
    glVertex2f(254, 128);
    glVertex2f(254, 145);
    glEnd();

    //p3
    glColor3f(0.2 + col, 0.5 + col, 0.2 + col);
    glBegin(GL_POLYGON);
    glVertex2f(51, 151);
    glVertex2f(51, 140);
    glVertex2f(221, 149);
    glColor3f(0.9 + col, 0.6 + col, 0.3 + col);
    glVertex2f(221, 165);
    glVertex2f(51, 151);
    glEnd();
    //side
    glBegin(GL_POLYGON);
    glColor3f(0.1 + col, 0.4 + col, 0.1 + col);
    glVertex2f(221, 164);
    glVertex2f(221, 149);
    glVertex2f(247, 147);
    glVertex2f(247, 162);
    glEnd();

    //p4
        //pipe1
    glColor3f(0.48 + col, 0.27 + col, 0.44 + col);
    glBegin(GL_POLYGON);
    glVertex2f(79, 152);
    glVertex2f(79, 194);
    glVertex2f(94, 194);
    glColor3f(0.0 + col, 0.0 + col, 0.0 + col);
    glVertex2f(94, 155);
    glEnd();
    cloud(59, 194);

    //pipe2
    glColor3f(0.44 + col, 0.48 + col, 0.27 + col);
    glBegin(GL_POLYGON);
    glVertex2f(112, 156);
    glVertex2f(112, 198);
    glVertex2f(127, 198);
    glColor3f(0.0 + col, 0.0 + col, 0.0 + col);
    glVertex2f(127, 158);
    glEnd();
    cloud(92, 198);

    //pipe3
    glColor3f(0.27 + col, 0.48 + col, 0.44 + col);
    glBegin(GL_POLYGON);
    glVertex2f(159, 161);
    glVertex2f(159, 203);
    glVertex2f(179, 203);
    glColor3f(0.0 + col, 0.0 + col, 0.0 + col);
    glVertex2f(179, 160);
    glEnd();
    cloud(144, 203);
    glPopMatrix();
}

void water()
{
    glBegin(GL_POLYGON);
    glColor3f(0.2 + col, 0.2 + col, 0.6 + col);
    glVertex2f(00, 00);
    glVertex2f(00, 300);
    glVertex2f(1024, 300);
    glVertex2f(1024, 00);
    glEnd();
}

void mountain2()
{
    float a, b;
    glColor3f(0.6 + col, 0.4 + col, 0.2 + col);
    for (a = 0, b = 300; a < 1025; a = a + 80)
    {
        glBegin(GL_POLYGON);
        glVertex2f(-40 + a, b);
        glVertex2f(10 + a, b + 140);
        glVertex2f(60 + a, b);
        glEnd();
    }
}

void mountain()
{
    float a, b;
    glColor3f(0.8 + col, 0.6 + col, 0.4 + col);
    for (a = 0, b = 300; a < 1025; a = a + 80)
    {
        glBegin(GL_POLYGON);
        glVertex2f(0 + a, b);
        glVertex2f(50 + a, b + 100);
        glVertex2f(100 + a, b);
        glEnd();
    }
}

void mountain3()
{
    float a, b;
    glColor3f(0.4 + col, 0.2 + col, 0.0 + col);
    for (a = 0, b = 350; a < 1025; a = a + 80)
    {
        glBegin(GL_POLYGON);
        glVertex2f(0 + a, b);
        glVertex2f(50 + a, b + 180);
        glVertex2f(100 + a, b);
        glEnd();
    }
}
float sub = 0.0;  // for submarine movement

void flag(float x)
{
    int s;
    glPushMatrix();
    glTranslatef(x, 0, 0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(245, 160);
    glVertex2f(245, 250);
    glVertex2f(242, 250);
    glVertex2f(242, 160);
    glEnd();
    glColor3f(0.8, 0.1, 0.1);
    glBegin(GL_POLYGON);
    glVertex2f(245, 250);
    glVertex2f(275, 215);
    glVertex2f(245, 180);
    glEnd();
    glRasterPos2i(50, 80);                                                    //displays college name
    for (s = 0; college[s] != '\0'; s++)
    {
        glColor3f(1.0, 1.0, 1.0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, name[s]);
    }
    glPopMatrix();
}
void crackers()
{
    // if(cf==1)
    {
        glColor3f(1, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2f(100 + pos, 100 + pr);
        glVertex2f(100 + pos, 110 + pr);
        glVertex2f(101 + pos, 110 + pr);
        glVertex2f(101 + pos, 100 + pr);
        glEnd();
        glFlush();
    }
    glutPostRedisplay();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glLoadIdentity();
    gluOrtho2D(0, 1024, 0, 768);
}


void submarine()
{
    glPushMatrix();
    glTranslatef(0 + sub, 10, 0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);//rectangular body
    glVertex2f(0.0, 30.0 / 3);
    glVertex2f(0.0, 55.0 / 3);
    glVertex2f(135.0 / 3, 55.0 / 3);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(135.0 / 3, 30.0 / 3);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);//outline of upper triangle plane
    glVertex2f(135.0 / 3, 55.0 / 3);
    glVertex2f(150.0 / 3, 50.0 / 3);
    glVertex2f(155.0 / 3, 45.0 / 3);
    glVertex2f(160.0 / 3, 40.0 / 3);
    glVertex2f(135.0 / 3, 40.0 / 3);
    glEnd();
    glBegin(GL_POLYGON);//lower triangle
    glVertex2f(135.0 / 3, 40.0 / 3);
    glVertex2f(160.0 / 3, 40.0 / 3);
    glVertex2f(160.0 / 3, 37.0 / 3);
    glVertex2f(145.0 / 3, 30.0 / 3);
    glVertex2f(135.0 / 3, 30.0 / 3);
    glEnd();

   
    glPopMatrix();
}
void plane()
{
    glPushMatrix();
    glTranslatef(0 + pl, 700, 0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);//rectangular body
    glVertex2f(0.0, 30.0 / 3);
    glVertex2f(0.0, 55.0 / 3);
    glVertex2f(135.0 / 3, 55.0 / 3);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(135.0 / 3, 30.0 / 3);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);//upper triangle construction plane
    glVertex2f(135.0 / 3, 55.0 / 3);
    glVertex2f(150.0 / 3, 50.0 / 3);
    glVertex2f(155.0 / 3, 45.0 / 3);
    glVertex2f(160.0 / 3, 40.0 / 3);
    glVertex2f(135.0 / 3, 40.0 / 3);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);//outline of upper triangle plane
    glVertex2f(135.0 / 3, 55.0 / 3);
    glVertex2f(150.0 / 3, 50.0 / 3);
    glVertex2f(155.0 / 3, 45.0 / 3);
    glVertex2f(160.0 / 3, 40.0 / 3);
    glVertex2f(135.0 / 3, 40.0 / 3);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);//lower triangle
    glVertex2f(135.0 / 3, 40.0 / 3);
    glVertex2f(160.0 / 3, 40.0 / 3);
    glVertex2f(160.0 / 3, 37.0 / 3);
    glVertex2f(145.0 / 3, 30.0 / 3);
    glVertex2f(135.0 / 3, 30.0 / 3);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);//back wing
    glVertex2f(0.0, 55.0 / 3);
    glVertex2f(0.0, 80.0 / 3);
    glVertex2f(10.0 / 3, 80.0 / 3);
    glVertex2f(40.0 / 3, 55.0 / 3);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);//left side wing
    glVertex2f(65.0 / 3, 55.0 / 3);
    glVertex2f(50.0 / 3, 70.0 / 3);
    glVertex2f(75.0 / 3, 70.0 / 3);
    glVertex2f(90.0 / 3, 55.0 / 3);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);//rightside wing
    glVertex2f(70.0 / 3, 40.0 / 3);
    glVertex2f(100.0 / 3, 40.0 / 3);
    glVertex2f(80.0 / 3, 15.0 / 3);
    glVertex2f(50.0 / 3, 15.0 / 3);
    glEnd();
    glPopMatrix();
}
float birdX = 0.0f;
//float wingAngle = 0;
//int flapDirection = 1; // 1 for up, -1 for down

void updateBirds(int value)
{
    birdX += 0.4f;  
    if (birdX > 1300)  
        birdX = -100;

    glutPostRedisplay();
    glutTimerFunc(30, updateBirds, 0);  // Call again after 30ms
}



void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (screen == 0)
    {
        frontscreen();
    }
    else if (screen == 1)
    {
        // Draw background elements
        mountain3();
        mountain2();
        mountain();
        water();

        // Fire crackers if flag set
        if (cf == 1)
        {
            crackers();
            pr += 2;
        }

        // Draw ship and flag at position 'pos'
        ship(pos);
        flag(pos);
        

        if (pos > 1200)  // adjust 1200 to your screen width if needed
        pos = -5;  // start from off-screen on the left


        // Animate plane
        plane();
        pl += 0.5;
        if (pl >= 1200)
            pl = 0;
        submarine();
        sub += 0.1;
        if (sub >= 1200)
            sub = 0;

        // Draw stars or other circular elements
        if (i == 1)
        {
            glColor3f(0.9, 0.9, 0.5); // star 1
            Drawarc(0, 360, 200, 700, 10);
        }
        if (i == 2)
        {
            glColor3f(0.8, 0.7, 0.4); // star 2
            Drawarc(0, 360, 400, 700, 10);
        }
        if (i == 3)
        {
            glColor3f(1.0, 1.0, 1.0); // star 3
            Drawarc(0, 360, 600, 700, 10);
        }
        if (i == 4)
        {
            glColor3f(1.0, 1.0, 1.0); // star 4
            Drawarc(0, 360, 800, 700, 10);
        }
        if (flapDirection == 1)
        wingAngle += 0.5;
        else
        wingAngle -= 0.5;

        if (wingAngle >= 20)  // Max wing up angle
        flapDirection = -1;
        else if (wingAngle <= -20)  // Max wing down angle
        flapDirection = 1;


        // Animate birds
        drawBird(100 + birdX, 600 + sin(birdX * 0.05) * 5);
drawBird(150 + birdX, 620 + sin((birdX + 10) * 0.05) * 5);
drawBird(200 + birdX, 610 + sin((birdX + 20) * 0.05) * 5);

        
    }

    glutSwapBuffers();       // For double buffering
    glutPostRedisplay();     // Continuous redraw
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 13:if (screen == 0)
    {
        screen = 1;
        glutPostRedisplay();
    }
           break;
    case 27:exit(0);
        break;
    case 'y':glClearColor(0.8, 0.5, 0.4, 1.0);
        col = -0.1;
        i = 0;
        glutPostRedisplay();
        break;
    case 'm':glClearColor(0.5, 0.5, 1.0, 1.0);
        i = 1;
        col = 0.2;
        glutPostRedisplay();
        break;
    case 'a':glClearColor(0.9, 0.9, 0.3, 1.0);
        i = 2;
        col = 0.3;
        glutPostRedisplay();
        break;
    case 'e':glClearColor(0.8, 0.5, 0.4, 1.0);
        col = -0.1;
        i = 0;
        glutPostRedisplay();
        break;
    case 'n':glClearColor(0.5, 0.5, 0.5, 1.0);
        i = 3;
        glutPostRedisplay();
        col = -0.2;
        break;
    case 'd':glClearColor(0.0, 0.0, 0.0, 0.0);
        i = 4;
        col = -0.3;
        glutPostRedisplay();
        break;
    case '6':pos += 2;
        break;
    case '4':pos -= 2;
        break;
    case 'z':cf = 1;
        pr = 0;
        glutPostRedisplay();
        break;
    }
}
void SpecialInput(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        break;
    case GLUT_KEY_DOWN:
        break;
    case GLUT_KEY_LEFT:
        pos -= 4;
        break;
    case GLUT_KEY_RIGHT:
        pos += 4;
        break;
    }
}

int main()
{    int argc = 1;
    char *argv[1] = { (char*)"Titanium Ship" };
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("TITANIUM");
    glutSwapBuffers();
    glutTimerFunc(0, updateBirds, 0);

    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutSpecialFunc(SpecialInput);
    init();
    glutMainLoop();
}