// #include <GL/freeglut.h>
// #include <GL/gl.h>
#include "game.hpp"
#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
Game game;

void init(void){
    glClearColor(1.0, 1.0, 1.0, 0.0);
}
//func to draw board
void drawBoard(void){
    glViewport(0, 0, 300, 600);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 10, 0, 20);
    for(int y = 0; y<20; y++){
        for(int x = 0; x<10; x++){ 
            if(game.getOccupied(x, y) ^ game.getCurrent(x, y)){
                glColor3f(game.getRed(x, y), game.getGreen(x, y), game.getBlue(x, y));
                glRectd(x, y, x+1, y+1);
            }
            else{
                glColor3f(0.0, 0.0, 0.0);
                glRectd(x, y , x+1, y+1);
            }

        }
    }
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    for(int i = 0; i<20; i++){
        glVertex2f(i, 0.0);
        glVertex2f(i, 20.0);
        glVertex2f(0.0, i);
        glVertex2f(20.0, i);
    }
    glEnd();
    
    glutSwapBuffers();
}
//take keyboard input to move block
void transform(int key, int x, int y){
    switch(key){
        case GLUT_KEY_UP:
            game.rotate();
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            game.translate(-1);
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            game.translate(1);
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            game.moveDown();
            glutPostRedisplay();

    }
}
void quitRestart(unsigned char key, int x, int y){
    switch(key){
        case 'q':
            exit(0);
        case 'r':
            game.restart();
    }
}
//timer function that moves pieces down every 500ms 
void timer(int id){
    if(game.getGameOver() == true){
        game.restart();
    }
    if(id == 0){ //beginning of game
        game.spawnFruits();
    }
    else{
        game.moveDown();
    }
    glutPostRedisplay();
    glutTimerFunc(500, timer, id+1);
}

int main(int argc, char** argv){
    //Shape::init();
    //board = new Board();

    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 500);
    glutInitWindowSize(300, 600);
    glutCreateWindow("Tetris");

    init();
    glutDisplayFunc(drawBoard);
    glutSpecialFunc(transform);
    glutKeyboardFunc(quitRestart);
    glutTimerFunc(500, timer, 0);
    glutMainLoop();
}