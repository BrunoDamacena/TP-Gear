#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "model/props/props.h"
#include "model/grama/grama.h"
#include "model/carro/carro.h"
#include "model/pista/pista.h"
#include "model/muro/muro.h"

#define radianoParaGraus(radianos) (radianos * (180.0 / M_PI))
#define grausParaRadianos(graus) ((graus * M_PI) / 180.0)
#define a_value 328

// Objetos
Pista pista;
Carro carro;
ListaCarro *listaCarros;
Grama grama;
Muro muro;

int windowWidth = 1280;
int windowHeight = 720;

int gameMatrix[3][100]; // PISTA E PROFUNDIDADE

int keyState[256];

//Variáveis look at
double eyeX=0, eyeY=10, eyeZ=-25, centerX=0, centerY=0, centerZ=0, upX=0, upY=1, upZ=0;



void desenhaCena(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(0, 0, 0);
    glPushMatrix();
        glTranslatef(0, 0, carro.posicao.z-fmod(carro.posicao.z, grama.dimensoes.depth));
        desenhaGrama(&grama);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 0, carro.posicao.z-fmod(carro.posicao.z, pista.dimensoes.depth));
        desenhaPista(&pista);
    glPopMatrix();
    glPushMatrix();
        glTranslatef((pista.dimensoes.width*2)-(muro.dimensoes.width), 0, carro.posicao.z-fmod(carro.posicao.z, muro.dimensoes.depth));
        muro_desenhaMuro(&muro);
    glPopMatrix();
    glPushMatrix();
        glTranslatef((-pista.dimensoes.width*2)+(muro.dimensoes.width), 0, carro.posicao.z-fmod(carro.posicao.z, muro.dimensoes.depth));
        muro_desenhaMuro(&muro);
    glPopMatrix();
    ListaCarro *_carros = listaCarros;
    int count=0;
    while(_carros != NULL){
        count++;
        glPushMatrix();
            //glTranslatef(_carros->carro.posicao.x, _carros->carro.posicao.y, _carros->carro.posicao.z-(_carros->carro.dimensoes.depth));
            carro_desenhaCarro(&(_carros->carro), (float)(count%3 +1)/4, (float)(count%5 +1)/6, (float)(count%2 +1)/3);

        glPopMatrix();
        _carros = _carros->proximo;
    }
    carro_desenhaCarro(&carro, 1, 1, 0);
    glutSwapBuffers();
}

void comandos(){
    if(keyState['A']==1 || keyState['a']==1){
        if(carro.inclinacao < 24) carro.inclinacao+=2;

    }
    if(keyState['d']==1 || keyState['D']==1){
        if(carro.inclinacao > -24) carro.inclinacao-=2;
    }

    if(!(keyState['A']==1 || keyState['a']==1) && !(keyState['d']==1 || keyState['D']==1)){
        if(carro.inclinacao < 0) carro.inclinacao++;
        if(carro.inclinacao > 0) carro.inclinacao--;
    }
}

void atualizaPosicao(){
    float valZ=cos(grausParaRadianos(carro.inclinacao));
    float valX=sin(grausParaRadianos(carro.inclinacao));
    if(valX > 0 && carro.posicao.x>10) valX=0;
    if(valX < 0 && carro.posicao.x<-10) valX=0;
    centerZ+=valZ;
    eyeZ+=valZ;
    centerX+=valX;
    eyeX+=valX;
    carro.posicao.z+=valZ;
    carro.posicao.x+=valX;
}

void atualiza(int idx){
    ListaCarro *_l = listaCarros;
    while(_l != NULL){
        if(checaColisao(_l->carro, carro)){
            printf("Faliceu\n");
            eyeX=0;
            eyeY=10;
            eyeZ=-25;
            centerX=0;
            centerY=0;
            centerZ=0;
            upX=0;
            upY=1;
            upZ=0;
            carro.posicao.x = 0;
            carro.posicao.y = 0;
            carro.posicao.z = 0;
        }
        _l = _l->proximo;
    }
    comandos();
    atualizaPosicao();

    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ);
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
    int i, k;
    for(i=0;i<3;i++){
        for(k=0;k<a_value;k++){
            gameMatrix[i][k] = 0; // Não tem nada no jogo ainda
        }
    }

    for(k=0;k<a_value; k++){
        if(k%10 == 9){
            if(k%3 == 0){
                gameMatrix[0][k] = 1;
                gameMatrix[1][k] = 0;
                gameMatrix[2][k] = 1;
            }

            if(k%3 == 1){
                gameMatrix[0][k] = 0;
                gameMatrix[1][k] = 1;
                gameMatrix[2][k] = 1;
            }

            if(k%3 == 2){
                gameMatrix[0][k] = 1;
                gameMatrix[1][k] = 1;
                gameMatrix[2][k] = 0;
            }
        }
    }

    grama = criaGrama();
    pista = criaPista();
    carro = carro_criaCarro();
    gameMatrix[1][0] = 1; // O carro inicia no meio
    muro = muro_criaMuro();


    for(i=0;i<3;i++){
        for(k=1;k<a_value;k++){
            if(gameMatrix[i][k] == 1){
                Carro _novoCarro = carro_criaCarro();
                _novoCarro.posicao.x = (i-1)*(pista.dimensoes.width);
                _novoCarro.posicao.z = k*pista.dimensoes.depth;
                listaCarros = listacarro_adicionaCarro(listaCarros, _novoCarro);
            }
        }
    }
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
