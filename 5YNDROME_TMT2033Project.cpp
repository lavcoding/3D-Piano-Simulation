/*
TMT2033 Computer Graphics
Project - Option 4 : to graphically simulate 3D hands playing a piano

Group 5YNDROME :
Ho Jia Wei      (79545)
Jason Chan Fong (79630)
Ku Wan Sien     (79801)
Lim Ai Vi       (79877)
Lim Wei Guan    (79885)

READ ME :
1. Requirements,
    - Microsoft Visual Studio Community 2022
    - Setup GLUT package in Visual Studio
    - Set Solution Platform to x86
2. To play the piano,
    - press key 'z' 'x' 'c' 'v' 'b' 'n' 'm' to play the first octave of white keys (C1 - B1)
    - press key 'a' 's' 'd' 'f' 'g' 'h' 'j' to play the second octave of white keys (C2 - B2)
    - press key '1' '2' '3' '4' '5' to play the first octave of black keys (Db1 - Bb1)
    - press key '6' '7' '8' '9' '0' to play the second octave of black keys (Db2 - Bb2)
3. To free roaming, drag the screen freely with the mouse.
4. To pause/resume the animation, press the key 'p'. (Note: When paused, free roaming will pause too
   and the piano will not play any sound even if the keys are pressed.)
5. To quit, press key 'Esc'.
*/

#include <windows.h>  // for MS Windows
#include <GL/glut.h>
#pragma comment(lib,"winmm.lib")
#include "mmsystem.h"

static int
A1Angle = 0.0f, B1Angle = 0.0f, C1Angle = 0.0f, D1Angle = 0.0f, E1Angle = 0.0f, F1Angle = 0.0f, G1Angle = 0.0f,
A2Angle = 0.0f, B2Angle = 0.0f, C2Angle = 0.0f, D2Angle = 0.0f, E2Angle = 0.0f, F2Angle = 0.0f, G2Angle = 0.0f,
Db1Angle = 0.0f, Gb1Angle = 0.0f, Eb1Angle = 0.0f, Ab1Angle = 0.0f, Bb1Angle = 0.0f,
Db1AngleDown = 0.0f, Gb1AngleDown = 0.0f, Eb1AngleDown = 0.0f, Ab1AngleDown = 0.0f, Bb1AngleDown = 0.0f,
Db2Angle = 0.0f, Gb2Angle = 0.0f, Eb2Angle = 0.0f, Ab2Angle = 0.0f, Bb2Angle = 0.0f,
Db2AngleDown = 0.0f, Gb2AngleDown = 0.0f, Eb2AngleDown = 0.0f, Ab2AngleDown = 0.0f, Bb2AngleDown = 0.0f,
LeftThumb = 0.0f, LeftIndex = 0.0f, LeftMiddle = 0.0f, LeftRing = 0.0f, LeftPinky = 0.0f,
LeftMoveX = 0.0f, LeftMoveY = 0.0f, LeftMoveZ = 0.0f,
RightMoveX = 0.0f, RightMoveY = 0.0f, RightMoveZ = 0.0f, Piano = 0.0f,
RightThumb = 0.0f, RightIndex = 0.0f, RightMiddle = 0.0f, RightRing = 0.0f, RightPinky = 0.0f;

GLfloat translateX = 0.0f;
GLfloat translateY = 0.0f;
GLfloat translateZ = -7.0f;
int lastMouseX = 0;
int lastMouseY = 0;
bool isMouseLeftButtonClicked = false;
bool isPaused = false;
GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;

