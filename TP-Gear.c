#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "model/props/props.h"
#include "model/pista/pista.h"

int windowWidth = 1280;
int windowHeight = 720;

int keyState[256];

//Variáveis look at
long double pyE = 3, ayE=-0.000008, pzE=5, vzE=-0.001, vyE=0;
int a, qtempo=0, t;
int tc1=0, tc2=1;
double eyeX=0, eyeY=2, eyeZ=-10, centerX=0, centerY=0, centerZ=0, upX=0, upY=1, upZ=0;
int slices = 32;
int stacks = 32;

void desenhaCena(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(0, 0, 0);
    Vetor origem = {0,0,0};
    Vetor tamanhoPlano = {500, 0, 5000};
    desenhaPista(origem, tamanhoPlano);
    glutSwapBuffers();
}

void posiciona(){
    pzE-=vzE*(t-qtempo);
    pyE+=vyE*(t-qtempo);
    if(pyE<1 && vyE < 0){ // só inverte se tiver embaixo do plano e descendo
        vyE=-vyE;
    }else {
		vyE+=ayE*(t-qtempo); // soh altera a V se n tiver invertido -
	}
    if(pzE<-50 || pzE>-5){
        vzE=-vzE;
    }
}
void comandos(){
    if(keyState['w']==1 || keyState['W']==1){
        centerZ+=1;
        eyeZ+=1;
    }
    if(keyState['s']==1 || keyState['S']==1){
        centerZ-=1;
        eyeZ-=1;
    }
    if(keyState['A']==1 || keyState['a']==1){
        centerX+=1;
        eyeX+=1;
    }
    if(keyState['d']==1 || keyState['D']==1){
        centerX-=1;
        eyeX-=1;
    }
    if(keyState['Q']==1 || keyState['q']==1){
        centerY+=1;
        eyeY+=1;
    }
    if(keyState['e']==1 || keyState['E']==1){
        centerY-=1;
        eyeY-=1;
    }
}

void atualiza(int idx){
    t = glutGet(GLUT_ELAPSED_TIME);
    posiciona();
    comandos();
    qtempo = glutGet(GLUT_ELAPSED_TIME);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ);
    glPopMatrix();
    glutPostRedisplay();
    glutTimerFunc(20, atualiza, 0);
}

void resize(int width, int height)
{
    float razaoaspecto = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-razaoaspecto, razaoaspecto, -1.0, 1.0, 2.0, 500.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
void pressiona(unsigned char key,int x, int y){
    keyState[key]=1;
    switch(key){
        case 27:
            exit(0);
            break;
    }
}
void solta(unsigned char key,int x, int y){
    keyState[key]=0;
}
void inicializa(void){
}


float light_ambient[]  = { 0.5f, 0.5f, 0.5f, 1.0f };
float light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
float light_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
float light_position[] = { 10.0f, 50.0f, 50.0f, 1.0f };

float mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
float mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
float mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
float high_shininess[] = { 100.0f };

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("");

    glutReshapeFunc(resize);
    glutDisplayFunc(desenhaCena);
    glutKeyboardFunc(pressiona);
    glutKeyboardUpFunc(solta);
    glutTimerFunc(0, atualiza, 0);

    glClearColor(0.3,0.5,1,0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return 0;
}
