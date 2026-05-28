#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// ========================================
// GAME VARIABLES
// ========================================
float roadSpeed = 2.0f;
float lineOffset = 0.0f;

float playerX = 0.0f;
float playerY = -150.0f;
float playerSpeed = 6.0f;

// 3 enemies
float enemyX[3];
float enemyY[3];
float enemySpeed[3];
float enemyColor[3][3];

// 3 coins
float coinX[3];
float coinY[3];
bool coinActive[3];

int score = 0;
int lives = 3;
bool gameOver = false;
bool gameStart = true;
float difficultyTimer = 0.0f;

// ========================================
// DRAW TEXT
// ========================================
void drawText(float x, float y, string text) {
    glRasterPos2f(x, y);
    for (int i = 0; i < text.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

void drawSmallText(float x, float y, string text) {
    glRasterPos2f(x, y);
    for (int i = 0; i < text.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}

// ========================================
// CIRCLE
// ========================================
void circle(float cx, float cy, float r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float pi = 3.1416f;
        float A = (i * 2 * pi) / 180;
        glVertex2f(r * cos(A) + cx, r * sin(A) + cy);
    }
    glEnd();
}

// ========================================
// PLAYER CAR
// ========================================
void drawPlayerCar(float x, float y) {
    // body
    glColor3f(0.0f, 0.5f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(x - 18, y - 30);
        glVertex2f(x + 18, y - 30);
        glVertex2f(x + 18, y + 30);
        glVertex2f(x - 18, y + 30);
    glEnd();

    // cabin
    glColor3f(0.5f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(x - 12, y - 12);
        glVertex2f(x + 12, y - 12);
        glVertex2f(x + 12, y + 12);
        glVertex2f(x - 12, y + 12);
    glEnd();

    // front windshield
    glColor3f(0.7f, 0.9f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(x - 10, y + 10);
        glVertex2f(x + 10, y + 10);
        glVertex2f(x + 10, y + 20);
        glVertex2f(x - 10, y + 20);
    glEnd();

    // headlights
    glColor3f(1.0f, 1.0f, 0.6f);
    glBegin(GL_QUADS);
        glVertex2f(x - 18, y + 22);
        glVertex2f(x - 8,  y + 22);
        glVertex2f(x - 8,  y + 30);
        glVertex2f(x - 18, y + 30);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x + 8,  y + 22);
        glVertex2f(x + 18, y + 22);
        glVertex2f(x + 18, y + 30);
        glVertex2f(x + 8,  y + 30);
    glEnd();

    // tail lights
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(x - 18, y - 30);
        glVertex2f(x - 8,  y - 30);
        glVertex2f(x - 8,  y - 22);
        glVertex2f(x - 18, y - 22);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x + 8,  y - 30);
        glVertex2f(x + 18, y - 30);
        glVertex2f(x + 18, y - 22);
        glVertex2f(x + 8,  y - 22);
    glEnd();

    // wheels
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(x - 22, y + 15);
        glVertex2f(x - 18, y + 15);
        glVertex2f(x - 18, y + 25);
        glVertex2f(x - 22, y + 25);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x + 18, y + 15);
        glVertex2f(x + 22, y + 15);
        glVertex2f(x + 22, y + 25);
        glVertex2f(x + 18, y + 25);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x - 22, y - 25);
        glVertex2f(x - 18, y - 25);
        glVertex2f(x - 18, y - 15);
        glVertex2f(x - 22, y - 15);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x + 18, y - 25);
        glVertex2f(x + 22, y - 25);
        glVertex2f(x + 22, y - 15);
        glVertex2f(x + 18, y - 15);
    glEnd();
}

