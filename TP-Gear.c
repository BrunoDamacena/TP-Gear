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
#include "model/carro/carro.h"

// Objetos
Pista pista;

int windowWidth = 1280;
int windowHeight = 720;

int keyState[256];

//Variáveis look at
long double pyE = 3, ayE=-0.000008, pzE=5, vzE=-0.001, vyE=0;
int a, qtempo=0, t;
int tc1=0, tc2=1;
double eyeX=0, eyeY=10, eyeZ=-25, centerX=0, centerY=0, centerZ=0, upX=0, upY=1, upZ=0;
int slices = 32;
int stacks = 32;

Carro carro;

void desenhaCena(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(0, 0, 0);
    glPushMatrix();
        glTranslatef(0, 0, carro.posicao.z-fmod(carro.posicao.z, pista.dimensoes.depth));
        desenhaPista(&pista);
    glPopMatrix();
    carro_desenhaCarro(&carro);
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
        centerZ++;
        eyeZ++;
        carro.posicao.z++;

    }
    if(keyState['s']==1 || keyState['S']==1){
      if(centerZ>=0){
        centerZ--;
        eyeZ--;
        carro.posicao.z--;
      }
    }

    if(keyState['A']==1 || keyState['a']==1){
        if(centerX<=(25)){
          centerX++;
          eyeX++;
          carro.posicao.x++;
        }

    }
    if(keyState['d']==1 || keyState['D']==1){
      if(centerX>=-25){
        centerX--;
        eyeX--;
        carro.posicao.x--;
      }
    }

    /*
    if(keyState['Q']==1 || keyState['q']==1){
        centerY++;
        eyeY++;
    }
    if(keyState['e']==1 || keyState['E']==1){
        centerY--;
        eyeY--;
    }

    */
}

void atualiza(int idx){
    t = glutGet(GLUT_ELAPSED_TIME);
    posiciona();
    comandos();
    qtempo = glutGet(GLUT_ELAPSED_TIME);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ);
    carro_desenhaCarro();
    glPopMatrix();
    glutPostRedisplay();
    glutTimerFunc(20, atualiza, 0);
}

void redimensiona(int w, int h){
    float razaoaspecto = (float) w / (float) h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-razaoaspecto, razaoaspecto, -1.0, 1.0, 2.0, 5000.0);

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
    pista = criaPista();
    carro = carro_criaCarro();
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
    glutInitWindowSize(windowWidth,windowHeight);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("TPGear - It was supposed to be a game about cars");

    glutReshapeFunc(redimensiona);
    glutDisplayFunc(desenhaCena);
    glutKeyboardFunc(pressiona);
    glutKeyboardUpFunc(solta);
    glutTimerFunc(0, atualiza, 0);
    inicializa();

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