/* Initialize OpenGL Graphics */
void initGL() {
    glClearColor(0.71f, 0.84f, 0.84f, 1.0f);
    glClearDepth(1.0f);         // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);    // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);     // Set the type of depth-test
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void keyboardInput(unsigned char key, int x, int y)
{
    if (key == 'p' || key == 'P') {
        isPaused = !isPaused;
    }

    if (key == 27) {
        exit(0);
    }

    if (!isPaused)
    {
        switch (key) {
        case 'z': C1Angle = 5; Piano = -0.97; LeftPinky = -5; PlaySound(TEXT("C1.wav"), NULL, SND_ASYNC); break;
        case 'x': D1Angle = 5; Piano = -0.97; LeftRing = -5; PlaySound(TEXT("D1.wav"), NULL, SND_ASYNC); break;
        case 'c': E1Angle = 5; Piano = -0.97; LeftMiddle = -5; PlaySound(TEXT("E1.wav"), NULL, SND_ASYNC); break;
        case 'v': F1Angle = 5; Piano = -0.97; LeftIndex = -5; PlaySound(TEXT("F1.wav"), NULL, SND_ASYNC); break;
        case 'b': G1Angle = 5; Piano = -0.97; LeftThumb = -5; PlaySound(TEXT("G1.wav"), NULL, SND_ASYNC); break;
        case 'n': A1Angle = 5; Piano = -0.97; LeftMoveX = 7.0; PlaySound(TEXT("A1.wav"), NULL, SND_ASYNC); LeftIndex = -5; break;
        case 'm': B1Angle = 5; Piano = -0.97; LeftMoveX = 7.0; PlaySound(TEXT("B1.wav"), NULL, SND_ASYNC); LeftThumb = -5; break;
        case 'a': C2Angle = 5; Piano = -0.97; RightMoveX = -7.0; PlaySound(TEXT("C2.wav"), NULL, SND_ASYNC); RightThumb = -5; break;
        case 's': D2Angle = 5; Piano = -0.97; RightMoveX = -7.0; PlaySound(TEXT("D2.wav"), NULL, SND_ASYNC); RightIndex = -5; break;
        case 'd': E2Angle = 5; Piano = -0.97; RightThumb = -5; PlaySound(TEXT("E2.wav"), NULL, SND_ASYNC); break;
        case 'f': F2Angle = 5; Piano = -0.97; RightIndex = -5; PlaySound(TEXT("F2.wav"), NULL, SND_ASYNC); break;
        case 'g': G2Angle = 5; Piano = -0.97; RightMiddle = -5; PlaySound(TEXT("G2.wav"), NULL, SND_ASYNC); break;
        case 'h': A2Angle = 5; Piano = -0.97; RightRing = -5; PlaySound(TEXT("A2.wav"), NULL, SND_ASYNC); break;
        case 'j': B2Angle = 5; Piano = -0.97; RightPinky = -5; PlaySound(TEXT("B2.wav"), NULL, SND_ASYNC); break;
        case '1': Db1Angle = 5; LeftMoveX = 1.9; LeftMoveY = 1.5; LeftMoveZ = -8.5; LeftPinky = -3; Db1AngleDown = -1; PlaySound(TEXT("DB1.wav"), NULL, SND_ASYNC); break;
        case '2': Eb1Angle = 5; LeftMoveX = 1.9; LeftMoveY = 1.5; LeftMoveZ = -8.5; LeftRing = -3; Eb1AngleDown = -1; PlaySound(TEXT("EB1.wav"), NULL, SND_ASYNC); break;
        case '3': Gb1Angle = 5; LeftMoveX = 9.5; LeftMoveY = 1.5; LeftMoveZ = -8.5; LeftRing = -3; Gb1AngleDown = -1; PlaySound(TEXT("GB1.wav"), NULL, SND_ASYNC); break;
        case '4': Ab1Angle = 5; LeftMoveX = 9.5; LeftMoveY = 1.5; LeftMoveZ = -8.5; LeftMiddle = -3; Ab1AngleDown = -1; PlaySound(TEXT("AB1.wav"), NULL, SND_ASYNC); break;
        case '5': Bb1Angle = 5; LeftMoveX = 9.5; LeftMoveY = 1.5; LeftMoveZ = -8.5; LeftIndex = -3; Bb1AngleDown = -1; PlaySound(TEXT("BB1.wav"), NULL, SND_ASYNC); break;
        case '6': Db2Angle = 5; RightMoveX = -9.5; RightMoveY = 1.5; RightMoveZ = -8.5; RightIndex = -3; Db2AngleDown = -1; PlaySound(TEXT("DB2.wav"), NULL, SND_ASYNC); break;
        case '7': Eb2Angle = 5; RightMoveX = -9.5; RightMoveY = 1.5; RightMoveZ = -8.5; RightMiddle = -3; Eb2AngleDown = -1; PlaySound(TEXT("EB2.wav"), NULL, SND_ASYNC); break;
        case '8': Gb2Angle = 5; RightMoveX = -1.9; RightMoveY = 1.5; RightMoveZ = -8.5; RightMiddle = -3; Gb2AngleDown = -1; PlaySound(TEXT("GB2.wav"), NULL, SND_ASYNC); break;
        case '9': Ab2Angle = 5; RightMoveX = -1.9; RightMoveY = 1.5; RightMoveZ = -8.5; RightRing = -3; Ab2AngleDown = -1; PlaySound(TEXT("AB2.wav"), NULL, SND_ASYNC); break;
        case '0': Bb2Angle = 5; RightMoveX = -1.9; RightMoveY = 1.5; RightMoveZ = -8.5; RightPinky = -3; Bb2AngleDown = -1; PlaySound(TEXT("BB2.wav"), NULL, SND_ASYNC); break;

        default: return;
        }
        glutPostRedisplay(); // Trigger a redraw
    }

}

void keyReleased(unsigned char key, int x, int y)
{
    switch (key) {
    case 'z': C1Angle = 0; Piano = 0; LeftPinky = 0; break;
    case 'x': D1Angle = 0; Piano = 0; LeftRing = 0; break;
    case 'c': E1Angle = 0; Piano = 0; LeftMiddle = 0; break;
    case 'v': F1Angle = 0; Piano = 0; LeftIndex = 0; break;
    case 'b': G1Angle = 0; Piano = 0; LeftThumb = 0; break;
    case 'n': A1Angle = 0; Piano = 0; LeftMoveX = 0; LeftIndex = 0; break;
    case 'm': B1Angle = 0; Piano = 0; LeftMoveX = 0; LeftThumb = 0; break;
    case 'a': C2Angle = 0; Piano = 0; RightMoveX = 0; RightThumb = 0; break;
    case 's': D2Angle = 0; Piano = 0; RightMoveX = 0; RightIndex = 0; break;
    case 'd': E2Angle = 0; Piano = 0; RightThumb = 0; break;
    case 'f': F2Angle = 0; Piano = 0; RightIndex = 0; break;
    case 'g': G2Angle = 0; Piano = 0; RightMiddle = 0; break;
    case 'h': A2Angle = 0; Piano = 0; RightRing = 0; break;
    case 'j': B2Angle = 0; Piano = 0; RightPinky = 0; break;
    case '1': Db1Angle = 0, LeftMoveX = 0; LeftMoveY = 0; LeftMoveZ = 0; LeftPinky = 0; Db1AngleDown = 0; break;
    case '3': Gb1Angle = 0, LeftMoveX = 0; LeftMoveY = 0; LeftMoveZ = 0; LeftRing = 0; Gb1AngleDown = 0; break;
    case '2': Eb1Angle = 0, LeftMoveX = 0; LeftMoveY = 0; LeftMoveZ = 0; LeftRing = 0; Eb1AngleDown = 0; break;
    case '4': Ab1Angle = 0, LeftMoveX = 0; LeftMoveY = 0; LeftMoveZ = 0; LeftMiddle = 0; Ab1AngleDown = 0; break;
    case '5': Bb1Angle = 0, LeftMoveX = 0; LeftMoveY = 0; LeftMoveZ = 0; LeftIndex = 0; Bb1AngleDown = 0; break;
    case '6': Db2Angle = 0, RightMoveX = 0; RightMoveY = 0; RightMoveZ = 0; RightIndex = 0; Db2AngleDown = 0; break;
    case '8': Gb2Angle = 0, RightMoveX = 0; RightMoveY = 0; RightMoveZ = 0; RightMiddle = 0; Gb2AngleDown = 0; break;
    case '7': Eb2Angle = 0, RightMoveX = 0; RightMoveY = 0; RightMoveZ = 0; RightMiddle = 0; Eb2AngleDown = 0; break;
    case '9': Ab2Angle = 0, RightMoveX = 0; RightMoveY = 0; RightMoveZ = 0; RightRing = 0; Ab2AngleDown = 0; break;
    case '0': Bb2Angle = 0, RightMoveX = 0; RightMoveY = 0; RightMoveZ = 0; RightPinky = 0; Bb2AngleDown = 0; break;

    default: return;
    }
    glutPostRedisplay(); // Trigger a redraw
}

void drawC1() {
    glBegin(GL_QUADS); // Draw the C1 key
    glColor3f(1.0f, 1.0f, 1.0f);

    // Top face (y = 3.0f)
    glVertex3f(-21.0f, 3.0f, -7.0f);
    glVertex3f(-21.0f, 3.0f, 8.0f);
    glVertex3f(-18.0f, 3.0f, 8.0f);
    glVertex3f(-18.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(-21.0f, 0.0f, -7.0f);
    glVertex3f(-18.0f, 0.0f, -7.0f);
    glVertex3f(-18.0f, 0.0f, 8.0f);
    glVertex3f(-21.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(-21.0f, 0.0f, 8.0f);
    glVertex3f(-18.0f, 0.0f, 8.0f);
    glVertex3f(-18.0f, 3.0f, 8.0f);
    glVertex3f(-21.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(-21.0f, 0.0f, -7.0f);
    glVertex3f(-21.0f, 3.0f, -7.0f);
    glVertex3f(-18.0f, 3.0f, -7.0f);
    glVertex3f(-18.0f, 0.0f, -7.0f);

    // Left face (x = -18.0f)
    glVertex3f(-18.0f, 3.0f, -7.0f);
    glVertex3f(-18.0f, 0.0f, -7.0f);
    glVertex3f(-18.0f, 0.0f, 8.0f);
    glVertex3f(-18.0f, 3.0f, 8.0f);

    // Right face (x = -21.0f)
    glVertex3f(-21.0f, 3.0f, -7.0f);
    glVertex3f(-21.0f, 3.0f, 8.0f);
    glVertex3f(-21.0f, 0.0f, 8.0f);
    glVertex3f(-21.0f, 0.0f, -7.0f);
    glEnd();  // End of drawing C1 key

    // Draw the C1's edges
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 3.0f)
    glVertex3f(-21.0f, 3.0f, -7.0f);
    glVertex3f(-21.0f, 3.0f, 8.0f);
    glVertex3f(-18.0f, 3.0f, 8.0f);
    glVertex3f(-18.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(-21.0f, 0.0f, -7.0f);
    glVertex3f(-18.0f, 0.0f, -7.0f);
    glVertex3f(-18.0f, 0.0f, 8.0f);
    glVertex3f(-21.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(-21.0f, 0.0f, 8.0f);
    glVertex3f(-18.0f, 0.0f, 8.0f);
    glVertex3f(-18.0f, 3.0f, 8.0f);
    glVertex3f(-21.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(-21.0f, 0.0f, -7.0f);
    glVertex3f(-21.0f, 3.0f, -7.0f);
    glVertex3f(-18.0f, 3.0f, -7.0f);
    glVertex3f(-18.0f, 0.0f, -7.0f);

    // Left face (x = -18.0f)
    glVertex3f(-18.0f, 3.0f, -7.0f);
    glVertex3f(-18.0f, 0.0f, -7.0f);
    glVertex3f(-18.0f, 0.0f, 8.0f);
    glVertex3f(-18.0f, 3.0f, 8.0f);

    // Right face (x = -21.0f)
    glVertex3f(-21.0f, 3.0f, -7.0f);
    glVertex3f(-21.0f, 3.0f, 8.0f);
    glVertex3f(-21.0f, 0.0f, 8.0f);
    glVertex3f(-21.0f, 0.0f, -7.0f);

    glEnd();
}

void drawD1() {
    glBegin(GL_QUADS); // // Draw the D1 key
    glColor3f(1.0f, 1.0f, 1.0f);

    // Top face (y = 3.0f)
    glVertex3f(-18.0f, 3.0f, -7.0f);
    glVertex3f(-18.0f, 3.0f, 8.0f);
    glVertex3f(-15.0f, 3.0f, 8.0f);
    glVertex3f(-15.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(-18.0f, 0.0f, -7.0f);
    glVertex3f(-15.0f, 0.0f, -7.0f);
    glVertex3f(-15.0f, 0.0f, 8.0f);
    glVertex3f(-18.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(-18.0f, 0.0f, 8.0f);
    glVertex3f(-15.0f, 0.0f, 8.0f);
    glVertex3f(-15.0f, 3.0f, 8.0f);
    glVertex3f(-18.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(-18.0f, 0.0f, -7.0f);
    glVertex3f(-18.0f, 3.0f, -7.0f);
    glVertex3f(-15.0f, 3.0f, -7.0f);
    glVertex3f(-15.0f, 0.0f, -7.0f);

    // Left face (x = -15.0f)
    glVertex3f(-15.0f, 3.0f, -7.0f);
    glVertex3f(-15.0f, 0.0f, -7.0f);
    glVertex3f(-15.0f, 0.0f, 8.0f);
    glVertex3f(-15.0f, 3.0f, 8.0f);

    // Right face (x = -18.0f)
    glVertex3f(-18.0f, 3.0f, -7.0f);
    glVertex3f(-18.0f, 3.0f, 8.0f);
    glVertex3f(-18.0f, 0.0f, 8.0f);
    glVertex3f(-18.0f, 0.0f, -7.0f);
    glEnd();  // End of drawing D1

    // Draw the D1's edges
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 3.0f)
    glVertex3f(-18.0f, 3.0f, -7.0f);
    glVertex3f(-18.0f, 3.0f, 8.0f);
    glVertex3f(-15.0f, 3.0f, 8.0f);
    glVertex3f(-15.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(-18.0f, 0.0f, -7.0f);
    glVertex3f(-15.0f, 0.0f, -7.0f);
    glVertex3f(-15.0f, 0.0f, 8.0f);
    glVertex3f(-18.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(-18.0f, 0.0f, 8.0f);
    glVertex3f(-15.0f, 0.0f, 8.0f);
    glVertex3f(-15.0f, 3.0f, 8.0f);
    glVertex3f(-18.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(-18.0f, 0.0f, -7.0f);
    glVertex3f(-18.0f, 3.0f, -7.0f);
    glVertex3f(-15.0f, 3.0f, -7.0f);
    glVertex3f(-15.0f, 0.0f, -7.0f);

    // Left face (x = -15.0f)
    glVertex3f(-15.0f, 3.0f, -7.0f);
    glVertex3f(-15.0f, 0.0f, -7.0f);
    glVertex3f(-15.0f, 0.0f, 8.0f);
    glVertex3f(-15.0f, 3.0f, 8.0f);

    // Right face (x = -18.0f)
    glVertex3f(-18.0f, 3.0f, -7.0f);
    glVertex3f(-18.0f, 3.0f, 8.0f);
    glVertex3f(-18.0f, 0.0f, 8.0f);
    glVertex3f(-18.0f, 0.0f, -7.0f);

    glEnd();
}

void drawE1() {
    glBegin(GL_QUADS); // Draw the E1 key
    glColor3f(1.0f, 1.0f, 1.0f);

    // Top face (y = 3.0f)
    glVertex3f(-15.0f, 3.0f, -7.0f);
    glVertex3f(-15.0f, 3.0f, 8.0f);
    glVertex3f(-12.0f, 3.0f, 8.0f);
    glVertex3f(-12.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(-15.0f, 0.0f, -7.0f);
    glVertex3f(-12.0f, 0.0f, -7.0f);
    glVertex3f(-12.0f, 0.0f, 8.0f);
    glVertex3f(-15.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(-15.0f, 0.0f, 8.0f);
    glVertex3f(-12.0f, 0.0f, 8.0f);
    glVertex3f(-12.0f, 3.0f, 8.0f);
    glVertex3f(-15.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(-15.0f, 0.0f, -7.0f);
    glVertex3f(-15.0f, 3.0f, -7.0f);
    glVertex3f(-12.0f, 3.0f, -7.0f);
    glVertex3f(-12.0f, 0.0f, -7.0f);

    // Left face (x = -12.0f)
    glVertex3f(-12.0f, 3.0f, -7.0f);
    glVertex3f(-12.0f, 0.0f, -7.0f);
    glVertex3f(-12.0f, 0.0f, 8.0f);
    glVertex3f(-12.0f, 3.0f, 8.0f);

    // Right face (x = -15.0f)
    glVertex3f(-15.0f, 3.0f, -7.0f);
    glVertex3f(-15.0f, 3.0f, 8.0f);
    glVertex3f(-15.0f, 0.0f, 8.0f);
    glVertex3f(-15.0f, 0.0f, -7.0f);
    glEnd();  // End of drawing E1

    // Draw the E1's edges
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 3.0f)
    glVertex3f(-15.0f, 3.0f, -7.0f);
    glVertex3f(-15.0f, 3.0f, 8.0f);
    glVertex3f(-12.0f, 3.0f, 8.0f);
    glVertex3f(-12.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(-15.0f, 0.0f, -7.0f);
    glVertex3f(-12.0f, 0.0f, -7.0f);
    glVertex3f(-12.0f, 0.0f, 8.0f);
    glVertex3f(-15.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(-15.0f, 0.0f, 8.0f);
    glVertex3f(-12.0f, 0.0f, 8.0f);
    glVertex3f(-12.0f, 3.0f, 8.0f);
    glVertex3f(-15.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(-15.0f, 0.0f, -7.0f);
    glVertex3f(-15.0f, 3.0f, -7.0f);
    glVertex3f(-12.0f, 3.0f, -7.0f);
    glVertex3f(-12.0f, 0.0f, -7.0f);

    // Left face (x = -12.0f)
    glVertex3f(-12.0f, 3.0f, -7.0f);
    glVertex3f(-12.0f, 0.0f, -7.0f);
    glVertex3f(-12.0f, 0.0f, 8.0f);
    glVertex3f(-12.0f, 3.0f, 8.0f);

    // Right face (x = -15.0f)
    glVertex3f(-15.0f, 3.0f, -7.0f);
    glVertex3f(-15.0f, 3.0f, 8.0f);
    glVertex3f(-15.0f, 0.0f, 8.0f);
    glVertex3f(-15.0f, 0.0f, -7.0f);

    glEnd();
}

void drawF1() {
    glBegin(GL_QUADS); // Draw the F1 key
    glColor3f(1.0f, 1.0f, 1.0f);

    // Top face (y = 3.0f)
    glVertex3f(-12.0f, 3.0f, -7.0f);
    glVertex3f(-12.0f, 3.0f, 8.0f);
    glVertex3f(-9.0f, 3.0f, 8.0f);
    glVertex3f(-9.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(-12.0f, 0.0f, -7.0f);
    glVertex3f(-9.0f, 0.0f, -7.0f);
    glVertex3f(-9.0f, 0.0f, 8.0f);
    glVertex3f(-12.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(-12.0f, 0.0f, 8.0f);
    glVertex3f(-9.0f, 0.0f, 8.0f);
    glVertex3f(-9.0f, 3.0f, 8.0f);
    glVertex3f(-12.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(-12.0f, 0.0f, -7.0f);
    glVertex3f(-12.0f, 3.0f, -7.0f);
    glVertex3f(-9.0f, 3.0f, -7.0f);
    glVertex3f(-9.0f, 0.0f, -7.0f);

    // Left face (x = -9.0f)
    glVertex3f(-9.0f, 3.0f, -7.0f);
    glVertex3f(-9.0f, 0.0f, -7.0f);
    glVertex3f(-9.0f, 0.0f, 8.0f);
    glVertex3f(-9.0f, 3.0f, 8.0f);

    // Right face (x = -12.0f)
    glVertex3f(-12.0f, 3.0f, -7.0f);
    glVertex3f(-12.0f, 3.0f, 8.0f);
    glVertex3f(-12.0f, 0.0f, 8.0f);
    glVertex3f(-12.0f, 0.0f, -7.0f);
    glEnd();  // End of drawing F1

    // Draw the F1's edges
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 3.0f)
    glVertex3f(-12.0f, 3.0f, -7.0f);
    glVertex3f(-12.0f, 3.0f, 8.0f);
    glVertex3f(-9.0f, 3.0f, 8.0f);
    glVertex3f(-9.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(-12.0f, 0.0f, -7.0f);
    glVertex3f(-9.0f, 0.0f, -7.0f);
    glVertex3f(-9.0f, 0.0f, 8.0f);
    glVertex3f(-12.0f, 0.0f, 8.0f);

    // Front face  (z = 7.0f)
    glVertex3f(-12.0f, 0.0f, 8.0f);
    glVertex3f(-9.0f, 0.0f, 8.0f);
    glVertex3f(-9.0f, 3.0f, 8.0f);
    glVertex3f(-12.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(-12.0f, 0.0f, -7.0f);
    glVertex3f(-12.0f, 3.0f, -7.0f);
    glVertex3f(-9.0f, 3.0f, -7.0f);
    glVertex3f(-9.0f, 0.0f, -7.0f);

    // Left face (x = -9.0f)
    glVertex3f(-9.0f, 3.0f, -7.0f);
    glVertex3f(-9.0f, 0.0f, -7.0f);
    glVertex3f(-9.0f, 0.0f, 8.0f);
    glVertex3f(-9.0f, 3.0f, 8.0f);

    // Right face (x = -12.0f)
    glVertex3f(-12.0f, 3.0f, -7.0f);
    glVertex3f(-12.0f, 3.0f, 8.0f);
    glVertex3f(-12.0f, 0.0f, 8.0f);
    glVertex3f(-12.0f, 0.0f, -7.0f);

    glEnd();
}

void drawG1() {
    glBegin(GL_QUADS); // Draw the G1 key
    glColor3f(1.0f, 1.0f, 1.0f);

    // Top face (y = 3.0f)
    glVertex3f(-9.0f, 3.0f, -7.0f);
    glVertex3f(-9.0f, 3.0f, 8.0f);
    glVertex3f(-6.0f, 3.0f, 8.0f);
    glVertex3f(-6.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(-9.0f, 0.0f, -7.0f);
    glVertex3f(-6.0f, 0.0f, -7.0f);
    glVertex3f(-6.0f, 0.0f, 8.0f);
    glVertex3f(-9.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(-9.0f, 0.0f, 8.0f);
    glVertex3f(-6.0f, 0.0f, 8.0f);
    glVertex3f(-6.0f, 3.0f, 8.0f);
    glVertex3f(-9.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(-9.0f, 0.0f, -7.0f);
    glVertex3f(-9.0f, 3.0f, -7.0f);
    glVertex3f(-6.0f, 3.0f, -7.0f);
    glVertex3f(-6.0f, 0.0f, -7.0f);

    // Left face (x = -6.0f)
    glVertex3f(-6.0f, 3.0f, -7.0f);
    glVertex3f(-6.0f, 0.0f, -7.0f);
    glVertex3f(-6.0f, 0.0f, 8.0f);
    glVertex3f(-6.0f, 3.0f, 8.0f);

    // Right face (x = -9.0f)
    glVertex3f(-9.0f, 3.0f, -7.0f);
    glVertex3f(-9.0f, 3.0f, 8.0f);
    glVertex3f(-9.0f, 0.0f, 8.0f);
    glVertex3f(-9.0f, 0.0f, -7.0f);
    glEnd();  // End of drawing G1

    // Draw the G1's edges
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 3.0f)
    glVertex3f(-9.0f, 3.0f, -7.0f);
    glVertex3f(-9.0f, 3.0f, 8.0f);
    glVertex3f(-6.0f, 3.0f, 8.0f);
    glVertex3f(-6.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(-9.0f, 0.0f, -7.0f);
    glVertex3f(-6.0f, 0.0f, -7.0f);
    glVertex3f(-6.0f, 0.0f, 8.0f);
    glVertex3f(-9.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(-9.0f, 0.0f, 8.0f);
    glVertex3f(-6.0f, 0.0f, 8.0f);
    glVertex3f(-6.0f, 3.0f, 8.0f);
    glVertex3f(-9.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(-9.0f, 0.0f, -7.0f);
    glVertex3f(-9.0f, 3.0f, -7.0f);
    glVertex3f(-6.0f, 3.0f, -7.0f);
    glVertex3f(-6.0f, 0.0f, -7.0f);

    // Left face (x = -6.0f)
    glVertex3f(-6.0f, 3.0f, -7.0f);
    glVertex3f(-6.0f, 0.0f, -7.0f);
    glVertex3f(-6.0f, 0.0f, 8.0f);
    glVertex3f(-6.0f, 3.0f, 8.0f);

    // Right face (x = -9.0f)
    glVertex3f(-9.0f, 3.0f, -7.0f);
    glVertex3f(-9.0f, 3.0f, 8.0f);
    glVertex3f(-9.0f, 0.0f, 8.0f);
    glVertex3f(-9.0f, 0.0f, -7.0f);

    glEnd();
}

void drawA1() {
    glBegin(GL_QUADS); // Draw the A1 key
    glColor3f(1.0f, 1.0f, 1.0f);

    // Top face (y = 3.0f)
    glVertex3f(-6.0f, 3.0f, -7.0f);
    glVertex3f(-6.0f, 3.0f, 8.0f);
    glVertex3f(-3.0f, 3.0f, 8.0f);
    glVertex3f(-3.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(-6.0f, 0.0f, -7.0f);
    glVertex3f(-3.0f, 0.0f, -7.0f);
    glVertex3f(-3.0f, 0.0f, 8.0f);
    glVertex3f(-6.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(-6.0f, 0.0f, 8.0f);
    glVertex3f(-3.0f, 0.0f, 8.0f);
    glVertex3f(-3.0f, 3.0f, 8.0f);
    glVertex3f(-6.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(-6.0f, 0.0f, -7.0f);
    glVertex3f(-6.0f, 3.0f, -7.0f);
    glVertex3f(-3.0f, 3.0f, -7.0f);
    glVertex3f(-3.0f, 0.0f, -7.0f);

    // Left face (x = -3.0f)
    glVertex3f(-3.0f, 3.0f, -7.0f);
    glVertex3f(-3.0f, 0.0f, -7.0f);
    glVertex3f(-3.0f, 0.0f, 8.0f);
    glVertex3f(-3.0f, 3.0f, 8.0f);

    // Right face (x = -6.0f)
    glVertex3f(-6.0f, 3.0f, -7.0f);
    glVertex3f(-6.0f, 3.0f, 8.0f);
    glVertex3f(-6.0f, 0.0f, 8.0f);
    glVertex3f(-6.0f, 0.0f, -7.0f);
    glEnd();  // End of drawing A1

    // Draw the A1's edges
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 3.0f)
    glVertex3f(-6.0f, 3.0f, -7.0f);
    glVertex3f(-6.0f, 3.0f, 8.0f);
    glVertex3f(-3.0f, 3.0f, 8.0f);
    glVertex3f(-3.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(-6.0f, 0.0f, -7.0f);
    glVertex3f(-3.0f, 0.0f, -7.0f);
    glVertex3f(-3.0f, 0.0f, 8.0f);
    glVertex3f(-6.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(-6.0f, 0.0f, 8.0f);
    glVertex3f(-3.0f, 0.0f, 8.0f);
    glVertex3f(-3.0f, 3.0f, 8.0f);
    glVertex3f(-6.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(-6.0f, 0.0f, -7.0f);
    glVertex3f(-6.0f, 3.0f, -7.0f);
    glVertex3f(-3.0f, 3.0f, -7.0f);
    glVertex3f(-3.0f, 0.0f, -7.0f);

    // Left face (x = -3.0f)
    glVertex3f(-3.0f, 3.0f, -7.0f);
    glVertex3f(-3.0f, 0.0f, -7.0f);
    glVertex3f(-3.0f, 0.0f, 8.0f);
    glVertex3f(-3.0f, 3.0f, 8.0f);

    // Right face (x = -6.0f)
    glVertex3f(-6.0f, 3.0f, -7.0f);
    glVertex3f(-6.0f, 3.0f, 8.0f);
    glVertex3f(-6.0f, 0.0f, 8.0f);
    glVertex3f(-6.0f, 0.0f, -7.0f);

    glEnd();
}

void drawB1() {
    glBegin(GL_QUADS); // Draw the B1 key
    glColor3f(1.0f, 1.0f, 1.0f);

    // Top face (y = 3.0f)
    glVertex3f(-3.0f, 3.0f, -7.0f);
    glVertex3f(-3.0f, 3.0f, 8.0f);
    glVertex3f(0.0f, 3.0f, 8.0f);
    glVertex3f(0.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(-3.0f, 0.0f, -7.0f);
    glVertex3f(0.0f, 0.0f, -7.0f);
    glVertex3f(0.0f, 0.0f, 8.0f);
    glVertex3f(-3.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(-3.0f, 0.0f, 8.0f);
    glVertex3f(0.0f, 0.0f, 8.0f);
    glVertex3f(0.0f, 3.0f, 8.0f);
    glVertex3f(-3.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(-3.0f, 0.0f, -7.0f);
    glVertex3f(-3.0f, 3.0f, -7.0f);
    glVertex3f(0.0f, 3.0f, -7.0f);
    glVertex3f(0.0f, 0.0f, -7.0f);

    // Left face (x = 0.0f)
    glVertex3f(0.0f, 3.0f, -7.0f);
    glVertex3f(0.0f, 0.0f, -7.0f);
    glVertex3f(0.0f, 0.0f, 8.0f);
    glVertex3f(0.0f, 3.0f, 8.0f);

    // Right face (x = -3.0f)
    glVertex3f(-3.0f, 3.0f, -7.0f);
    glVertex3f(-3.0f, 3.0f, 8.0f);
    glVertex3f(-3.0f, 0.0f, 8.0f);
    glVertex3f(-3.0f, 0.0f, -7.0f);
    glEnd();  // End of drawing B1

    // Draw the B1's edges
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 3.0f)
    glVertex3f(-3.0f, 3.0f, -7.0f);
    glVertex3f(-3.0f, 3.0f, 8.0f);
    glVertex3f(0.0f, 3.0f, 8.0f);
    glVertex3f(0.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(-3.0f, 0.0f, -7.0f);
    glVertex3f(0.0f, 0.0f, -7.0f);
    glVertex3f(0.0f, 0.0f, 8.0f);
    glVertex3f(-3.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(-3.0f, 0.0f, 8.0f);
    glVertex3f(0.0f, 0.0f, 8.0f);
    glVertex3f(0.0f, 3.0f, 8.0f);
    glVertex3f(-3.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(-3.0f, 0.0f, -7.0f);
    glVertex3f(-3.0f, 3.0f, -7.0f);
    glVertex3f(0.0f, 3.0f, -7.0f);
    glVertex3f(0.0f, 0.0f, -7.0f);

    // Left face (x = 0.0f)
    glVertex3f(0.0f, 3.0f, -7.0f);
    glVertex3f(0.0f, 0.0f, -7.0f);
    glVertex3f(0.0f, 0.0f, 8.0f);
    glVertex3f(0.0f, 3.0f, 8.0f);

    // Right face (x = -3.0f)
    glVertex3f(-3.0f, 3.0f, -7.0f);
    glVertex3f(-3.0f, 3.0f, 8.0f);
    glVertex3f(-3.0f, 0.0f, 8.0f);
    glVertex3f(-3.0f, 0.0f, -7.0f);

    glEnd();
}

void drawC2() {
    glBegin(GL_QUADS); // Draw the C2 key
    glColor3f(1.0f, 1.0f, 1.0f);

    // Top face (y = 3.0f)
    glVertex3f(0.0f, 3.0f, -7.0f);
    glVertex3f(0.0f, 3.0f, 8.0f);
    glVertex3f(3.0f, 3.0f, 8.0f);
    glVertex3f(3.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(0.0f, 0.0f, -7.0f);
    glVertex3f(3.0f, 0.0f, -7.0f);
    glVertex3f(3.0f, 0.0f, 8.0f);
    glVertex3f(0.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(0.0f, 0.0f, 8.0f);
    glVertex3f(3.0f, 0.0f, 8.0f);
    glVertex3f(3.0f, 3.0f, 8.0f);
    glVertex3f(0.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(0.0f, 0.0f, -7.0f);
    glVertex3f(0.0f, 3.0f, -7.0f);
    glVertex3f(3.0f, 3.0f, -7.0f);
    glVertex3f(3.0f, 0.0f, -7.0f);

    // Left face (x = 3.0f)
    glVertex3f(3.0f, 3.0f, -7.0f);
    glVertex3f(3.0f, 0.0f, -7.0f);
    glVertex3f(3.0f, 0.0f, 8.0f);
    glVertex3f(3.0f, 3.0f, 8.0f);

    // Right face (x = 0.0f)
    glVertex3f(0.0f, 3.0f, -7.0f);
    glVertex3f(0.0f, 3.0f, 8.0f);
    glVertex3f(0.0f, 0.0f, 8.0f);
    glVertex3f(0.0f, 0.0f, -7.0f);
    glEnd();  // End of drawing C2

    // Draw the C2's edges
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 3.0f)
    glVertex3f(0.0f, 3.0f, -7.0f);
    glVertex3f(0.0f, 3.0f, 8.0f);
    glVertex3f(3.0f, 3.0f, 8.0f);
    glVertex3f(3.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(0.0f, 0.0f, -7.0f);
    glVertex3f(3.0f, 0.0f, -7.0f);
    glVertex3f(3.0f, 0.0f, 8.0f);
    glVertex3f(0.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(0.0f, 0.0f, 8.0f);
    glVertex3f(3.0f, 0.0f, 8.0f);
    glVertex3f(3.0f, 3.0f, 8.0f);
    glVertex3f(0.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(0.0f, 0.0f, -7.0f);
    glVertex3f(0.0f, 3.0f, -7.0f);
    glVertex3f(3.0f, 3.0f, -7.0f);
    glVertex3f(3.0f, 0.0f, -7.0f);

    // Left face (x = 3.0f)
    glVertex3f(3.0f, 3.0f, -7.0f);
    glVertex3f(3.0f, 0.0f, -7.0f);
    glVertex3f(3.0f, 0.0f, 8.0f);
    glVertex3f(3.0f, 3.0f, 8.0f);

    // Right face (x = 0.0f)
    glVertex3f(0.0f, 3.0f, -7.0f);
    glVertex3f(0.0f, 3.0f, 8.0f);
    glVertex3f(0.0f, 0.0f, 8.0f);
    glVertex3f(0.0f, 0.0f, -7.0f);

    glEnd();
}

void drawD2() {
    glBegin(GL_QUADS); // Draw the D2 key
    glColor3f(1.0f, 1.0f, 1.0f);

    // Top face (y = 3.0f)
    glVertex3f(3.0f, 3.0f, -7.0f);
    glVertex3f(3.0f, 3.0f, 8.0f);
    glVertex3f(6.0f, 3.0f, 8.0f);
    glVertex3f(6.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(3.0f, 0.0f, -7.0f);
    glVertex3f(6.0f, 0.0f, -7.0f);
    glVertex3f(6.0f, 0.0f, 8.0f);
    glVertex3f(3.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(3.0f, 0.0f, 8.0f);
    glVertex3f(6.0f, 0.0f, 8.0f);
    glVertex3f(6.0f, 3.0f, 8.0f);
    glVertex3f(3.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(3.0f, 0.0f, -7.0f);
    glVertex3f(3.0f, 3.0f, -7.0f);
    glVertex3f(6.0f, 3.0f, -7.0f);
    glVertex3f(6.0f, 0.0f, -7.0f);

    // Left face (x = 6.0f)
    glVertex3f(6.0f, 3.0f, -7.0f);
    glVertex3f(6.0f, 0.0f, -7.0f);
    glVertex3f(6.0f, 0.0f, 8.0f);
    glVertex3f(6.0f, 3.0f, 8.0f);

    // Right face (x = 3.0f)
    glVertex3f(3.0f, 3.0f, -7.0f);
    glVertex3f(3.0f, 3.0f, 8.0f);
    glVertex3f(3.0f, 0.0f, 8.0f);
    glVertex3f(3.0f, 0.0f, -7.0f);
    glEnd();  // End of drawing D2

    // Draw the D2 key
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 3.0f)
    glVertex3f(3.0f, 3.0f, -7.0f);
    glVertex3f(3.0f, 3.0f, 8.0f);
    glVertex3f(6.0f, 3.0f, 8.0f);
    glVertex3f(6.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(3.0f, 0.0f, -7.0f);
    glVertex3f(6.0f, 0.0f, -7.0f);
    glVertex3f(6.0f, 0.0f, 8.0f);
    glVertex3f(3.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(3.0f, 0.0f, 8.0f);
    glVertex3f(6.0f, 0.0f, 8.0f);
    glVertex3f(6.0f, 3.0f, 8.0f);
    glVertex3f(3.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(3.0f, 0.0f, -7.0f);
    glVertex3f(3.0f, 3.0f, -7.0f);
    glVertex3f(6.0f, 3.0f, -7.0f);
    glVertex3f(6.0f, 0.0f, -7.0f);

    // Left face (x = 6.0f)
    glVertex3f(6.0f, 3.0f, -7.0f);
    glVertex3f(6.0f, 0.0f, -7.0f);
    glVertex3f(6.0f, 0.0f, 8.0f);
    glVertex3f(6.0f, 3.0f, 8.0f);

    // Right face (x = 3.0f)
    glVertex3f(3.0f, 3.0f, -7.0f);
    glVertex3f(3.0f, 3.0f, 8.0f);
    glVertex3f(3.0f, 0.0f, 8.0f);
    glVertex3f(3.0f, 0.0f, -7.0f);

    glEnd();
}

void drawE2() {
    glBegin(GL_QUADS); // Draw the E2 key
    glColor3f(1.0f, 1.0f, 1.0f);

    // Top face (y = 3.0f)
    glVertex3f(6.0f, 3.0f, -7.0f);
    glVertex3f(6.0f, 3.0f, 8.0f);
    glVertex3f(9.0f, 3.0f, 8.0f);
    glVertex3f(9.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(6.0f, 0.0f, -7.0f);
    glVertex3f(9.0f, 0.0f, -7.0f);
    glVertex3f(9.0f, 0.0f, 8.0f);
    glVertex3f(6.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(6.0f, 0.0f, 8.0f);
    glVertex3f(9.0f, 0.0f, 8.0f);
    glVertex3f(9.0f, 3.0f, 8.0f);
    glVertex3f(6.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(6.0f, 0.0f, -7.0f);
    glVertex3f(6.0f, 3.0f, -7.0f);
    glVertex3f(9.0f, 3.0f, -7.0f);
    glVertex3f(9.0f, 0.0f, -7.0f);

    // Left face (x = 9.0f)
    glVertex3f(9.0f, 3.0f, -7.0f);
    glVertex3f(9.0f, 0.0f, -7.0f);
    glVertex3f(9.0f, 0.0f, 8.0f);
    glVertex3f(9.0f, 3.0f, 8.0f);

    // Right face (x = 6.0f)
    glVertex3f(6.0f, 3.0f, -7.0f);
    glVertex3f(6.0f, 3.0f, 8.0f);
    glVertex3f(6.0f, 0.0f, 8.0f);
    glVertex3f(6.0f, 0.0f, -7.0f);
    glEnd();  // End of drawing E2

    // Draw the E2's edges
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 3.0f)
    glVertex3f(6.0f, 3.0f, -7.0f);
    glVertex3f(6.0f, 3.0f, 8.0f);
    glVertex3f(9.0f, 3.0f, 8.0f);
    glVertex3f(9.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(6.0f, 0.0f, -7.0f);
    glVertex3f(9.0f, 0.0f, -7.0f);
    glVertex3f(9.0f, 0.0f, 8.0f);
    glVertex3f(6.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(6.0f, 0.0f, 8.0f);
    glVertex3f(9.0f, 0.0f, 8.0f);
    glVertex3f(9.0f, 3.0f, 8.0f);
    glVertex3f(6.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(6.0f, 0.0f, -7.0f);
    glVertex3f(6.0f, 3.0f, -7.0f);
    glVertex3f(9.0f, 3.0f, -7.0f);
    glVertex3f(9.0f, 0.0f, -7.0f);

    // Left face (x = 9.0f)
    glVertex3f(9.0f, 3.0f, -7.0f);
    glVertex3f(9.0f, 0.0f, -7.0f);
    glVertex3f(9.0f, 0.0f, 8.0f);
    glVertex3f(9.0f, 3.0f, 8.0f);

    // Right face (x = 6.0f)
    glVertex3f(6.0f, 3.0f, -7.0f);
    glVertex3f(6.0f, 3.0f, 8.0f);
    glVertex3f(6.0f, 0.0f, 8.0f);
    glVertex3f(6.0f, 0.0f, -7.0f);

    glEnd();
}

void drawF2() {
    glBegin(GL_QUADS); // Draw the F2 key
    glColor3f(1.0f, 1.0f, 1.0f);

    // Top face (y = 3.0f)
    glVertex3f(9.0f, 3.0f, -7.0f);
    glVertex3f(9.0f, 3.0f, 8.0f);
    glVertex3f(12.0f, 3.0f, 8.0f);
    glVertex3f(12.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(9.0f, 0.0f, -7.0f);
    glVertex3f(12.0f, 0.0f, -7.0f);
    glVertex3f(12.0f, 0.0f, 8.0f);
    glVertex3f(9.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(9.0f, 0.0f, 8.0f);
    glVertex3f(12.0f, 0.0f, 8.0f);
    glVertex3f(12.0f, 3.0f, 8.0f);
    glVertex3f(9.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(9.0f, 0.0f, -7.0f);
    glVertex3f(9.0f, 3.0f, -7.0f);
    glVertex3f(12.0f, 3.0f, -7.0f);
    glVertex3f(12.0f, 0.0f, -7.0f);

    // Left face (x = 12.0f)
    glVertex3f(12.0f, 3.0f, -7.0f);
    glVertex3f(12.0f, 0.0f, -7.0f);
    glVertex3f(12.0f, 0.0f, 8.0f);
    glVertex3f(12.0f, 3.0f, 8.0f);

    // Right face (x = 9.0f)
    glVertex3f(9.0f, 3.0f, -7.0f);
    glVertex3f(9.0f, 3.0f, 8.0f);
    glVertex3f(9.0f, 0.0f, 8.0f);
    glVertex3f(9.0f, 0.0f, -7.0f);
    glEnd();  // End of drawing F2

    // Draw the F2's edges
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 3.0f)
    glVertex3f(9.0f, 3.0f, -7.0f);
    glVertex3f(9.0f, 3.0f, 8.0f);
    glVertex3f(12.0f, 3.0f, 8.0f);
    glVertex3f(12.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(9.0f, 0.0f, -7.0f);
    glVertex3f(12.0f, 0.0f, -7.0f);
    glVertex3f(12.0f, 0.0f, 8.0f);
    glVertex3f(9.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(9.0f, 0.0f, 8.0f);
    glVertex3f(12.0f, 0.0f, 8.0f);
    glVertex3f(12.0f, 3.0f, 8.0f);
    glVertex3f(9.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(9.0f, 0.0f, -7.0f);
    glVertex3f(9.0f, 3.0f, -7.0f);
    glVertex3f(12.0f, 3.0f, -7.0f);
    glVertex3f(12.0f, 0.0f, -7.0f);

    // Left face (x = 12.0f)
    glVertex3f(12.0f, 3.0f, -7.0f);
    glVertex3f(12.0f, 0.0f, -7.0f);
    glVertex3f(12.0f, 0.0f, 8.0f);
    glVertex3f(12.0f, 3.0f, 8.0f);

    // Right face (x = 9.0f)
    glVertex3f(9.0f, 3.0f, -7.0f);
    glVertex3f(9.0f, 3.0f, 8.0f);
    glVertex3f(9.0f, 0.0f, 8.0f);
    glVertex3f(9.0f, 0.0f, -7.0f);

    glEnd();
}

void drawG2() {
    glBegin(GL_QUADS); // Draw the G2 key
    glColor3f(1.0f, 1.0f, 1.0f);

    // Top face (y = 3.0f)
    glVertex3f(12.0f, 3.0f, -7.0f);
    glVertex3f(12.0f, 3.0f, 8.0f);
    glVertex3f(15.0f, 3.0f, 8.0f);
    glVertex3f(15.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(12.0f, 0.0f, -7.0f);
    glVertex3f(15.0f, 0.0f, -7.0f);
    glVertex3f(15.0f, 0.0f, 8.0f);
    glVertex3f(12.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(12.0f, 0.0f, 8.0f);
    glVertex3f(15.0f, 0.0f, 8.0f);
    glVertex3f(15.0f, 3.0f, 8.0f);
    glVertex3f(12.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(12.0f, 0.0f, -7.0f);
    glVertex3f(12.0f, 3.0f, -7.0f);
    glVertex3f(15.0f, 3.0f, -7.0f);
    glVertex3f(15.0f, 0.0f, -7.0f);

    // Left face (x = 15.0f)
    glVertex3f(15.0f, 3.0f, -7.0f);
    glVertex3f(15.0f, 0.0f, -7.0f);
    glVertex3f(15.0f, 0.0f, 8.0f);
    glVertex3f(15.0f, 3.0f, 8.0f);

    // Right face (x = 12.0f)
    glVertex3f(12.0f, 3.0f, -7.0f);
    glVertex3f(12.0f, 3.0f, 8.0f);
    glVertex3f(12.0f, 0.0f, 8.0f);
    glVertex3f(12.0f, 0.0f, -7.0f);
    glEnd();  // End of drawing G2

    // Draw the G2's edges
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 3.0f)
    glVertex3f(12.0f, 3.0f, -7.0f);
    glVertex3f(12.0f, 3.0f, 8.0f);
    glVertex3f(15.0f, 3.0f, 8.0f);
    glVertex3f(15.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(12.0f, 0.0f, -7.0f);
    glVertex3f(15.0f, 0.0f, -7.0f);
    glVertex3f(15.0f, 0.0f, 8.0f);
    glVertex3f(12.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(12.0f, 0.0f, 8.0f);
    glVertex3f(15.0f, 0.0f, 8.0f);
    glVertex3f(15.0f, 3.0f, 8.0f);
    glVertex3f(12.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(12.0f, 0.0f, -7.0f);
    glVertex3f(12.0f, 3.0f, -7.0f);
    glVertex3f(15.0f, 3.0f, -7.0f);
    glVertex3f(15.0f, 0.0f, -7.0f);

    // Left face (x = 15.0f)
    glVertex3f(15.0f, 3.0f, -7.0f);
    glVertex3f(15.0f, 0.0f, -7.0f);
    glVertex3f(15.0f, 0.0f, 8.0f);
    glVertex3f(15.0f, 3.0f, 8.0f);

    // Right face (x = 12.0f)
    glVertex3f(12.0f, 3.0f, -7.0f);
    glVertex3f(12.0f, 3.0f, 8.0f);
    glVertex3f(12.0f, 0.0f, 8.0f);
    glVertex3f(12.0f, 0.0f, -7.0f);

    glEnd();
}

void drawA2() {
    glBegin(GL_QUADS); // Draw the A2 key
    glColor3f(1.0f, 1.0f, 1.0f);

    // Top face (y = 3.0f)
    glVertex3f(15.0f, 3.0f, -7.0f);
    glVertex3f(15.0f, 3.0f, 8.0f);
    glVertex3f(18.0f, 3.0f, 8.0f);
    glVertex3f(18.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(15.0f, 0.0f, -7.0f);
    glVertex3f(18.0f, 0.0f, -7.0f);
    glVertex3f(18.0f, 0.0f, 8.0f);
    glVertex3f(15.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(15.0f, 0.0f, 8.0f);
    glVertex3f(18.0f, 0.0f, 8.0f);
    glVertex3f(18.0f, 3.0f, 8.0f);
    glVertex3f(15.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(15.0f, 0.0f, -7.0f);
    glVertex3f(15.0f, 3.0f, -7.0f);
    glVertex3f(18.0f, 3.0f, -7.0f);
    glVertex3f(18.0f, 0.0f, -7.0f);

    // Left face (x = 18.0f)
    glVertex3f(18.0f, 3.0f, -7.0f);
    glVertex3f(18.0f, 0.0f, -7.0f);
    glVertex3f(18.0f, 0.0f, 8.0f);
    glVertex3f(18.0f, 3.0f, 8.0f);

    // Right face (x = 15.0f)
    glVertex3f(15.0f, 3.0f, -7.0f);
    glVertex3f(15.0f, 3.0f, 8.0f);
    glVertex3f(15.0f, 0.0f, 8.0f);
    glVertex3f(15.0f, 0.0f, -7.0f);
    glEnd();  // End of drawing A2

    // Draw the A2's edges
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 3.0f)
    glVertex3f(15.0f, 3.0f, -7.0f);
    glVertex3f(15.0f, 3.0f, 8.0f);
    glVertex3f(18.0f, 3.0f, 8.0f);
    glVertex3f(18.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(15.0f, 0.0f, -7.0f);
    glVertex3f(18.0f, 0.0f, -7.0f);
    glVertex3f(18.0f, 0.0f, 8.0f);
    glVertex3f(15.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(15.0f, 0.0f, 8.0f);
    glVertex3f(18.0f, 0.0f, 8.0f);
    glVertex3f(18.0f, 3.0f, 8.0f);
    glVertex3f(15.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(15.0f, 0.0f, -7.0f);
    glVertex3f(15.0f, 3.0f, -7.0f);
    glVertex3f(18.0f, 3.0f, -7.0f);
    glVertex3f(18.0f, 0.0f, -7.0f);

    // Left face (x = 18.0f)
    glVertex3f(18.0f, 3.0f, -7.0f);
    glVertex3f(18.0f, 0.0f, -7.0f);
    glVertex3f(18.0f, 0.0f, 8.0f);
    glVertex3f(18.0f, 3.0f, 8.0f);

    // Right face (x = 15.0f)
    glVertex3f(15.0f, 3.0f, -7.0f);
    glVertex3f(15.0f, 3.0f, 8.0f);
    glVertex3f(15.0f, 0.0f, 8.0f);
    glVertex3f(15.0f, 0.0f, -7.0f);

    glEnd();
}

void drawB2() {
    glBegin(GL_QUADS); // Draw the B2 key
    glColor3f(1.0f, 1.0f, 1.0f);

    // Top face (y = 3.0f)
    glVertex3f(18.0f, 3.0f, -7.0f);
    glVertex3f(18.0f, 3.0f, 8.0f);
    glVertex3f(21.0f, 3.0f, 8.0f);
    glVertex3f(21.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(18.0f, 0.0f, -7.0f);
    glVertex3f(21.0f, 0.0f, -7.0f);
    glVertex3f(21.0f, 0.0f, 8.0f);
    glVertex3f(18.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(18.0f, 0.0f, 8.0f);
    glVertex3f(21.0f, 0.0f, 8.0f);
    glVertex3f(21.0f, 3.0f, 8.0f);
    glVertex3f(18.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(18.0f, 0.0f, -7.0f);
    glVertex3f(18.0f, 3.0f, -7.0f);
    glVertex3f(21.0f, 3.0f, -7.0f);
    glVertex3f(21.0f, 0.0f, -7.0f);

    // Left face (x = 21.0f)
    glVertex3f(21.0f, 3.0f, -7.0f);
    glVertex3f(21.0f, 0.0f, -7.0f);
    glVertex3f(21.0f, 0.0f, 8.0f);
    glVertex3f(21.0f, 3.0f, 8.0f);

    // Right face (x = 18.0f)
    glVertex3f(18.0f, 3.0f, -7.0f);
    glVertex3f(18.0f, 3.0f, 8.0f);
    glVertex3f(18.0f, 0.0f, 8.0f);
    glVertex3f(18.0f, 0.0f, -7.0f);
    glEnd();  // End of drawing B2

    // Draw the B2's edges
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 3.0f)
    glVertex3f(18.0f, 3.0f, -7.0f);
    glVertex3f(18.0f, 3.0f, 8.0f);
    glVertex3f(21.0f, 3.0f, 8.0f);
    glVertex3f(21.0f, 3.0f, -7.0f);

    // Bottom face (y = 0.0f)
    glVertex3f(18.0f, 0.0f, -7.0f);
    glVertex3f(21.0f, 0.0f, -7.0f);
    glVertex3f(21.0f, 0.0f, 8.0f);
    glVertex3f(18.0f, 0.0f, 8.0f);

    // Front face  (z = 8.0f)
    glVertex3f(18.0f, 0.0f, 8.0f);
    glVertex3f(21.0f, 0.0f, 8.0f);
    glVertex3f(21.0f, 3.0f, 8.0f);
    glVertex3f(18.0f, 3.0f, 8.0f);

    // Back face (z = -7.0f)
    glVertex3f(18.0f, 0.0f, -7.0f);
    glVertex3f(18.0f, 3.0f, -7.0f);
    glVertex3f(21.0f, 3.0f, -7.0f);
    glVertex3f(21.0f, 0.0f, -7.0f);

    // Left face (x = 21.0f)
    glVertex3f(21.0f, 3.0f, -7.0f);
    glVertex3f(21.0f, 0.0f, -7.0f);
    glVertex3f(21.0f, 0.0f, 8.0f);
    glVertex3f(21.0f, 3.0f, 8.0f);

    // Right face (x = 18.0f)
    glVertex3f(18.0f, 3.0f, -7.0f);
    glVertex3f(18.0f, 3.0f, 8.0f);
    glVertex3f(18.0f, 0.0f, 8.0f);
    glVertex3f(18.0f, 0.0f, -7.0f);

    glEnd();
}

void drawDb1() {
    glBegin(GL_QUADS); // Draw the Db1 key
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 4.0f)
    glVertex3f(-19.0f, 4.0f, -7.0f);
    glVertex3f(-19.0f, 4.0f, 0.0f);
    glVertex3f(-17.0f, 4.0f, 0.0f);
    glVertex3f(-17.0f, 4.0f, -7.0f);

    // Bottom face (y = 3.0f)
    glVertex3f(-19.0f, 3.0f, -7.0f);
    glVertex3f(-17.0f, 3.0f, -7.0f);
    glVertex3f(-17.0f, 3.0f, 0.0f);
    glVertex3f(-19.0f, 3.0f, 0.0f);

    // Front face  (z = 0.0f)
    glVertex3f(-19.0f, 3.0f, 0.0f);
    glVertex3f(-17.0f, 3.0f, 0.0f);
    glVertex3f(-17.0f, 4.0f, 0.0f);
    glVertex3f(-19.0f, 4.0f, 0.0f);

    // Back face (z = -7.0f)
    glVertex3f(-19.0f, 3.0f, -7.0f);
    glVertex3f(-19.0f, 4.0f, -7.0f);
    glVertex3f(-17.0f, 4.0f, -7.0f);
    glVertex3f(-17.0f, 3.0f, -7.0f);

    // Left face (x = -17.0f)
    glVertex3f(-17.0f, 4.0f, -7.0f);
    glVertex3f(-17.0f, 3.0f, -7.0f);
    glVertex3f(-17.0f, 3.0f, 0.0f);
    glVertex3f(-17.0f, 4.0f, 0.0f);

    // Right face (x = 18.0f)
    glVertex3f(-19.0f, 4.0f, -7.0f);
    glVertex3f(-19.0f, 4.0f, 0.0f);
    glVertex3f(-19.0f, 3.0f, 0.0f);
    glVertex3f(-19.0f, 3.0f, -7.0f);
    glEnd();  // End of drawing Db1
}

void drawEb1() {
    glBegin(GL_QUADS); // Draw the Eb1 key
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 4.0f)
    glVertex3f(-16.0f, 4.0f, -7.0f);
    glVertex3f(-16.0f, 4.0f, 0.0f);
    glVertex3f(-14.0f, 4.0f, 0.0f);
    glVertex3f(-14.0f, 4.0f, -7.0f);

    // Bottom face (y = 3.0f)
    glVertex3f(-16.0f, 3.0f, -7.0f);
    glVertex3f(-14.0f, 3.0f, -7.0f);
    glVertex3f(-14.0f, 3.0f, 0.0f);
    glVertex3f(-16.0f, 3.0f, 0.0f);

    // Front face  (z = 7.0f)
    glVertex3f(-16.0f, 3.0f, 0.0f);
    glVertex3f(-14.0f, 3.0f, 0.0f);
    glVertex3f(-14.0f, 4.0f, 0.0f);
    glVertex3f(-16.0f, 4.0f, 0.0f);

    // Back face (z = -7.0f)
    glVertex3f(-16.0f, 3.0f, -7.0f);
    glVertex3f(-16.0f, 4.0f, -7.0f);
    glVertex3f(-14.0f, 4.0f, -7.0f);
    glVertex3f(-14.0f, 3.0f, -7.0f);

    // Left face (x = -16.0f)
    glVertex3f(-16.0f, 4.0f, -7.0f);
    glVertex3f(-16.0f, 3.0f, -7.0f);
    glVertex3f(-16.0f, 3.0f, 0.0f);
    glVertex3f(-16.0f, 4.0f, 0.0f);

    // Right face (x = 14.0f)
    glVertex3f(-14.0f, 4.0f, -7.0f);
    glVertex3f(-14.0f, 4.0f, 0.0f);
    glVertex3f(-14.0f, 3.0f, 0.0f);
    glVertex3f(-14.0f, 3.0f, -7.0f);
    glEnd();  // End of drawing Eb1
}

void drawGb1() {
    glBegin(GL_QUADS); // Draw the Gb1 key
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 4.0f)
    glVertex3f(-10.0f, 4.0f, -7.0f);
    glVertex3f(-10.0f, 4.0f, 0.0f);
    glVertex3f(-8.0f, 4.0f, 0.0f);
    glVertex3f(-8.0f, 4.0f, -7.0f);

    // Bottom face (y = 3.0f)
    glVertex3f(-10.0f, 3.0f, -7.0f);
    glVertex3f(-8.0f, 3.0f, -7.0f);
    glVertex3f(-8.0f, 3.0f, 0.0f);
    glVertex3f(-10.0f, 3.0f, 0.0f);

    // Front face  (z = 7.0f)
    glVertex3f(-10.0f, 3.0f, 0.0f);
    glVertex3f(-8.0f, 3.0f, 0.0f);
    glVertex3f(-8.0f, 4.0f, 0.0f);
    glVertex3f(-10.0f, 4.0f, 0.0f);

    // Back face (z = -7.0f)
    glVertex3f(-10.0f, 3.0f, -7.0f);
    glVertex3f(-10.0f, 4.0f, -7.0f);
    glVertex3f(-8.0f, 4.0f, -7.0f);
    glVertex3f(-8.0f, 3.0f, -7.0f);

    // Left face (x = -16.0f)
    glVertex3f(-10.0f, 4.0f, -7.0f);
    glVertex3f(-10.0f, 3.0f, -7.0f);
    glVertex3f(-10.0f, 3.0f, 0.0f);
    glVertex3f(-10.0f, 4.0f, 0.0f);

    // Right face (x = 14.0f)
    glVertex3f(-8.0f, 4.0f, -7.0f);
    glVertex3f(-8.0f, 4.0f, 0.0f);
    glVertex3f(-8.0f, 3.0f, 0.0f);
    glVertex3f(-8.0f, 3.0f, -7.0f);
    glEnd();  // End of drawing Gb1
}

void drawAb1() {
    glBegin(GL_QUADS); // Draw the Ab1 key
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 4.0f)
    glVertex3f(-7.0f, 4.0f, -7.0f);
    glVertex3f(-7.0f, 4.0f, 0.0f);
    glVertex3f(-5.0f, 4.0f, 0.0f);
    glVertex3f(-5.0f, 4.0f, -7.0f);

    // Bottom face (y = 3.0f)
    glVertex3f(-7.0f, 3.0f, -7.0f);
    glVertex3f(-5.0f, 3.0f, -7.0f);
    glVertex3f(-5.0f, 3.0f, 0.0f);
    glVertex3f(-7.0f, 3.0f, 0.0f);

    // Front face  (z = 7.0f)
    glVertex3f(-7.0f, 3.0f, 0.0f);
    glVertex3f(-5.0f, 3.0f, 0.0f);
    glVertex3f(-5.0f, 4.0f, 0.0f);
    glVertex3f(-7.0f, 4.0f, 0.0f);

    // Back face (z = -7.0f)
    glVertex3f(-7.0f, 3.0f, -7.0f);
    glVertex3f(-7.0f, 4.0f, -7.0f);
    glVertex3f(-5.0f, 4.0f, -7.0f);
    glVertex3f(-5.0f, 3.0f, -7.0f);

    // Left face (x = -16.0f)
    glVertex3f(-7.0f, 4.0f, -7.0f);
    glVertex3f(-7.0f, 3.0f, -7.0f);
    glVertex3f(-7.0f, 3.0f, 0.0f);
    glVertex3f(-7.0f, 4.0f, 0.0f);

    // Right face (x = 14.0f)
    glVertex3f(-5.0f, 4.0f, -7.0f);
    glVertex3f(-5.0f, 4.0f, 0.0f);
    glVertex3f(-5.0f, 3.0f, 0.0f);
    glVertex3f(-5.0f, 3.0f, -7.0f);
    glEnd();  // End of drawing Ab1
}

void drawBb1() {
    glBegin(GL_QUADS); // Draw the Bb1 key
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 4.0f)
    glVertex3f(-4.0f, 4.0f, -7.0f);
    glVertex3f(-4.0f, 4.0f, 0.0f);
    glVertex3f(-2.0f, 4.0f, 0.0f);
    glVertex3f(-2.0f, 4.0f, -7.0f);

    // Bottom face (y = 3.0f)
    glVertex3f(-4.0f, 3.0f, -7.0f);
    glVertex3f(-2.0f, 3.0f, -7.0f);
    glVertex3f(-2.0f, 3.0f, 0.0f);
    glVertex3f(-4.0f, 3.0f, 0.0f);

    // Front face  (z = 7.0f)
    glVertex3f(-4.0f, 3.0f, 0.0f);
    glVertex3f(-2.0f, 3.0f, 0.0f);
    glVertex3f(-2.0f, 4.0f, 0.0f);
    glVertex3f(-4.0f, 4.0f, 0.0f);

    // Back face (z = -7.0f)
    glVertex3f(-4.0f, 3.0f, -7.0f);
    glVertex3f(-4.0f, 4.0f, -7.0f);
    glVertex3f(-2.0f, 4.0f, -7.0f);
    glVertex3f(-2.0f, 3.0f, -7.0f);

    // Left face (x = -16.0f)
    glVertex3f(-4.0f, 4.0f, -7.0f);
    glVertex3f(-4.0f, 3.0f, -7.0f);
    glVertex3f(-4.0f, 3.0f, 0.0f);
    glVertex3f(-4.0f, 4.0f, 0.0f);

    // Right face (x = 14.0f)
    glVertex3f(-2.0f, 4.0f, -7.0f);
    glVertex3f(-2.0f, 4.0f, 0.0f);
    glVertex3f(-2.0f, 3.0f, 0.0f);
    glVertex3f(-2.0f, 3.0f, -7.0f);
    glEnd();  // End of drawing Bb1
}

void drawDb2() {
    glBegin(GL_QUADS); // Draw the Db2 key
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 4.0f)
    glVertex3f(2.0f, 4.0f, -7.0f);
    glVertex3f(2.0f, 4.0f, 0.0f);
    glVertex3f(4.0f, 4.0f, 0.0f);
    glVertex3f(4.0f, 4.0f, -7.0f);

    // Bottom face (y = 3.0f)
    glVertex3f(2.0f, 3.0f, -7.0f);
    glVertex3f(4.0f, 3.0f, -7.0f);
    glVertex3f(4.0f, 3.0f, 0.0f);
    glVertex3f(2.0f, 3.0f, 0.0f);

    // Front face  (z = 7.0f)
    glVertex3f(2.0f, 3.0f, 0.0f);
    glVertex3f(4.0f, 3.0f, 0.0f);
    glVertex3f(4.0f, 4.0f, 0.0f);
    glVertex3f(2.0f, 4.0f, 0.0f);

    // Back face (z = -7.0f)
    glVertex3f(2.0f, 3.0f, -7.0f);
    glVertex3f(2.0f, 4.0f, -7.0f);
    glVertex3f(4.0f, 4.0f, -7.0f);
    glVertex3f(4.0f, 3.0f, -7.0f);

    // Left face (x = -16.0f)
    glVertex3f(2.0f, 4.0f, -7.0f);
    glVertex3f(2.0f, 3.0f, -7.0f);
    glVertex3f(2.0f, 3.0f, 0.0f);
    glVertex3f(2.0f, 4.0f, 0.0f);

    // Right face (x = 14.0f)
    glVertex3f(4.0f, 4.0f, -7.0f);
    glVertex3f(4.0f, 4.0f, 0.0f);
    glVertex3f(4.0f, 3.0f, 0.0f);
    glVertex3f(4.0f, 3.0f, -7.0f);
    glEnd();  // End of drawing Db2
}

void drawEb2() {
    glBegin(GL_QUADS); // Draw the Eb2 key
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 4.0f)
    glVertex3f(5.0f, 4.0f, -7.0f);
    glVertex3f(5.0f, 4.0f, 0.0f);
    glVertex3f(7.0f, 4.0f, 0.0f);
    glVertex3f(7.0f, 4.0f, -7.0f);

    // Bottom face (y = 3.0f)
    glVertex3f(5.0f, 3.0f, -7.0f);
    glVertex3f(7.0f, 3.0f, -7.0f);
    glVertex3f(7.0f, 3.0f, 0.0f);
    glVertex3f(5.0f, 3.0f, 0.0f);

    // Front face  (z = 7.0f)
    glVertex3f(5.0f, 3.0f, 0.0f);
    glVertex3f(7.0f, 3.0f, 0.0f);
    glVertex3f(7.0f, 4.0f, 0.0f);
    glVertex3f(5.0f, 4.0f, 0.0f);

    // Back face (z = -7.0f)
    glVertex3f(5.0f, 3.0f, -7.0f);
    glVertex3f(5.0f, 4.0f, -7.0f);
    glVertex3f(7.0f, 4.0f, -7.0f);
    glVertex3f(7.0f, 3.0f, -7.0f);

    // Left face (x = -16.0f)
    glVertex3f(5.0f, 4.0f, -7.0f);
    glVertex3f(5.0f, 3.0f, -7.0f);
    glVertex3f(5.0f, 3.0f, 0.0f);
    glVertex3f(5.0f, 4.0f, 0.0f);

    // Right face (x = 14.0f)
    glVertex3f(7.0f, 4.0f, -7.0f);
    glVertex3f(7.0f, 4.0f, 0.0f);
    glVertex3f(7.0f, 3.0f, 0.0f);
    glVertex3f(7.0f, 3.0f, -7.0f);
    glEnd();  // End of drawing Eb2
}

void drawGb2() {
    glBegin(GL_QUADS); // Draw the Gb2 key
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 4.0f)
    glVertex3f(11.0f, 4.0f, -7.0f);
    glVertex3f(11.0f, 4.0f, 0.0f);
    glVertex3f(13.0f, 4.0f, 0.0f);
    glVertex3f(13.0f, 4.0f, -7.0f);

    // Bottom face (y = 3.0f)
    glVertex3f(11.0f, 3.0f, -7.0f);
    glVertex3f(13.0f, 3.0f, -7.0f);
    glVertex3f(13.0f, 3.0f, 0.0f);
    glVertex3f(11.0f, 3.0f, 0.0f);

    // Front face  (z = 7.0f)
    glVertex3f(11.0f, 3.0f, 0.0f);
    glVertex3f(13.0f, 3.0f, 0.0f);
    glVertex3f(13.0f, 4.0f, 0.0f);
    glVertex3f(11.0f, 4.0f, 0.0f);

    // Back face (z = -7.0f)
    glVertex3f(11.0f, 3.0f, -7.0f);
    glVertex3f(11.0f, 4.0f, -7.0f);
    glVertex3f(13.0f, 4.0f, -7.0f);
    glVertex3f(13.0f, 3.0f, -7.0f);

    // Left face (x = -16.0f)
    glVertex3f(11.0f, 4.0f, -7.0f);
    glVertex3f(11.0f, 3.0f, -7.0f);
    glVertex3f(11.0f, 3.0f, 0.0f);
    glVertex3f(11.0f, 4.0f, 0.0f);

    // Right face (x = 14.0f)
    glVertex3f(13.0f, 4.0f, -7.0f);
    glVertex3f(13.0f, 4.0f, 0.0f);
    glVertex3f(13.0f, 3.0f, 0.0f);
    glVertex3f(13.0f, 3.0f, -7.0f);
    glEnd();  // End of drawing Gb2
}

void drawAb2() {
    glBegin(GL_QUADS); // Draw the Ab2 key
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 4.0f)
    glVertex3f(14.0f, 4.0f, -7.0f);
    glVertex3f(14.0f, 4.0f, 0.0f);
    glVertex3f(16.0f, 4.0f, 0.0f);
    glVertex3f(16.0f, 4.0f, -7.0f);

    // Bottom face (y = 3.0f)
    glVertex3f(14.0f, 3.0f, -7.0f);
    glVertex3f(16.0f, 3.0f, -7.0f);
    glVertex3f(16.0f, 3.0f, 0.0f);
    glVertex3f(14.0f, 3.0f, 0.0f);

    // Front face  (z = 7.0f)
    glVertex3f(14.0f, 3.0f, 0.0f);
    glVertex3f(16.0f, 3.0f, 0.0f);
    glVertex3f(16.0f, 4.0f, 0.0f);
    glVertex3f(14.0f, 4.0f, 0.0f);

    // Back face (z = -7.0f)
    glVertex3f(14.0f, 3.0f, -7.0f);
    glVertex3f(14.0f, 4.0f, -7.0f);
    glVertex3f(16.0f, 4.0f, -7.0f);
    glVertex3f(16.0f, 3.0f, -7.0f);

    // Left face (x = -16.0f)
    glVertex3f(14.0f, 4.0f, -7.0f);
    glVertex3f(14.0f, 3.0f, -7.0f);
    glVertex3f(14.0f, 3.0f, 0.0f);
    glVertex3f(14.0f, 4.0f, 0.0f);

    // Right face (x = 14.0f)
    glVertex3f(16.0f, 4.0f, -7.0f);
    glVertex3f(16.0f, 4.0f, 0.0f);
    glVertex3f(16.0f, 3.0f, 0.0f);
    glVertex3f(16.0f, 3.0f, -7.0f);
    glEnd();  // End of drawing Ab2
}

void drawBb2() {
    glBegin(GL_QUADS); // Draw the Bb2 key
    glColor3f(0.0f, 0.0f, 0.0f);

    // Top face (y = 4.0f)
    glVertex3f(17.0f, 4.0f, -7.0f);
    glVertex3f(17.0f, 4.0f, 0.0f);
    glVertex3f(19.0f, 4.0f, 0.0f);
    glVertex3f(19.0f, 4.0f, -7.0f);

    // Bottom face (y = 3.0f)
    glVertex3f(17.0f, 3.0f, -7.0f);
    glVertex3f(19.0f, 3.0f, -7.0f);
    glVertex3f(19.0f, 3.0f, 0.0f);
    glVertex3f(17.0f, 3.0f, 0.0f);

    // Front face  (z = 7.0f)
    glVertex3f(17.0f, 3.0f, 0.0f);
    glVertex3f(19.0f, 3.0f, 0.0f);
    glVertex3f(19.0f, 4.0f, 0.0f);
    glVertex3f(17.0f, 4.0f, 0.0f);

    // Back face (z = -7.0f)
    glVertex3f(17.0f, 3.0f, -7.0f);
    glVertex3f(17.0f, 4.0f, -7.0f);
    glVertex3f(19.0f, 4.0f, -7.0f);
    glVertex3f(19.0f, 3.0f, -7.0f);

    // Left face (x = -16.0f)
    glVertex3f(17.0f, 4.0f, -7.0f);
    glVertex3f(17.0f, 3.0f, -7.0f);
    glVertex3f(17.0f, 3.0f, 0.0f);
    glVertex3f(17.0f, 4.0f, 0.0f);

    // Right face (x = 14.0f)
    glVertex3f(19.0f, 4.0f, -7.0f);
    glVertex3f(19.0f, 4.0f, 0.0f);
    glVertex3f(19.0f, 3.0f, 0.0f);
    glVertex3f(19.0f, 3.0f, -7.0f);
    glEnd();  // End of drawing Bb2
}


void drawLeftPalm() {
    glBegin(GL_QUADS); // Begin drawing the palm
    glColor3f(1.0f, 0.95f, 0.86f);

    // Top face (y = 0.0f)
    glVertex3f(-16.0f, 0.0f, -18.0f);
    glVertex3f(-16.0f, 0.0f, 0.0f);
    glVertex3f(-2.5f, 0.0f, 0.0f);
    glVertex3f(-2.5f, 0.0f, -18.0f);

    // Bottom face (y = -3.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(-16.0f, -3.0f, -18.0f);
    glVertex3f(-2.5f, -3.0f, -18.0f);
    glVertex3f(-2.5f, -3.0f, 0.0f);
    glVertex3f(-16.0f, -3.0f, 0.0f);

    // Front face  (z = 0.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(-16.0f, 0.0f, 0.0f);
    glVertex3f(-16.0f, -3.0f, 0.0f);
    glVertex3f(-2.5f, -3.0f, 0.0f);
    glVertex3f(-2.5f, 0.0f, 0.0f);

    // Back face (z = -18.0f)
    glVertex3f(-16.0f, 0.0f, -18.0f);
    glVertex3f(-2.5f, 0.0f, -18.0f);
    glVertex3f(-2.5f, -3.0f, -18.0f);
    glVertex3f(-16.0f, -3.0f, -18.0f);

    // Left face (x = -16.0f)
    glVertex3f(-16.0f, -3.0f, 0.0f);
    glVertex3f(-16.0f, -3.0f, -18.0f);
    glVertex3f(-16.0f, 0.0f, -18.0f);
    glVertex3f(-16.0f, 0.0f, 0.0f);

    // Right face (x = -2.5f)
    glVertex3f(-2.5f, -3.0f, 0.0f);
    glVertex3f(-2.5f, 0.0f, 0.0f);
    glVertex3f(-2.5f, 0.0f, -18.0f);
    glVertex3f(-2.5f, -3.0f, -18.0f);
    glEnd();  // End of drawing palm
}

void drawLeftThumb() {
    glBegin(GL_QUADS); // Begin drawing the thumb
    glColor3f(1.0f, 0.95f, 0.86f);

    // T1
    // Top face (y = 0.0f, y = -2.0f)
    glVertex3f(-2.5f, 0.0f, -9.0f);
    glVertex3f(-2.5f, 0.0f, 0.0f);
    glVertex3f(0.0f, -2.0f, -6.0f);
    glVertex3f(-2.0f, -2.0f, -9.0f);

    // Bottom face (y = -3.0f, y = -5.0f)
    glVertex3f(-2.5f, -3.0f, -9.0f);
    glVertex3f(-2.0f, -5.0f, -9.0f);
    glVertex3f(0.0f, -5.0f, -6.0f);
    glVertex3f(-2.5f, -3.0f, 0.0f);

    // Front face  (z = 0.0f, z = -6.0f)
    glVertex3f(-2.5f, 0.0f, 0.0f);
    glVertex3f(-2.5f, -3.0f, 0.0f);
    glVertex3f(0.0f, -5.0f, -6.0f);
    glVertex3f(0.0f, -2.0f, -6.0f);

    // Back face (z = -9.0f)
    glVertex3f(-2.5f, 0.0f, -9.0f);
    glVertex3f(-2.0f, -2.0f, -9.0f);
    glVertex3f(-2.0f, -5.0f, -9.0f);
    glVertex3f(-2.5f, -3.0f, -9.0f);

    // Left face (x = -2.5f)
    glVertex3f(-2.5f, -3.0f, 0.0f);
    glVertex3f(-2.5f, -3.0f, -9.0f);
    glVertex3f(-2.5f, 0.0f, -9.0f);
    glVertex3f(-2.5f, 0.0f, 0.0f);

    // Right face (x = -2.0f, x = 0.0f)
    glVertex3f(0.0f, -2.0f, -6.0f);
    glVertex3f(-2.0f, -2.0f, -9.0f);
    glVertex3f(-2.0f, -5.0f, -9.0f);
    glVertex3f(0.0f, -5.0f, -6.0f);

    // T2
    // Top face (y = -2.0f, y = -5.0f)
    glVertex3f(-2.0f, -2.0f, -9.0f);
    glVertex3f(0.0f, -2.0f, -6.0f);
    glVertex3f(0.0f, -5.0f, -20.0f);
    glVertex3f(-2.0f, -5.0f, -20.0f);

    // Bottom face (y = -5.0f, y = -8.0f)
    glVertex3f(-2.0f, -5.0f, -9.0f);
    glVertex3f(-2.0f, -8.0f, -20.0f);
    glVertex3f(0.0f, -8.0f, -20.0f);
    glVertex3f(0.0f, -5.0f, -6.0f);

    // Front face  (z = -6.0f, z = -9.0f)
    glVertex3f(0.0f, -2.0f, -6.0f);
    glVertex3f(0.0f, -5.0f, -6.0f);
    glVertex3f(-2.0f, -5.0f, -9.0f);
    glVertex3f(-2.0f, -2.0f, -9.0f);

    // Back face (z = -20.0f)
    glVertex3f(-2.0f, -5.0f, -20.0f);
    glVertex3f(0.0f, -5.0f, -20.0f);
    glVertex3f(0.0f, -8.0f, -20.0f);
    glVertex3f(-2.0f, -8.0f, -20.0f);

    // Left face (x = -2.0f)
    glVertex3f(-2.0f, -5.0f, -9.0f);
    glVertex3f(-2.0f, -8.0f, -20.0f);
    glVertex3f(-2.0f, -5.0f, -20.0f);
    glVertex3f(-2.0f, -2.0f, -9.0f);

    // Right face (x = 0.0f)
    glVertex3f(0.0f, -5.0f, -6.0f);
    glVertex3f(0.0f, -2.0f, -6.0f);
    glVertex3f(0.0f, -5.0f, -20.0f);
    glVertex3f(0.0f, -8.0f, -20.0f);

    glEnd();  // End of drawing thumb
}

void drawLeftIndex() {
    glBegin(GL_QUADS); // Begin drawing the index finger
    glColor3f(1.0f, 0.95f, 0.86f);

    // I1
    // Top face (y = 0.0f)
    glVertex3f(-5.5f, 0.0f, -18.0f);
    glVertex3f(-2.5f, 0.0f, -18.0f);
    glVertex3f(-2.5f, 0.0f, -25.0f);
    glVertex3f(-5.5f, 0.0f, -25.0f);

    // Bottom face (y = -3.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(-5.5f, -3.0f, -18.0f);
    glVertex3f(-5.5f, -3.0f, -25.0f);
    glVertex3f(-2.5f, -3.0f, -25.0f);
    glVertex3f(-2.5f, -3.0f, -18.0f);

    // Front face  (z = -18.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(-5.5f, -3.0f, -18.0f);
    glVertex3f(-2.5f, -3.0f, -18.0f);
    glVertex3f(-2.5f, 0.0f, -18.0f);
    glVertex3f(-5.5f, 0.0f, -18.0f);

    // Back face (z = -25.0f)
    glVertex3f(-5.5f, -3.0f, -25.0f);
    glVertex3f(-5.5f, 0.0f, -25.0f);
    glVertex3f(-2.5f, 0.0f, -25.0f);
    glVertex3f(-2.5f, -3.0f, -25.0f);

    // Left face (x = -5.5f)
    glVertex3f(-5.5f, -3.0f, -18.0f);
    glVertex3f(-5.5f, -3.0f, -25.0f);
    glVertex3f(-5.5f, 0.0f, -25.0f);
    glVertex3f(-5.5f, 0.0f, -18.0f);

    // Right face (x = -2.5f)
    glVertex3f(-2.5f, -3.0f, -18.0f);
    glVertex3f(-2.5f, 0.0f, -18.0f);
    glVertex3f(-2.5f, 0.0f, -25.0f);
    glVertex3f(-2.5f, -3.0f, -25.0f);

    // I2
    // Top face (y = 0.0f, y = -5.0f)
    glVertex3f(-5.5f, 0.0f, -25.0f);
    glVertex3f(-2.5f, 0.0f, -25.0f);
    glVertex3f(-3.0f, -5.0f, -31.0f);
    glVertex3f(-5.0f, -5.0f, -31.0f);

    // Bottom face (y = -3.0f, y = -6.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(-2.5f, -3.0f, -25.0f);
    glVertex3f(-5.5f, -3.0f, -25.0f);
    glVertex3f(-5.0f, -6.0f, -29.0f);
    glVertex3f(-3.0f, -6.0f, -29.0f);

    // Front face  (z = -25.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(-5.5f, -3.0f, -25.0f);
    glVertex3f(-2.5f, -3.0f, -25.0f);
    glVertex3f(-2.5f, 0.0f, -25.0f);
    glVertex3f(-5.5f, 0.0f, -25.0f);

    // Back face (z = -29.0f, z = -31.0f)
    glVertex3f(-3.0f, -6.0f, -29.0f);
    glVertex3f(-5.0f, -6.0f, -29.0f);
    glVertex3f(-5.0f, -5.0f, -31.0f);
    glVertex3f(-3.0f, -5.0f, -31.0f);

    // Left face (x = -5.5f, x = -5.0f)
    glVertex3f(-5.5f, 0.0f, -25.0f);
    glVertex3f(-5.5f, -3.0f, -25.0f);
    glVertex3f(-5.0f, -6.0f, -29.0f);
    glVertex3f(-5.0f, -5.0f, -31.0f);

    // Right face (x = -3.5f, x = -3.0f)
    glVertex3f(-2.5f, -3.0f, -25.0f);
    glVertex3f(-2.5f, 0.0f, -25.0f);
    glVertex3f(-3.0f, -5.0f, -31.0f);
    glVertex3f(-3.0f, -6.0f, -29.0f);

    // I3
    // Top face (y = -5.0f, y = -6.0f)
    glVertex3f(-3.0f, -5.0f, -31.0f);
    glVertex3f(-5.0f, -5.0f, -31.0f);
    glVertex3f(-5.0f, -6.0f, -29.0f);
    glVertex3f(-3.0f, -6.0f, -29.0f);

    // Bottom face (y = -8.0f)
    glVertex3f(-5.0f, -8.0f, -31.0f);
    glVertex3f(-3.0f, -8.0f, -31.0f);
    glVertex3f(-3.0f, -8.0f, -29.0f);
    glVertex3f(-5.0f, -8.0f, -29.0f);

    // Front face  (z = -29.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(-3.0f, -6.0f, -29.0f);
    glVertex3f(-5.0f, -6.0f, -29.0f);
    glVertex3f(-5.0f, -8.0f, -29.0f);
    glVertex3f(-3.0f, -8.0f, -29.0f);

    // Back face (z = -31.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(-5.0f, -5.0f, -31.0f);
    glVertex3f(-3.0f, -5.0f, -31.0f);
    glVertex3f(-3.0f, -8.0f, -31.0f);
    glVertex3f(-5.0f, -8.0f, -31.0f);

    // Left face (x = -5.0f)
    glVertex3f(-5.0f, -5.0f, -31.0f);
    glVertex3f(-5.0f, -6.0f, -29.0f);
    glVertex3f(-5.0f, -8.0f, -29.0f);
    glVertex3f(-5.0f, -8.0f, -31.0f);

    // Right face (x = -3.0f)
    glVertex3f(-3.0f, -5.0f, -31.0f);
    glVertex3f(-3.0f, -8.0f, -31.0f);
    glVertex3f(-3.0f, -8.0f, -29.0f);
    glVertex3f(-3.0f, -6.0f, -29.0f);

    glEnd();  // End of drawing index finger
}

void drawLeftMiddle() {
    glBegin(GL_QUADS); // Begin drawing the middle finger
    glColor3f(1.0f, 0.95f, 0.86f);

    // M1
    // Top face (y = 0.0f)
    glVertex3f(-9.0f, 0.0f, -18.0f);
    glVertex3f(-6.0f, 0.0f, -18.0f);
    glVertex3f(-6.0f, 0.0f, -27.0f);
    glVertex3f(-9.0f, 0.0f, -27.0f);

    // Bottom face (y = -3.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(-9.0f, -3.0f, -18.0f);
    glVertex3f(-9.0f, -3.0f, -27.0f);
    glVertex3f(-6.0f, -3.0f, -27.0f);
    glVertex3f(-6.0f, -3.0f, -18.0f);

    // Front face  (z = -18.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(-9.0f, -3.0f, -18.0f);
    glVertex3f(-6.0f, -3.0f, -18.0f);
    glVertex3f(-6.0f, 0.0f, -18.0f);
    glVertex3f(-9.0f, 0.0f, -18.0f);

    // Back face (z = -27.0f)
    glVertex3f(-9.0f, -3.0f, -27.0f);
    glVertex3f(-9.0f, 0.0f, -27.0f);
    glVertex3f(-6.0f, 0.0f, -27.0f);
    glVertex3f(-6.0f, -3.0f, -27.0f);

    // Left face (x = -9.0f)
    glVertex3f(-9.0f, -3.0f, -18.0f);
    glVertex3f(-9.0f, -3.0f, -27.0f);
    glVertex3f(-9.0f, 0.0f, -27.0f);
    glVertex3f(-9.0f, 0.0f, -18.0f);

    // Right face (x = -6.0f)
    glVertex3f(-6.0f, -3.0f, -18.0f);
    glVertex3f(-6.0f, 0.0f, -18.0f);
    glVertex3f(-6.0f, 0.0f, -27.0f);
    glVertex3f(-6.0f, -3.0f, -27.0f);

    // M2
    // Top face (y = 0.0f, y = -5.0f)
    glVertex3f(-9.0f, 0.0f, -27.0f);
    glVertex3f(-6.0f, 0.0f, -27.0f);
    glVertex3f(-6.5f, -5.0f, -33.0f);
    glVertex3f(-8.5f, -5.0f, -33.0f);

    // Bottom face (y = -3.0f, y = -6.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(-6.0f, -3.0f, -27.0f);
    glVertex3f(-9.0f, -3.0f, -27.0f);
    glVertex3f(-8.5f, -6.0f, -31.0f);
    glVertex3f(-6.5f, -6.0f, -31.0f);

    // Front face  (z = -27.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(-9.0f, -3.0f, -27.0f);
    glVertex3f(-6.0f, -3.0f, -27.0f);
    glVertex3f(-6.0f, 0.0f, -27.0f);
    glVertex3f(-9.0f, 0.0f, -27.0f);

    // Back face (z = -31.0f, z = -33.0f)
    glVertex3f(-6.5f, -6.0f, -31.0f);
    glVertex3f(-8.5f, -6.0f, -31.0f);
    glVertex3f(-8.5f, -5.0f, -33.0f);
    glVertex3f(-6.5f, -5.0f, -33.0f);

    // Left face (x = -9.0f, x = -8.5f)

    glVertex3f(-9.0f, 0.0f, -27.0f);
    glVertex3f(-9.0f, -3.0f, -27.0f);
    glVertex3f(-8.5f, -6.0f, -31.0f);
    glVertex3f(-8.5f, -5.0f, -33.0f);

    // Right face (x = -6.0f, x = -6.5f)

    glVertex3f(-6.0f, -3.0f, -27.0f);
    glVertex3f(-6.0f, 0.0f, -27.0f);
    glVertex3f(-6.5f, -5.0f, -33.0f);
    glVertex3f(-6.5f, -6.0f, -31.0f);

    glColor3f(1.0f, 0.95f, 0.86f);

    // M3
    // Top face (y = -5.0f, y = -6.0f)
    glVertex3f(-6.5f, -5.0f, -33.0f);
    glVertex3f(-8.5f, -5.0f, -33.0f);
    glVertex3f(-8.5f, -6.0f, -31.0f);
    glVertex3f(-6.5f, -6.0f, -31.0f);

    // Bottom face (y = -8.0f)
    glVertex3f(-8.5f, -8.0f, -33.0f);
    glVertex3f(-6.5f, -8.0f, -33.0f);
    glVertex3f(-6.5f, -8.0f, -31.0f);
    glVertex3f(-8.5f, -8.0f, -31.0f);

    // Front face  (z = -31.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(-6.5f, -6.0f, -31.0f);
    glVertex3f(-8.5f, -6.0f, -31.0f);
    glVertex3f(-8.5f, -8.0f, -31.0f);
    glVertex3f(-6.5f, -8.0f, -31.0f);

    // Back face (z = -33.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(-8.5f, -5.0f, -33.0f);
    glVertex3f(-6.5f, -5.0f, -33.0f);
    glVertex3f(-6.5f, -8.0f, -33.0f);
    glVertex3f(-8.5f, -8.0f, -33.0f);

    // Left face (x = -8.5f)
    glVertex3f(-8.5f, -5.0f, -33.0f);
    glVertex3f(-8.5f, -6.0f, -31.0f);
    glVertex3f(-8.5f, -8.0f, -31.0f);
    glVertex3f(-8.5f, -8.0f, -33.0f);

    // Right face (x = -6.5f)
    glVertex3f(-6.5f, -5.0f, -33.0f);
    glVertex3f(-6.5f, -8.0f, -33.0f);
    glVertex3f(-6.5f, -8.0f, -31.0f);
    glVertex3f(-6.5f, -6.0f, -31.0f);

    glEnd();  // End of drawing middle finger
}

void drawLeftRing() {
    glBegin(GL_QUADS); // Begin drawing the ring finger
    glColor3f(1.0f, 0.95f, 0.86f);

    // R1
    // Top face (y = 0.0f)
    glVertex3f(-12.5f, 0.0f, -18.0f);
    glVertex3f(-9.5f, 0.0f, -18.0f);
    glVertex3f(-9.5f, 0.0f, -25.0f);
    glVertex3f(-12.5f, 0.0f, -25.0f);

    // Bottom face (y = -3.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(-12.5f, -3.0f, -18.0f);
    glVertex3f(-12.5f, -3.0f, -25.0f);
    glVertex3f(-9.5f, -3.0f, -25.0f);
    glVertex3f(-9.5f, -3.0f, -18.0f);

    // Front face  (z = -18.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(-12.5f, -3.0f, -18.0f);
    glVertex3f(-9.5f, -3.0f, -18.0f);
    glVertex3f(-9.5f, 0.0f, -18.0f);
    glVertex3f(-12.5f, 0.0f, -18.0f);

    // Back face (z = -25.0f)
    glVertex3f(-12.5f, -3.0f, -25.0f);
    glVertex3f(-12.5f, 0.0f, -25.0f);
    glVertex3f(-9.5f, 0.0f, -25.0f);
    glVertex3f(-9.5f, -3.0f, -25.0f);

    // Left face (x = -12.5f)
    glVertex3f(-12.5f, -3.0f, -18.0f);
    glVertex3f(-12.5f, -3.0f, -25.0f);
    glVertex3f(-12.5f, 0.0f, -25.0f);
    glVertex3f(-12.5f, 0.0f, -18.0f);

    // Right face (x = -9.5f)
    glVertex3f(-9.5f, -3.0f, -18.0f);
    glVertex3f(-9.5f, 0.0f, -18.0f);
    glVertex3f(-9.5f, 0.0f, -25.0f);
    glVertex3f(-9.5f, -3.0f, -25.0f);

    // R2
    // Top face (y = 0.0f, y = -5.0f)
    glVertex3f(-9.5f, 0.0f, -25.0f);
    glVertex3f(-12.5f, 0.0f, -25.0f);
    glVertex3f(-12.0f, -5.0f, -31.0f);
    glVertex3f(-10.0f, -5.0f, -31.0f);

    // Bottom face (y = -3.0f, y = -6.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(-9.5f, -3.0f, -25.0f);
    glVertex3f(-12.5f, -3.0f, -25.0f);
    glVertex3f(-12.0f, -6.0f, -29.0f);
    glVertex3f(-10.0f, -6.0f, -29.0f);

    // Front face  (z = -25.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(-12.5f, -3.0f, -25.0f);
    glVertex3f(-9.5f, -3.0f, -25.0f);
    glVertex3f(-9.5f, 0.0f, -25.0f);
    glVertex3f(-12.5f, 0.0f, -25.0f);

    // Back face (z = -29.0f, z = -31.0f)
    glVertex3f(-10.0f, -6.0f, -29.0f);
    glVertex3f(-12.0f, -6.0f, -29.0f);
    glVertex3f(-12.0f, -5.0f, -31.0f);
    glVertex3f(-10.0f, -5.0f, -31.0f);

    // Left face (x = -12.5f, x = -12.0f)
    glVertex3f(-12.5f, 0.0f, -25.0f);
    glVertex3f(-12.5f, -3.0f, -25.0f);
    glVertex3f(-12.0f, -6.0f, -29.0f);
    glVertex3f(-12.0f, -5.0f, -31.0f);

    // Right face (x = -9.5f, x = -10.0f)
    glVertex3f(-9.5f, -3.0f, -25.0f);
    glVertex3f(-9.5f, 0.0f, -25.0f);
    glVertex3f(-10.0f, -5.0f, -31.0f);
    glVertex3f(-10.0f, -6.0f, -29.0f);

    // R3
    // Top face (y = -5.0f, y = -6.0f)
    glVertex3f(-10.0f, -5.0f, -31.0f);
    glVertex3f(-12.0f, -5.0f, -31.0f);
    glVertex3f(-12.0f, -6.0f, -29.0f);
    glVertex3f(-10.0f, -6.0f, -29.0f);

    // Bottom face (y = -8.0f)
    glVertex3f(-12.0f, -8.0f, -31.0f);
    glVertex3f(-10.0f, -8.0f, -31.0f);
    glVertex3f(-10.0f, -8.0f, -29.0f);
    glVertex3f(-12.0f, -8.0f, -29.0f);

    // Front face  (z = -29.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(-10.0f, -6.0f, -29.0f);
    glVertex3f(-12.0f, -6.0f, -29.0f);
    glVertex3f(-12.0f, -8.0f, -29.0f);
    glVertex3f(-10.0f, -8.0f, -29.0f);

    // Back face (z = -31.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(-12.0f, -5.0f, -31.0f);
    glVertex3f(-10.0f, -5.0f, -31.0f);
    glVertex3f(-10.0f, -8.0f, -31.0f);
    glVertex3f(-12.0f, -8.0f, -31.0f);

    // Left face (x = -12.0f)
    glVertex3f(-12.0f, -5.0f, -31.0f);
    glVertex3f(-12.0f, -6.0f, -29.0f);
    glVertex3f(-12.0f, -8.0f, -29.0f);
    glVertex3f(-12.0f, -8.0f, -31.0f);

    // Right face (x = -10.0f)
    glVertex3f(-10.0f, -5.0f, -31.0f);
    glVertex3f(-10.0f, -8.0f, -31.0f);
    glVertex3f(-10.0f, -8.0f, -29.0f);
    glVertex3f(-10.0f, -6.0f, -29.0f);

    glEnd();  // End of drawing ring finger
}

void drawLeftPinky() {
    glBegin(GL_QUADS); // Begin drawing the pinky
    glColor3f(1.0f, 0.95f, 0.86f);

    // P1
    // Top face (y = 0.0f)
    glVertex3f(-16.0f, 0.0f, -18.0f);
    glVertex3f(-13.0f, 0.0f, -18.0f);
    glVertex3f(-13.0f, 0.0f, -23.0f);
    glVertex3f(-16.0f, 0.0f, -23.0f);

    // Bottom face (y = -3.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(-16.0f, -3.0f, -18.0f);
    glVertex3f(-16.0f, -3.0f, -23.0f);
    glVertex3f(-13.0f, -3.0f, -23.0f);
    glVertex3f(-13.0f, -3.0f, -18.0f);

    // Front face  (z = -18.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(-16.0f, -3.0f, -18.0f);
    glVertex3f(-13.0f, -3.0f, -18.0f);
    glVertex3f(-13.0f, 0.0f, -18.0f);
    glVertex3f(-16.0f, 0.0f, -18.0f);

    // Back face (z = -23.0f)
    glVertex3f(-16.0f, -3.0f, -23.0f);
    glVertex3f(-16.0f, 0.0f, -23.0f);
    glVertex3f(-13.0f, 0.0f, -23.0f);
    glVertex3f(-13.0f, -3.0f, -23.0f);

    // Left face (x = -16.0f)
    glVertex3f(-16.0f, -3.0f, -18.0f);
    glVertex3f(-16.0f, -3.0f, -23.0f);
    glVertex3f(-16.0f, 0.0f, -23.0f);
    glVertex3f(-16.0f, 0.0f, -18.0f);

    // Right face (x = -13.0f)
    glVertex3f(-13.0f, -3.0f, -18.0f);
    glVertex3f(-13.0f, 0.0f, -18.0f);
    glVertex3f(-13.0f, 0.0f, -23.0f);
    glVertex3f(-13.0f, -3.0f, -23.0f);

    // P2
    // Top face (y = 0.0f, y = -5.0f)
    glVertex3f(-16.0f, 0.0f, -23.0f);
    glVertex3f(-13.0f, 0.0f, -23.0f);
    glVertex3f(-13.5f, -5.0f, -29.0f);
    glVertex3f(-15.5f, -5.0f, -29.0f);

    // Bottom face (y = -3.0f, y = -6.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(-13.0f, -3.0f, -23.0f);
    glVertex3f(-16.0f, -3.0f, -23.0f);
    glVertex3f(-15.5f, -6.0f, -27.0f);
    glVertex3f(-13.5f, -6.0f, -27.0f);

    // Front face  (z = -23.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(-16.0f, -3.0f, -23.0f);
    glVertex3f(-13.0f, -3.0f, -23.0f);
    glVertex3f(-13.0f, 0.0f, -23.0f);
    glVertex3f(-16.0f, 0.0f, -23.0f);

    // Back face (z = -27.0f, z = -29.0f)
    glVertex3f(-13.5f, -6.0f, -27.0f);
    glVertex3f(-15.5f, -6.0f, -27.0f);
    glVertex3f(-15.5f, -5.0f, -29.0f);
    glVertex3f(-13.5f, -5.0f, -29.0f);

    // Left face (x = -16.0f, x = -15.5f)
    glVertex3f(-16.0f, 0.0f, -23.0f);
    glVertex3f(-16.0f, -3.0f, -23.0f);
    glVertex3f(-15.5f, -6.0f, -27.0f);
    glVertex3f(-15.5f, -5.0f, -29.0f);

    // Right face (x = -13.0f, x = -13.5f)
    glVertex3f(-13.0f, -3.0f, -23.0f);
    glVertex3f(-13.0f, 0.0f, -23.0f);
    glVertex3f(-13.5f, -5.0f, -29.0f);
    glVertex3f(-13.5f, -6.0f, -27.0f);

    // P3
    // Top face (y = -5.0f, y = -6.0f)
    glVertex3f(-13.5f, -5.0f, -29.0f);
    glVertex3f(-15.5f, -5.0f, -29.0f);
    glVertex3f(-15.5f, -6.0f, -27.0f);
    glVertex3f(-13.5f, -6.0f, -27.0f);

    // Bottom face (y = -8.0f)
    glVertex3f(-15.5f, -8.0f, -29.0f);
    glVertex3f(-13.5f, -8.0f, -29.0f);
    glVertex3f(-13.5f, -8.0f, -27.0f);
    glVertex3f(-15.5f, -8.0f, -27.0f);

    // Front face  (z = -27.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(-13.5f, -6.0f, -27.0f);
    glVertex3f(-15.5f, -6.0f, -27.0f);
    glVertex3f(-15.5f, -8.0f, -27.0f);
    glVertex3f(-13.5f, -8.0f, -27.0f);

    // Back face (z = -29.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(-15.5f, -5.0f, -29.0f);
    glVertex3f(-13.5f, -5.0f, -29.0f);
    glVertex3f(-13.5f, -8.0f, -29.0f);
    glVertex3f(-15.5f, -8.0f, -29.0f);

    // Left face (x = -15.5f)
    glVertex3f(-15.5f, -5.0f, -29.0f);
    glVertex3f(-15.5f, -6.0f, -27.0f);
    glVertex3f(-15.5f, -8.0f, -27.0f);
    glVertex3f(-15.5f, -8.0f, -29.0f);

    // Right face (x = -13.5f)
    glVertex3f(-13.5f, -5.0f, -29.0f);
    glVertex3f(-13.5f, -8.0f, -29.0f);
    glVertex3f(-13.5f, -8.0f, -27.0f);
    glVertex3f(-13.5f, -6.0f, -27.0f);

    glEnd();  // End of drawing pinky
}

void drawRightPalm() {
    glBegin(GL_QUADS); // Begin drawing the palm
    glColor3f(1.0f, 0.95f, 0.86f);

    // Top face (y = 0.0f)
    glVertex3f(2.5f, 0.0f, -18.0f);
    glVertex3f(2.5f, 0.0f, 0.0f);
    glVertex3f(16.0f, 0.0f, 0.0f);
    glVertex3f(16.0f, 0.0f, -18.0f);

    // Bottom face (y = -3.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(2.5f, -3.0f, -18.0f);
    glVertex3f(16.0f, -3.0f, -18.0f);
    glVertex3f(16.0f, -3.0f, 0.0f);
    glVertex3f(2.5f, -3.0f, 0.0f);

    // Front face  (z = 0.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(2.5f, 0.0f, 0.0f);
    glVertex3f(2.5f, -3.0f, 0.0f);
    glVertex3f(16.0f, -3.0f, 0.0f);
    glVertex3f(16.0f, 0.0f, 0.0f);

    // Back face (z = -18.0f)
    glVertex3f(2.5f, 0.0f, -18.0f);
    glVertex3f(16.0f, 0.0f, -18.0f);
    glVertex3f(16.0f, -3.0f, -18.0f);
    glVertex3f(2.5f, -3.0f, -18.0f);

    // Left face (x = 2.5f)
    glVertex3f(2.5f, -3.0f, 0.0f);
    glVertex3f(2.5f, -3.0f, -18.0f);
    glVertex3f(2.5f, 0.0f, -18.0f);
    glVertex3f(2.5f, 0.0f, 0.0f);

    // Right face (x = 16.0f)
    glVertex3f(16.0f, -3.0f, 0.0f);
    glVertex3f(16.0f, 0.0f, 0.0f);
    glVertex3f(16.0f, 0.0f, -18.0f);
    glVertex3f(16.0f, -3.0f, -18.0f);
    glEnd();  // End of drawing palm
}

void drawRightThumb() {
    glBegin(GL_QUADS); // Begin drawing the thumb
    glColor3f(1.0f, 0.95f, 0.86f);

    // T1
    // Top face (y = 0.0f, y = -2.0f)
    glVertex3f(2.5f, 0.0f, -9.0f);
    glVertex3f(2.0f, -2.0f, -9.0f);
    glVertex3f(0.0f, -2.0f, -6.0f);
    glVertex3f(2.5f, 0.0f, 0.0f);

    // Bottom face (y = -3.0f, y = -5.0f)
    glVertex3f(2.5f, -3.0f, -9.0f);
    glVertex3f(2.5f, -3.0f, 0.0f);
    glVertex3f(0.0f, -5.0f, -6.0f);
    glVertex3f(2.0f, -5.0f, -9.0f);

    // Front face  (z = 0.0f, z = -6.0f)
    glVertex3f(2.5f, 0.0f, 0.0f);
    glVertex3f(0.0f, -2.0f, -6.0f);
    glVertex3f(0.0f, -5.0f, -6.0f);
    glVertex3f(2.5f, -3.0f, 0.0f);

    // Back face (z = -9.0f)
    glVertex3f(2.5f, 0.0f, -9.0f);
    glVertex3f(2.5f, -3.0f, -9.0f);
    glVertex3f(2.0f, -5.0f, -9.0f);
    glVertex3f(2.0f, -2.0f, -9.0f);

    // Left face (x = 2.0f, x = 0.0f)
    glVertex3f(0.0f, -2.0f, -6.0f);
    glVertex3f(0.0f, -5.0f, -6.0f);
    glVertex3f(2.0f, -5.0f, -9.0f);
    glVertex3f(2.0f, -2.0f, -9.0f);

    // Right face (x = 2.5f)
    glVertex3f(2.5f, -3.0f, 0.0f);
    glVertex3f(2.5f, 0.0f, 0.0f);
    glVertex3f(2.5f, 0.0f, -9.0f);
    glVertex3f(2.5f, -3.0f, -9.0f);

    // T2
    // Top face (y = -2.0f, y = -5.0f)
    glVertex3f(2.0f, -2.0f, -9.0f);
    glVertex3f(2.0f, -5.0f, -20.0f);
    glVertex3f(0.0f, -5.0f, -20.0f);
    glVertex3f(0.0f, -2.0f, -6.0f);

    // Bottom face (y = -5.0f, y = -8.0f)
    glVertex3f(2.0f, -5.0f, -9.0f);
    glVertex3f(0.0f, -5.0f, -6.0f);
    glVertex3f(0.0f, -8.0f, -20.0f);
    glVertex3f(2.0f, -8.0f, -20.0f);

    // Front face  (z = -6.0f, z = -9.0f)
    glVertex3f(0.0f, -2.0f, -6.0f);
    glVertex3f(2.0f, -2.0f, -9.0f);
    glVertex3f(2.0f, -5.0f, -9.0f);
    glVertex3f(0.0f, -5.0f, -6.0f);

    // Back face (z = -20.0f)
    glVertex3f(2.0f, -5.0f, -20.0f);
    glVertex3f(2.0f, -8.0f, -20.0f);
    glVertex3f(0.0f, -8.0f, -20.0f);
    glVertex3f(0.0f, -5.0f, -20.0f);

    // Left face (x = 0.0f)
    glVertex3f(0.0f, -5.0f, -6.0f);
    glVertex3f(0.0f, -8.0f, -20.0f);
    glVertex3f(0.0f, -5.0f, -20.0f);
    glVertex3f(0.0f, -2.0f, -6.0f);

    // Right face (x = 2.0f)
    glVertex3f(2.0f, -5.0f, -9.0f);
    glVertex3f(2.0f, -2.0f, -9.0f);
    glVertex3f(2.0f, -5.0f, -20.0f);
    glVertex3f(2.0f, -8.0f, -20.0f);

    glEnd();  // End of drawing thumb
}

void drawRightIndex() {
    glBegin(GL_QUADS); // Begin drawing the index finger
    glColor3f(1.0f, 0.95f, 0.86f);

    // I1
    // Top face (y = 0.0f)
    glVertex3f(5.5f, 0.0f, -18.0f);
    glVertex3f(5.5f, 0.0f, -25.0f);
    glVertex3f(2.5f, 0.0f, -25.0f);
    glVertex3f(2.5f, 0.0f, -18.0f);

    // Bottom face (y = -3.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(5.5f, -3.0f, -18.0f);
    glVertex3f(2.5f, -3.0f, -18.0f);
    glVertex3f(2.5f, -3.0f, -25.0f);
    glVertex3f(5.5f, -3.0f, -25.0f);

    // Front face  (z = -18.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(5.5f, -3.0f, -18.0f);
    glVertex3f(5.5f, 0.0f, -18.0f);
    glVertex3f(2.5f, 0.0f, -18.0f);
    glVertex3f(2.5f, -3.0f, -18.0f);

    // Back face (z = -25.0f)
    glVertex3f(5.5f, -3.0f, -25.0f);
    glVertex3f(2.5f, -3.0f, -25.0f);
    glVertex3f(2.5f, 0.0f, -25.0f);
    glVertex3f(5.5f, 0.0f, -25.0f);

    // Left face (x = 2.5f)
    glVertex3f(2.5f, -3.0f, -18.0f);
    glVertex3f(2.5f, -3.0f, -25.0f);
    glVertex3f(2.5f, 0.0f, -25.0f);
    glVertex3f(2.5f, 0.0f, -18.0f);

    // Right face (x = 5.5f)
    glVertex3f(5.5f, -3.0f, -18.0f);
    glVertex3f(5.5f, 0.0f, -18.0f);
    glVertex3f(5.5f, 0.0f, -25.0f);
    glVertex3f(5.5f, -3.0f, -25.0f);

    // I2
    // Top face (y = 0.0f, y = -5.0f)
    glVertex3f(5.5f, 0.0f, -25.0f);
    glVertex3f(5.0f, -5.0f, -31.0f);
    glVertex3f(3.0f, -5.0f, -31.0f);
    glVertex3f(2.5f, 0.0f, -25.0f);

    // Bottom face (y = -3.0f, y = -6.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(2.5f, -3.0f, -25.0f);
    glVertex3f(3.0f, -6.0f, -29.0f);
    glVertex3f(5.0f, -6.0f, -29.0f);
    glVertex3f(5.5f, -3.0f, -25.0f);

    // Front face  (z = -25.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(5.5f, -3.0f, -25.0f);
    glVertex3f(5.5f, 0.0f, -25.0f);
    glVertex3f(2.5f, 0.0f, -25.0f);
    glVertex3f(2.5f, -3.0f, -25.0f);

    // Back face (z = -29.0f, z = -31.0f)
    glVertex3f(3.0f, -6.0f, -29.0f);
    glVertex3f(3.0f, -5.0f, -31.0f);
    glVertex3f(5.0f, -5.0f, -31.0f);
    glVertex3f(5.0f, -6.0f, -29.0f);

    // Left face (x = 3.5f, x = 3.0f)
    glVertex3f(2.5f, -3.0f, -25.0f);
    glVertex3f(3.0f, -6.0f, -29.0f);
    glVertex3f(3.0f, -5.0f, -31.0f);
    glVertex3f(2.5f, 0.0f, -25.0f);

    // Right face (x = 5.5f, x = 5.0f)
    glVertex3f(5.5f, 0.0f, -25.0f);
    glVertex3f(5.0f, -5.0f, -31.0f);
    glVertex3f(5.0f, -6.0f, -29.0f);
    glVertex3f(5.5f, -3.0f, -25.0f);

    // I3
    // Top face (y = -5.0f, y = -6.0f)
    glVertex3f(3.0f, -5.0f, -31.0f);
    glVertex3f(3.0f, -6.0f, -29.0f);
    glVertex3f(5.0f, -6.0f, -29.0f);
    glVertex3f(5.0f, -5.0f, -31.0f);

    // Bottom face (y = -8.0f)
    glVertex3f(5.0f, -8.0f, -31.0f);
    glVertex3f(5.0f, -8.0f, -29.0f);
    glVertex3f(3.0f, -8.0f, -29.0f);
    glVertex3f(3.0f, -8.0f, -31.0f);

    // Front face  (z = -29.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(3.0f, -6.0f, -29.0f);
    glVertex3f(3.0f, -8.0f, -29.0f);
    glVertex3f(5.0f, -8.0f, -29.0f);
    glVertex3f(5.0f, -6.0f, -29.0f);

    // Back face (z = -31.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(5.0f, -5.0f, -31.0f);
    glVertex3f(5.0f, -8.0f, -31.0f);
    glVertex3f(3.0f, -8.0f, -31.0f);
    glVertex3f(3.0f, -5.0f, -31.0f);

    // Left face (x = 3.0f)
    glVertex3f(3.0f, -5.0f, -31.0f);
    glVertex3f(3.0f, -8.0f, -31.0f);
    glVertex3f(3.0f, -8.0f, -29.0f);
    glVertex3f(3.0f, -6.0f, -29.0f);

    // Right face (x = 5.0f)
    glVertex3f(5.0f, -5.0f, -31.0f);
    glVertex3f(5.0f, -8.0f, -31.0f);
    glVertex3f(5.0f, -8.0f, -29.0f);
    glVertex3f(5.0f, -6.0f, -29.0f);

    glEnd();  // End of drawing index finger
}

void drawRightMiddle() {
    glBegin(GL_QUADS); // Begin drawing the middle finger
    glColor3f(1.0f, 0.95f, 0.86f);

    // M1
    // Top face (y = 0.0f)
    glVertex3f(9.0f, 0.0f, -18.0f);
    glVertex3f(9.0f, 0.0f, -27.0f);
    glVertex3f(6.0f, 0.0f, -27.0f);
    glVertex3f(6.0f, 0.0f, -18.0f);

    // Bottom face (y = -3.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(9.0f, -3.0f, -18.0f);
    glVertex3f(6.0f, -3.0f, -18.0f);
    glVertex3f(6.0f, -3.0f, -27.0f);
    glVertex3f(9.0f, -3.0f, -27.0f);

    // Front face  (z = -18.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(9.0f, -3.0f, -18.0f);
    glVertex3f(9.0f, 0.0f, -18.0f);
    glVertex3f(6.0f, 0.0f, -18.0f);
    glVertex3f(6.0f, -3.0f, -18.0f);

    // Back face (z = -27.0f)
    glVertex3f(9.0f, -3.0f, -27.0f);
    glVertex3f(6.0f, -3.0f, -27.0f);
    glVertex3f(6.0f, 0.0f, -27.0f);
    glVertex3f(9.0f, 0.0f, -27.0f);

    // Left face (x = 6.0f)
    glVertex3f(6.0f, -3.0f, -18.0f);
    glVertex3f(6.0f, -3.0f, -27.0f);
    glVertex3f(6.0f, 0.0f, -27.0f);
    glVertex3f(6.0f, 0.0f, -18.0f);

    // Right face (x = 9.0f)
    glVertex3f(9.0f, -3.0f, -18.0f);
    glVertex3f(9.0f, 0.0f, -18.0f);
    glVertex3f(9.0f, 0.0f, -27.0f);
    glVertex3f(9.0f, -3.0f, -27.0f);

    // M2
    // Top face (y = 0.0f, y = -5.0f)
    glVertex3f(9.0f, 0.0f, -27.0f);
    glVertex3f(8.5f, -5.0f, -33.0f);
    glVertex3f(6.5f, -5.0f, -33.0f);
    glVertex3f(6.0f, 0.0f, -27.0f);

    // Bottom face (y = -3.0f, y = -6.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(6.0f, -3.0f, -27.0f);
    glVertex3f(6.5f, -6.0f, -31.0f);
    glVertex3f(8.5f, -6.0f, -31.0f);
    glVertex3f(9.0f, -3.0f, -27.0f);

    // Front face  (z = -27.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(9.0f, -3.0f, -27.0f);
    glVertex3f(9.0f, 0.0f, -27.0f);
    glVertex3f(6.0f, 0.0f, -27.0f);
    glVertex3f(6.0f, -3.0f, -27.0f);

    // Back face (z = -31.0f, z = -33.0f)
    glVertex3f(6.5f, -6.0f, -31.0f);
    glVertex3f(6.5f, -5.0f, -33.0f);
    glVertex3f(8.5f, -5.0f, -33.0f);
    glVertex3f(8.5f, -6.0f, -31.0f);

    // Right face (x = 9.0f, x = 8.5f)
    glVertex3f(9.0f, 0.0f, -27.0f);
    glVertex3f(8.5f, -5.0f, -33.0f);
    glVertex3f(8.5f, -6.0f, -31.0f);
    glVertex3f(9.0f, -3.0f, -27.0f);

    // Left face (x = 6.0f, x = 6.5f)
    glVertex3f(6.0f, -3.0f, -27.0f);
    glVertex3f(6.5f, -6.0f, -31.0f);
    glVertex3f(6.5f, -5.0f, -33.0f);
    glVertex3f(6.0f, 0.0f, -27.0f);

    // M3
    // Top face (y = -5.0f, y = -6.0f)
    glVertex3f(6.5f, -5.0f, -33.0f);
    glVertex3f(6.5f, -6.0f, -31.0f);
    glVertex3f(8.5f, -6.0f, -31.0f);
    glVertex3f(8.5f, -5.0f, -33.0f);

    // Bottom face (y = -8.0f)
    glVertex3f(8.5f, -8.0f, -33.0f);
    glVertex3f(8.5f, -8.0f, -31.0f);
    glVertex3f(6.5f, -8.0f, -31.0f);
    glVertex3f(6.5f, -8.0f, -33.0f);

    // Front face  (z = -31.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(6.5f, -6.0f, -31.0f);
    glVertex3f(6.5f, -8.0f, -31.0f);
    glVertex3f(8.5f, -8.0f, -31.0f);
    glVertex3f(8.5f, -6.0f, -31.0f);

    // Back face (z = -33.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(8.5f, -5.0f, -33.0f);
    glVertex3f(8.5f, -8.0f, -33.0f);
    glVertex3f(6.5f, -8.0f, -33.0f);
    glVertex3f(6.5f, -5.0f, -33.0f);

    // Right face (x = 8.5f)
    glVertex3f(8.5f, -5.0f, -33.0f);
    glVertex3f(8.5f, -8.0f, -33.0f);
    glVertex3f(8.5f, -8.0f, -31.0f);
    glVertex3f(8.5f, -6.0f, -31.0f);

    // Left face (x = 6.5f)
    glVertex3f(6.5f, -5.0f, -33.0f);
    glVertex3f(6.5f, -6.0f, -31.0f);
    glVertex3f(6.5f, -8.0f, -31.0f);
    glVertex3f(6.5f, -8.0f, -33.0f);

    glEnd();  // End of drawing middle finger
}

void drawRightRing() {
    glBegin(GL_QUADS); // Begin drawing the ring finger
    glColor3f(1.0f, 0.95f, 0.86f);

    // R1
    // Top face (y = 0.0f)
    glVertex3f(12.5f, 0.0f, -18.0f);
    glVertex3f(12.5f, 0.0f, -25.0f);
    glVertex3f(9.5f, 0.0f, -25.0f);
    glVertex3f(9.5f, 0.0f, -18.0f);

    // Bottom face (y = -3.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(12.5f, -3.0f, -18.0f);
    glVertex3f(9.5f, -3.0f, -18.0f);
    glVertex3f(9.5f, -3.0f, -25.0f);
    glVertex3f(12.5f, -3.0f, -25.0f);

    // Front face  (z = -18.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(12.5f, -3.0f, -18.0f);
    glVertex3f(12.5f, 0.0f, -18.0f);
    glVertex3f(9.5f, 0.0f, -18.0f);
    glVertex3f(9.5f, -3.0f, -18.0f);

    // Back face (z = -25.0f)
    glVertex3f(12.5f, -3.0f, -25.0f);
    glVertex3f(9.5f, -3.0f, -25.0f);
    glVertex3f(9.5f, 0.0f, -25.0f);
    glVertex3f(12.5f, 0.0f, -25.0f);

    // Left face (x = 9.5f)
    glVertex3f(9.5f, -3.0f, -18.0f);
    glVertex3f(9.5f, 0.0f, -18.0f);
    glVertex3f(9.5f, 0.0f, -25.0f);
    glVertex3f(9.5f, -3.0f, -25.0f);

    // Right face (x = 12.5f)
    glVertex3f(12.5f, -3.0f, -18.0f);
    glVertex3f(12.5f, 0.0f, -18.0f);
    glVertex3f(12.5f, 0.0f, -25.0f);
    glVertex3f(12.5f, -3.0f, -25.0f);

    // R2
    // Top face (y = 0.0f, y = -5.0f)
    glVertex3f(9.5f, 0.0f, -25.0f);
    glVertex3f(10.0f, -5.0f, -31.0f);
    glVertex3f(12.0f, -5.0f, -31.0f);
    glVertex3f(12.5f, 0.0f, -25.0f);

    // Bottom face (y = -3.0f, y = -6.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(9.5f, -3.0f, -25.0f);
    glVertex3f(10.0f, -6.0f, -29.0f);
    glVertex3f(12.0f, -6.0f, -29.0f);
    glVertex3f(12.5f, -3.0f, -25.0f);

    // Front face  (z = -25.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(12.5f, -3.0f, -25.0f);
    glVertex3f(12.5f, 0.0f, -25.0f);
    glVertex3f(9.5f, 0.0f, -25.0f);
    glVertex3f(9.5f, -3.0f, -25.0f);

    // Back face (z = -29.0f, z = -31.0f)
    glVertex3f(10.0f, -6.0f, -29.0f);
    glVertex3f(10.0f, -5.0f, -31.0f);
    glVertex3f(12.0f, -5.0f, -31.0f);
    glVertex3f(12.0f, -6.0f, -29.0f);

    // Left face (x = 9.5f, x = 10.0f)
    glVertex3f(9.5f, -3.0f, -25.0f);
    glVertex3f(10.0f, -6.0f, -29.0f);
    glVertex3f(10.0f, -5.0f, -31.0f);
    glVertex3f(9.5f, 0.0f, -25.0f);

    // Right face (x = 12.5f, x = 12.0f)
    glVertex3f(12.5f, 0.0f, -25.0f);
    glVertex3f(12.0f, -5.0f, -31.0f);
    glVertex3f(12.0f, -6.0f, -29.0f);
    glVertex3f(12.5f, -3.0f, -25.0f);

    // R3
    // Top face (y = -5.0f, y = -6.0f)
    glVertex3f(10.0f, -5.0f, -31.0f);
    glVertex3f(10.0f, -6.0f, -29.0f);
    glVertex3f(12.0f, -6.0f, -29.0f);
    glVertex3f(12.0f, -5.0f, -31.0f);

    // Bottom face (y = -8.0f)
    glVertex3f(12.0f, -8.0f, -31.0f);
    glVertex3f(12.0f, -8.0f, -29.0f);
    glVertex3f(10.0f, -8.0f, -29.0f);
    glVertex3f(10.0f, -8.0f, -31.0f);

    // Front face  (z = -29.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(10.0f, -6.0f, -29.0f);
    glVertex3f(10.0f, -8.0f, -29.0f);
    glVertex3f(12.0f, -8.0f, -29.0f);
    glVertex3f(12.0f, -6.0f, -29.0f);

    // Back face (z = -31.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(12.0f, -5.0f, -31.0f);
    glVertex3f(12.0f, -8.0f, -31.0f);
    glVertex3f(10.0f, -8.0f, -31.0f);
    glVertex3f(10.0f, -5.0f, -31.0f);

    // Left face (x = 10.0f)
    glVertex3f(10.0f, -5.0f, -31.0f);
    glVertex3f(10.0f, -6.0f, -29.0f);
    glVertex3f(10.0f, -8.0f, -29.0f);
    glVertex3f(10.0f, -8.0f, -31.0f);

    // Right face (x = 12.0f)
    glVertex3f(12.0f, -5.0f, -31.0f);
    glVertex3f(12.0f, -8.0f, -31.0f);
    glVertex3f(12.0f, -8.0f, -29.0f);
    glVertex3f(12.0f, -6.0f, -29.0f);

    glEnd();  // End of drawing ring finger
}

void drawRightPinky() {
    glBegin(GL_QUADS); // Begin drawing the pinky
    glColor3f(1.0f, 0.95f, 0.86f);

    // P1
    // Top face (y = 0.0f)
    glVertex3f(16.0f, 0.0f, -18.0f);
    glVertex3f(16.0f, 0.0f, -23.0f);
    glVertex3f(13.0f, 0.0f, -23.0f);
    glVertex3f(13.0f, 0.0f, -18.0f);

    // Bottom face (y = -3.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(16.0f, -3.0f, -18.0f);
    glVertex3f(13.0f, -3.0f, -18.0f);
    glVertex3f(13.0f, -3.0f, -23.0f);
    glVertex3f(16.0f, -3.0f, -23.0f);

    // Front face  (z = -18.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(16.0f, -3.0f, -18.0f);
    glVertex3f(16.0f, 0.0f, -18.0f);
    glVertex3f(13.0f, 0.0f, -18.0f);
    glVertex3f(13.0f, -3.0f, -18.0f);

    // Back face (z = -23.0f)
    glVertex3f(16.0f, -3.0f, -23.0f);
    glVertex3f(13.0f, -3.0f, -23.0f);
    glVertex3f(13.0f, 0.0f, -23.0f);
    glVertex3f(16.0f, 0.0f, -23.0f);

    // Left face (x = 13.0f)
    glVertex3f(13.0f, -3.0f, -18.0f);
    glVertex3f(13.0f, -3.0f, -23.0f);
    glVertex3f(13.0f, 0.0f, -23.0f);
    glVertex3f(13.0f, 0.0f, -18.0f);

    // Right face (x = 16.0f)
    glVertex3f(16.0f, -3.0f, -18.0f);
    glVertex3f(16.0f, 0.0f, -18.0f);
    glVertex3f(16.0f, 0.0f, -23.0f);
    glVertex3f(16.0f, -3.0f, -23.0f);

    // P2
    // Top face (y = 0.0f, y = -5.0f)
    glVertex3f(16.0f, 0.0f, -23.0f);
    glVertex3f(15.5f, -5.0f, -29.0f);
    glVertex3f(13.5f, -5.0f, -29.0f);
    glVertex3f(13.0f, 0.0f, -23.0f);

    // Bottom face (y = -3.0f, y = -6.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(13.0f, -3.0f, -23.0f);
    glVertex3f(13.5f, -6.0f, -27.0f);
    glVertex3f(15.5f, -6.0f, -27.0f);
    glVertex3f(16.0f, -3.0f, -23.0f);

    // Front face  (z = -23.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(16.0f, -3.0f, -23.0f);
    glVertex3f(16.0f, 0.0f, -23.0f);
    glVertex3f(13.0f, 0.0f, -23.0f);
    glVertex3f(13.0f, -3.0f, -23.0f);

    // Back face (z = -27.0f, z = -29.0f)
    glVertex3f(13.5f, -6.0f, -27.0f);
    glVertex3f(13.5f, -5.0f, -29.0f);
    glVertex3f(15.5f, -5.0f, -29.0f);
    glVertex3f(15.5f, -6.0f, -27.0f);

    // Left face (x = 13.0f, x = 13.5f)
    glVertex3f(13.0f, -3.0f, -23.0f);
    glVertex3f(13.5f, -6.0f, -27.0f);
    glVertex3f(13.5f, -5.0f, -29.0f);
    glVertex3f(13.0f, 0.0f, -23.0f);

    // Right face (x = 16.0f, x = 15.5f)
    glVertex3f(16.0f, 0.0f, -23.0f);
    glVertex3f(15.5f, -5.0f, -29.0f);
    glVertex3f(15.5f, -6.0f, -27.0f);
    glVertex3f(16.0f, -3.0f, -23.0f);

    // P3
    // Top face (y = 5.0f, y = 6.0f)
    glVertex3f(13.5f, -5.0f, -29.0f);
    glVertex3f(13.5f, -6.0f, -27.0f);
    glVertex3f(15.5f, -6.0f, -27.0f);
    glVertex3f(15.5f, -5.0f, -29.0f);

    // Bottom face (y = -8.0f)
    glVertex3f(15.5f, -8.0f, -29.0f);
    glVertex3f(15.5f, -8.0f, -27.0f);
    glVertex3f(13.5f, -8.0f, -27.0f);
    glVertex3f(13.5f, -8.0f, -29.0f);

    // Front face  (z = -27.0f)
    glColor3f(0.47f, 0.45f, 0.4f);
    glVertex3f(13.5f, -6.0f, -27.0f);
    glVertex3f(13.5f, -8.0f, -27.0f);
    glVertex3f(15.5f, -8.0f, -27.0f);
    glVertex3f(15.5f, -6.0f, -27.0f);

    // Back face (z = -29.0f)
    glColor3f(1.0f, 0.95f, 0.86f);
    glVertex3f(15.5f, -5.0f, -29.0f);
    glVertex3f(15.5f, -8.0f, -29.0f);
    glVertex3f(13.5f, -8.0f, -29.0f);
    glVertex3f(13.5f, -5.0f, -29.0f);

    // Left face (x = 13.5f)
    glVertex3f(13.5f, -5.0f, -29.0f);
    glVertex3f(13.5f, -8.0f, -29.0f);
    glVertex3f(13.5f, -8.0f, -27.0f);
    glVertex3f(13.5f, -6.0f, -27.0f);

    // Right face (x = 15.5f)
    glVertex3f(15.5f, -5.0f, -29.0f);
    glVertex3f(15.5f, -6.0f, -27.0f);
    glVertex3f(15.5f, -8.0f, -27.0f);
    glVertex3f(15.5f, -8.0f, -29.0f);

    glEnd();  // End of drawing pinky
}


/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    // Define the light properties
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_specular[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_position[] = { 1.0, 20.0, 10.0, 1.0 };

    // Enable lighting and set light properties
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glShadeModel(GL_SMOOTH);

    // Enable lighting calculations for each vertex
    glEnable(GL_COLOR_MATERIAL);

    // Set material properties for objects
    GLfloat material_ambient[] = { 1.0, 1.0, 0.0, 1.0 };
    GLfloat material_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat material_shininess[] = { 10.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
    glLoadIdentity();               // Reset the model-view matrix

    // Set up the viewing transformation
    gluLookAt(0.0, 25.0, -60.0,     // eye position
        0.0, 0.0, 0.0,              // center position
        0.0, 1.0, 0.0);             // up direction

    glTranslatef(translateX, translateY, translateZ);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

    // First octave of white keys
    glPushMatrix();

    glRotatef((GLfloat)C1Angle, 8.0, 0.0, 1.0);
    glTranslatef(0.0f, Piano, 0.0f);
    drawC1();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)D1Angle, 8.0, 0.0, 1.0);
    glTranslatef(0.0f, Piano, 0.0f);
    drawD1();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)E1Angle, 8.0, 0.0, 1.0);
    glTranslatef(0.0f, Piano, 0.0f);
    drawE1();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)F1Angle, 8.0, 0.0, 1.0);
    glTranslatef(0.0f, Piano, 0.0f);
    drawF1();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)G1Angle, 8.0, 0.0, 1.0);
    glTranslatef(0.0f, Piano, 0.0f);
    drawG1();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)A1Angle, 8.0, 0.0, 1.0);
    glTranslatef(0.0f, Piano, 0.0f);
    drawA1();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)B1Angle, 8.0, 0.0, 1.0);
    glTranslatef(0.0f, Piano, 0.0f);
    drawB1();
    glPopMatrix();

    // Second octave of white keys
    glPushMatrix();
    glRotatef((GLfloat)C2Angle, 8.0, 0.0, 1.0);
    glTranslatef(0.0f, Piano, 0.0f);
    drawC2();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)D2Angle, 8.0, 0.0, 1.0);
    glTranslatef(0.0f, Piano, 0.0f);
    drawD2();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)E2Angle, 8.0, 0.0, 1.0);
    glTranslatef(0.0f, Piano, 0.0f);
    drawE2();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)F2Angle, 8.0, 0.0, 1.0);
    glTranslatef(0.0f, Piano, 0.0f);
    drawF2();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)G2Angle, 8.0, 0.0, 1.0);
    glTranslatef(0.0f, Piano, 0.0f);
    drawG2();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)A2Angle, 8.0, 0.0, 1.0);
    glTranslatef(0.0f, Piano, 0.0f);
    drawA2();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)B2Angle, 8.0, 0.0, 1.0);
    glTranslatef(0.0f, Piano, 0.0f);
    drawB2();
    glPopMatrix();

    // First octave of black keys
    glPushMatrix();
    glRotatef((GLfloat)Db1Angle, 1000.0, 0.0, 1.0);
    glTranslatef(0.0, Db1AngleDown, 0.0);
    drawDb1();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)Eb1Angle, 1000.0, 0.0, 1.0);
    glTranslatef(0.0, Eb1AngleDown, 0.0);
    drawEb1();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)Gb1Angle, 1000.0, 0.0, 1.0);
    glTranslatef(0.0, Gb1AngleDown, 0.0);
    drawGb1();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)Ab1Angle, 1000.0, 0.0, 1.0);
    glTranslatef(0.0, Ab1AngleDown, 0.0);
    drawAb1();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)Bb1Angle, 1000.0, 0.0, 1.0);
    glTranslatef(0.0, Bb1AngleDown, 0.0);
    drawBb1();
    glPopMatrix();

    // Second octave of black keys
    glPushMatrix();
    glRotatef((GLfloat)Db2Angle, 1000.0, 0.0, 1.0);
    glTranslatef(0.0, Db2AngleDown, 0.0);
    drawDb2();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)Eb2Angle, 1000.0, 0.0, 1.0);
    glTranslatef(0.0, Eb2AngleDown, 0.0);
    drawEb2();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)Gb2Angle, 1000.0, 0.0, 1.0);
    glTranslatef(0.0, Gb2AngleDown, 0.0);
    drawGb2();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)Ab2Angle, 1000.0, 0.0, 1.0);
    glTranslatef(0.0, Ab2AngleDown, 0.0);
    drawAb2();
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat)Bb2Angle, 1000.0, 0.0, 1.0);
    glTranslatef(0.0, Bb2AngleDown, 0.0);
    drawBb2();
    glPopMatrix();

    // Draw left hand
    glPushMatrix();

    glScalef(0.85, 1.0, 0.5f);
    glTranslatef(-8.0f, 11.5f, 33.0f);
    glTranslatef(LeftMoveX, LeftMoveY, LeftMoveZ);
    drawLeftPalm();

    glPopMatrix();

    glPushMatrix();
    glScalef(0.85, 1.0, 0.5f);
    glTranslatef(-8.0f, 11.5f, 33.0f);
    glTranslatef(LeftMoveX, LeftMoveY, LeftMoveZ);
    glRotatef((GLfloat)LeftThumb, 8.0, 0.0, 1.0);
    drawLeftThumb();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.85, 1.0, 0.5f);
    glTranslatef(-8.0f, 11.5f, 16.5f);
    glTranslatef(LeftMoveX, LeftMoveY, LeftMoveZ);
    glRotatef((GLfloat)LeftIndex, 8.0, 0.0, 1.0);
    glTranslatef(0.0f, 0.0f, 16.5f);
    drawLeftIndex();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.85, 1.0, 0.5f);
    glTranslatef(-8.0f, 11.5f, 16.5f);
    glTranslatef(LeftMoveX, LeftMoveY, LeftMoveZ);
    glRotatef((GLfloat)LeftMiddle, 8.0, 0.0, 1.0);
    glTranslatef(0.0f, 0.0f, 16.5f);
    drawLeftMiddle();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.85, 1.0, 0.5f);
    glTranslatef(-8.0f, 11.5f, 16.5f);
    glTranslatef(LeftMoveX, LeftMoveY, LeftMoveZ);
    glRotatef((GLfloat)LeftRing, 8.0, 0.0, 1.0);
    glTranslatef(0.0f, 0.0f, 16.5f);
    drawLeftRing();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.85, 1.0, 0.5f);
    glTranslatef(-8.0f, 11.5f, 16.5f);
    glTranslatef(LeftMoveX, LeftMoveY, LeftMoveZ);
    glRotatef((GLfloat)LeftPinky, 8.0, 0.0, 1.0);
    glTranslatef(0.0f, 0.0f, 16.5f);
    drawLeftPinky();
    glPopMatrix();

    // Draw right hand
    glPushMatrix();

    glScalef(0.85, 1.0, 0.5f);
    glTranslatef(8.0f, 11.5f, 15.0f);
    glTranslatef(RightMoveX, RightMoveY, RightMoveZ);
    glTranslatef(0.0f, 0.0f, 18.0f);
    drawRightPalm();

    glPopMatrix();

    glPushMatrix();

    glScalef(0.85, 1.0, 0.5f);
    glTranslatef(8.0f, 11.5f, 33.0f);
    glRotatef((GLfloat)RightThumb, 8.0, 0.0, 1.0);
    glTranslatef(RightMoveX, RightMoveY, RightMoveZ);
    drawRightThumb();

    glPopMatrix();

    glPushMatrix();
    glScalef(0.85, 1.0, 0.5f);
    glTranslatef(8.0f, 11.5f, 16.5f);
    glRotatef((GLfloat)RightIndex, 8.0, 0.0, 1.0);
    glTranslatef(RightMoveX, RightMoveY, RightMoveZ);
    glTranslatef(0.0f, 0.0f, 16.5f);
    drawRightIndex();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.85, 1.0, 0.5f);
    glTranslatef(8.0f, 11.5f, 16.5f);
    glRotatef((GLfloat)RightMiddle, 8.0, 0.0, 1.0);
    glTranslatef(RightMoveX, RightMoveY, RightMoveZ);
    glTranslatef(0.0f, 0.0f, 16.5f);
    drawRightMiddle();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.85, 1.0, 0.5f);
    glTranslatef(8.0f, 11.5f, 16.5f);
    glRotatef((GLfloat)RightRing, 8.0, 0.0, 1.0);
    glTranslatef(RightMoveX, RightMoveY, RightMoveZ);
    glTranslatef(0.0f, 0.0f, 16.5f);
    drawRightRing();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.85, 1.0, 0.5f);
    glTranslatef(8.0f, 11.5f, 13.0f);
    glRotatef((GLfloat)RightPinky, 8.0, 0.0, 1.0);
    glTranslatef(RightMoveX, RightMoveY, RightMoveZ);
    glTranslatef(0.0f, 0.0f, 20.0f);
    drawRightPinky();
    glPopMatrix();


    glFlush();
    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;    // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset

    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void mouseMovement(int x, int y) {
    if (!isPaused && isMouseLeftButtonClicked) {
        int deltaX = x - lastMouseX;
        int deltaY = y - lastMouseY;

        // Update translation variables based on mouse movement
        rotationX += static_cast<GLfloat>(deltaY) / 3.0f;
        rotationY += static_cast<GLfloat>(deltaX) / 3.0f;

        glutPostRedisplay();
    }

    lastMouseX = x;
    lastMouseY = y;
}

/* Handler for mouse click event */
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isMouseLeftButtonClicked = true;
            lastMouseX = x;
            lastMouseY = y;
        }
        else if (state == GLUT_UP) {
            isMouseLeftButtonClicked = false;
        }
    }
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    glutInit(&argc, argv);          // Initialize GLUT
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1200, 600);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow("5YNDROME - 3D Hands Playing Piano");  // Create window with the given title
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    glutKeyboardFunc(keyboardInput);
    glutKeyboardUpFunc(keyReleased);
    glutMotionFunc(mouseMovement);
    glutMouseFunc(mouseClick);
    initGL();                       // Our own OpenGL initialization
    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}