// ========================================
// ENEMY CAR
// ========================================
void drawEnemyCar(float x, float y, float r, float g, float b) {
    // body
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x - 18, y - 30);
        glVertex2f(x + 18, y - 30);
        glVertex2f(x + 18, y + 30);
        glVertex2f(x - 18, y + 30);
    glEnd();

    // cabin
    glColor3f(r * 0.6f, g * 0.6f, b * 0.6f);
    glBegin(GL_QUADS);
        glVertex2f(x - 12, y - 12);
        glVertex2f(x + 12, y - 12);
        glVertex2f(x + 12, y + 12);
        glVertex2f(x - 12, y + 12);
    glEnd();

    // windshield
    glColor3f(0.7f, 0.9f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(x - 10, y - 20);
        glVertex2f(x + 10, y - 20);
        glVertex2f(x + 10, y - 10);
        glVertex2f(x - 10, y - 10);
    glEnd();

    // headlights
    glColor3f(1.0f, 1.0f, 0.6f);
    glBegin(GL_QUADS);
        glVertex2f(x - 18, y - 30);
        glVertex2f(x - 8,  y - 30);
        glVertex2f(x - 8,  y - 22);
        glVertex2f(x - 18, y - 22);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x + 8,  y - 30);
        glVertex2f(x + 18, y - 30);
        glVertex2f(x + 18, y - 22);
        glVertex2f(x + 8,  y - 22);
    glEnd();

    // tail lights
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(x - 18, y + 22);
        glVertex2f(x - 8,  y + 22);
        glVertex2f(x - 8,  y + 30);
        glVertex2f(x - 18, y + 30);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x + 8,  y + 22);
        glVertex2f(x + 18, y + 22);
        glVertex2f(x + 18, y + 30);
        glVertex2f(x + 8,  y + 30);
    glEnd();

    // wheels
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(x - 22, y + 15);
        glVertex2f(x - 18, y + 15);
        glVertex2f(x - 18, y + 25);
        glVertex2f(x - 22, y + 25);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x + 18, y + 15);
        glVertex2f(x + 22, y + 15);
        glVertex2f(x + 22, y + 25);
        glVertex2f(x + 18, y + 25);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x - 22, y - 25);
        glVertex2f(x - 18, y - 25);
        glVertex2f(x - 18, y - 15);
        glVertex2f(x - 22, y - 15);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x + 18, y - 25);
        glVertex2f(x + 22, y - 25);
        glVertex2f(x + 22, y - 15);
        glVertex2f(x + 18, y - 15);
    glEnd();
}

// ========================================
// INIT ENEMY
// ========================================
void initEnemy(int i) {
    // 3 lanes: left=-90, center=0, right=90
    int lane = rand() % 3;
    if (lane == 0)      enemyX[i] = -90.0f;
    else if (lane == 1) enemyX[i] =   0.0f;
    else                enemyX[i] =  90.0f;

    // big Y gap so enemies dont stack up
    enemyY[i] = 300.0f + (rand() % 500);
    enemySpeed[i] = 1.0f + (rand() % 2);

    int c = rand() % 5;
    if      (c == 0) { enemyColor[i][0]=1.0f; enemyColor[i][1]=0.2f; enemyColor[i][2]=0.2f; }
    else if (c == 1) { enemyColor[i][0]=0.2f; enemyColor[i][1]=0.8f; enemyColor[i][2]=0.2f; }
    else if (c == 2) { enemyColor[i][0]=1.0f; enemyColor[i][1]=0.6f; enemyColor[i][2]=0.0f; }
    else if (c == 3) { enemyColor[i][0]=0.8f; enemyColor[i][1]=0.0f; enemyColor[i][2]=0.8f; }
    else             { enemyColor[i][0]=1.0f; enemyColor[i][1]=1.0f; enemyColor[i][2]=0.0f; }
}

// ========================================
// INIT COIN
// ========================================
void initCoin(int i) {
    int lane = rand() % 3;
    if (lane == 0)      coinX[i] = -90.0f;
    else if (lane == 1) coinX[i] =   0.0f;
    else                coinX[i] =  90.0f;
    coinY[i] = 300.0f + (rand() % 500);
    coinActive[i] = true;
}

// ========================================
// INIT GAME
// ========================================
void initGame() {
    srand(time(0));
    playerX = 0.0f;
    playerY = -150.0f;
    score = 0;
    lives = 3;
    gameOver = false;
    roadSpeed = 2.0f;
    lineOffset = 0.0f;
    difficultyTimer = 0.0f;

    for (int i = 0; i < 3; i++) initEnemy(i);
    for (int i = 0; i < 3; i++) initCoin(i);
}

// ========================================
// COLLISION CHECK
// ========================================
bool checkCollision(float x1, float y1,
                    float x2, float y2,
                    float w,  float h) {
    return (x1 > x2 - w && x1 < x2 + w &&
            y1 > y2 - h && y1 < y2 + h);
}

// ========================================
// DISPLAY
// ========================================
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -250, 250);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // ---- START SCREEN ----
    if (gameStart) {
        glColor3f(0.05f, 0.05f, 0.15f);
        glBegin(GL_QUADS);
            glVertex2f(-200, -250);
            glVertex2f( 200, -250);
            glVertex2f( 200,  250);
            glVertex2f(-200,  250);
        glEnd();

        glColor3f(1.0f, 0.8f, 0.0f);
        drawText(-95, 100, "CAR RACING GAME");

        glColor3f(0.0f, 1.0f, 0.5f);
        drawText(-70, 50, "HOW TO PLAY:");

        glColor3f(1.0f, 1.0f, 1.0f);
        drawText(-130,  15, "LEFT / RIGHT Arrow  - Move your car");
        drawText(-130, -15, "UP Arrow            - Speed up");
        drawText(-130, -45, "DOWN Arrow          - Slow down");
        drawText(-130, -75, "R                   - Restart");
        drawText(-130,-105, "ESC                 - Quit");

        glColor3f(1.0f, 0.85f, 0.0f);
        drawText(-80, -155, "Collect coins = +20");
        drawText(-80, -180, "Overtake cars = +10");
        drawText(-80, -205, "Avoid crash   = +5");

        glColor3f(1.0f, 0.3f, 0.3f);
        drawText(-95, -235, "Press ENTER to Start!");

        glutSwapBuffers();
        return;
    }

    // ---- GAME OVER SCREEN ----
    if (gameOver) {
        glColor3f(0.08f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(-200, -250);
            glVertex2f( 200, -250);
            glVertex2f( 200,  250);
            glVertex2f(-200,  250);
        glEnd();

        glColor3f(1.0f, 0.0f, 0.0f);
        drawText(-70, 80, "GAME OVER!");

        glColor3f(1.0f, 1.0f, 1.0f);
        drawText(-90, 30, "Final Score: " + to_string(score));

        if (score >= 200)
            glColor3f(1.0f, 0.85f, 0.0f);
        else
            glColor3f(0.7f, 0.7f, 0.7f);

        if      (score >= 500) drawText(-80,  -20, "Rank: LEGEND!");
        else if (score >= 300) drawText(-80,  -20, "Rank: PRO!");
        else if (score >= 100) drawText(-80,  -20, "Rank: GOOD!");
        else                   drawText(-80,  -20, "Rank: BEGINNER");

        glColor3f(0.0f, 1.0f, 0.5f);
        drawText(-90, -80, "Press R   - Restart");
        drawText(-90,-110, "Press ESC - Quit");

        glutSwapBuffers();
        return;
    }

    // ========================================
    // GRASS LEFT
    // ========================================
    glColor3f(0.15f, 0.50f, 0.10f);
    glBegin(GL_QUADS);
        glVertex2f(-200, -250);
        glVertex2f(-130, -250);
        glVertex2f(-130,  250);
        glVertex2f(-200,  250);
    glEnd();

    // GRASS RIGHT
    glBegin(GL_QUADS);
        glVertex2f( 130, -250);
        glVertex2f( 200, -250);
        glVertex2f( 200,  250);
        glVertex2f( 130,  250);
    glEnd();

    // ROAD
    glColor3f(0.22f, 0.22f, 0.22f);
    glBegin(GL_QUADS);
        glVertex2f(-130, -250);
        glVertex2f( 130, -250);
        glVertex2f( 130,  250);
        glVertex2f(-130,  250);
    glEnd();

    // ROAD BORDER LEFT
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-130, -250);
        glVertex2f(-124, -250);
        glVertex2f(-124,  250);
        glVertex2f(-130,  250);
    glEnd();

    // ROAD BORDER RIGHT
    glBegin(GL_QUADS);
        glVertex2f( 124, -250);
        glVertex2f( 130, -250);
        glVertex2f( 130,  250);
        glVertex2f( 124,  250);
    glEnd();

    // LANE DIVIDER LEFT (dashed)
    glColor3f(1.0f, 1.0f, 0.0f);
    for (float y = -250 + lineOffset; y < 250; y += 60) {
        glBegin(GL_QUADS);
            glVertex2f(-45, y);
            glVertex2f(-40, y);
            glVertex2f(-40, y + 35);
            glVertex2f(-45, y + 35);
        glEnd();
    }

    // LANE DIVIDER RIGHT (dashed)
    for (float y = -250 + lineOffset; y < 250; y += 60) {
        glBegin(GL_QUADS);
            glVertex2f(40, y);
            glVertex2f(45, y);
            glVertex2f(45, y + 35);
            glVertex2f(40, y + 35);
        glEnd();
    }

    // TREES LEFT GRASS
    glColor3f(0.10f, 0.40f, 0.08f);
    for (float ty = -230 + (lineOffset * 0.3f); ty < 260; ty += 130) {
        circle(-155, ty,      18);
        circle(-170, ty + 55, 15);
    }

    // TREES RIGHT GRASS
    for (float ty = -180 + (lineOffset * 0.3f); ty < 260; ty += 130) {
        circle(155, ty,      18);
        circle(170, ty + 55, 15);
    }

    // ========================================
    // COINS
    // ========================================
    for (int i = 0; i < 3; i++) {
        if (coinActive[i]) {
            glColor3f(1.0f, 0.85f, 0.0f);
            circle(coinX[i], coinY[i], 10);
            glColor3f(1.0f, 1.0f, 0.5f);
            circle(coinX[i], coinY[i], 6);
            glColor3f(0.8f, 0.5f, 0.0f);
            drawSmallText(coinX[i] - 3, coinY[i] - 4, "$");
        }
    }

    // ========================================
    // ENEMY CARS
    // ========================================
    for (int i = 0; i < 3; i++) {
        drawEnemyCar(enemyX[i], enemyY[i],
                     enemyColor[i][0],
                     enemyColor[i][1],
                     enemyColor[i][2]);
    }

    // ========================================
    // PLAYER CAR
    // ========================================
    drawPlayerCar(playerX, playerY);

    // ========================================
    // HUD BACKGROUND
    // ========================================
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-200, 210);
        glVertex2f( 200, 210);
        glVertex2f( 200, 250);
        glVertex2f(-200, 250);
    glEnd();

    // HUD BORDER
    glColor3f(0.0f, 0.8f, 1.0f);
    glBegin(GL_LINES);
        glVertex2f(-200, 210);
        glVertex2f( 200, 210);
    glEnd();

    // SCORE
    glColor3f(1.0f, 1.0f, 0.0f);
    drawText(-190, 225, "SCORE: " + to_string(score));

    // SPEED
    glColor3f(0.5f, 1.0f, 0.5f);
    drawText(-40, 225, "SPD: " + to_string((int)roadSpeed));

    // LIVES
    glColor3f(1.0f, 0.3f, 0.3f);
    drawText(70, 225, "LIVES:");
    for (int i = 0; i < lives; i++) {
        circle(135 + i * 22, 233, 7);
    }

    glutSwapBuffers();
}

// ========================================
// UPDATE
// ========================================
void update(int value) {
    if (gameOver || gameStart) {
        glutPostRedisplay();
        glutTimerFunc(16, update, 0);
        return;
    }

    // scroll road lines
    lineOffset -= roadSpeed;
    if (lineOffset < -60.0f) lineOffset = 0.0f;

    // difficulty increases every 10 seconds
    difficultyTimer += 0.016f;
    if (difficultyTimer > 10.0f) {
        roadSpeed += 0.2f;
        if (roadSpeed > 10.0f) roadSpeed = 10.0f;
        difficultyTimer = 0.0f;
        score += 5; // survival bonus
    }

    // update enemies
    for (int i = 0; i < 3; i++) {
        enemyY[i] -= (roadSpeed + enemySpeed[i]) * 0.5f;

        // overtake score
        if (enemyY[i] < playerY - 38 &&
            enemyY[i] > playerY - 43) {
            score += 10;
        }

        // enemy off screen — reset
        if (enemyY[i] < -290.0f) {
            initEnemy(i);
            score += 5;
        }

        // collision
        if (checkCollision(playerX, playerY,
                           enemyX[i], enemyY[i],
                           32, 55)) {
            lives--;
            initEnemy(i);
            enemyY[i] = 350.0f;
            if (lives <= 0) gameOver = true;
        }
    }

    // update coins
    for (int i = 0; i < 3; i++) {
        if (coinActive[i]) {
            coinY[i] -= roadSpeed * 0.5f;

            // coin collected
            if (checkCollision(playerX, playerY,
                               coinX[i], coinY[i],
                               22, 22)) {
                coinActive[i] = false;
                score += 20;
            }

            // coin off screen — reset
            if (coinY[i] < -290.0f) {
                initCoin(i);
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// ========================================
// KEYBOARD
// ========================================
void keyboardInput(unsigned char key, int x, int y) {
    if (key == 13) { // ENTER
        if (gameStart) {
            gameStart = false;
            initGame();
        }
    }
    if (key == 'r' || key == 'R') {
        gameStart = false;
        initGame();
    }
    if (key == 27) exit(0);
}

// ========================================
// ARROW KEYS
// ========================================
void specialKeyInput(int key, int x, int y) {
    if (gameOver || gameStart) return;

    if (key == GLUT_KEY_LEFT) {
        playerX -= playerSpeed;
        if (playerX < -105.0f) playerX = -105.0f;
    }
    if (key == GLUT_KEY_RIGHT) {
        playerX += playerSpeed;
        if (playerX > 105.0f) playerX = 105.0f;
    }
    if (key == GLUT_KEY_UP) {
        roadSpeed += 0.5f;
        if (roadSpeed > 10.0f) roadSpeed = 10.0f;
    }
    if (key == GLUT_KEY_DOWN) {
        roadSpeed -= 0.5f;
        if (roadSpeed < 1.0f) roadSpeed = 1.0f;
    }
}

// ========================================
// MAIN
// ========================================
int main(int argc, char** argv) {
    cout << "========================================" << endl;
    cout << "      CAR RACING GAME - CONTROLS        " << endl;
    cout << "========================================" << endl;
    cout << " ENTER       - Start game               " << endl;
    cout << " LEFT        - Move car left            " << endl;
    cout << " RIGHT       - Move car right           " << endl;
    cout << " UP          - Speed up                 " << endl;
    cout << " DOWN        - Slow down                " << endl;
    cout << " R           - Restart                  " << endl;
    cout << " ESC         - Quit                     " << endl;
    cout << "========================================" << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 600);
    glutInitWindowPosition(400, 50);
    glutCreateWindow("Car Racing Game");

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardInput);
    glutSpecialFunc(specialKeyInput);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
