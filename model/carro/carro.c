#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <math.h>
#include <stdio.h>
#include "../props/props.h"
#include "carro.h"

Carro carro_criaCarro(){
    Carro _novoCarro;

    _novoCarro.dimensoes.width = 64;
    _novoCarro.dimensoes.height = 64;
    _novoCarro.dimensoes.depth = 64;
    _novoCarro.posicao.x = 0;
    _novoCarro.posicao.y = 0;
    _novoCarro.posicao.z = 0;
    _novoCarro.velocidade = 0;
    _novoCarro.inclinacao = 0;



     _novoCarro.textura[0] = SOIL_load_OGL_texture(
         "textures/carro/lateral.png",
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
	 	SOIL_FLAG_INVERT_Y
	 );

    return _novoCarro;
}

void carro_desenhaRoda(){
    printf("Hello");
}

void carro_desenhaCarro(Carro *carro){
    glPushMatrix();

    glTranslated(carro->posicao.x-(4.5/2),carro->posicao.y+0.5,carro->posicao.z);
    glRotated(90+carro->inclinacao,0,1,0);
    //desenha lado
    glColor3f(1,1,1); //branco

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // Desenha o tiro
    glBindTexture(GL_TEXTURE_2D, carro->textura[0]);

    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f(0,0,0);
        glTexCoord2f(0, .5); glVertex3f(0,2,0);
        glTexCoord2f(.3, .5); glVertex3f(3,2,0);
        glTexCoord2f(.5, 1); glVertex3f(5,4,0);
        glTexCoord2f(.8, 1); glVertex3f(8,4,0);
        glTexCoord2f(1, .75); glVertex3f(10,3,0);
        glTexCoord2f(1, 0); glVertex3f(10,0,0);
        glTexCoord2f(.9, 0); glVertex3f(9,0,0);
        glTexCoord2f(.9, .375); glVertex3f(9,1.5,0);
        glTexCoord2f(.7, .375); glVertex3f(7,1.5,0);
        glTexCoord2f(.7, 0); glVertex3f(7,0,0);
        glTexCoord2f(.25, 0); glVertex3f(2.5,0,0);
        glTexCoord2f(.25, .375); glVertex3f(2.5,1.5,0);
        glTexCoord2f(.05, .375); glVertex3f(.5,1.5,0);
        glTexCoord2f(.05, 0); glVertex3f(.5,0,0);
    glEnd();



    //desenha outro lado
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(.05, 0); glVertex3f(.5,0,4.5);
        glTexCoord2f(.05, .375); glVertex3f(.5,1.5,4.5);
        glTexCoord2f(.25, .375); glVertex3f(2.5,1.5,4.5);
        glTexCoord2f(.25, 0); glVertex3f(2.5,0,4.5);
        glTexCoord2f(.7, 0); glVertex3f(7,0,4.5);
        glTexCoord2f(.7, .375); glVertex3f(7,1.5,4.5);
        glTexCoord2f(.9, .375); glVertex3f(9,1.5,4.5);
        glTexCoord2f(.9, 0); glVertex3f(9,0,4.5);
        glTexCoord2f(1, 0); glVertex3f(10,0,4.5);
        glTexCoord2f(1, .75); glVertex3f(10,3,4.5);
        glTexCoord2f(.8, 1); glVertex3f(8,4,4.5);
        glTexCoord2f(.5, 1); glVertex3f(5,4,4.5);
        glTexCoord2f(.3, .5); glVertex3f(3,2,4.5);
        glTexCoord2f(0, .5); glVertex3f(0,2,4.5);
        glTexCoord2f(0, 0); glVertex3f(0,0,4.5);
    glEnd();

    glDisable(GL_BLEND);


    //desenha frente
    glColor3f(1,0,0); //vermelho
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0,0,4.5);
        glVertex3f(0,2,4.5);
        glVertex3f(0,2,0);
        glVertex3f(0,0,0);
    glEnd();

    //desenha capo
    glColor3f(0,0,1); //azul
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0,2,4.5);
        glVertex3f(2.5,2,4.5);
        glVertex3f(2.5,2,0);
        glVertex3f(0,2,0);
    glEnd();

    //desenha vidro da frente
    glColor3f(0.3,0.3,0.3); //cinza
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(2.5,2,4.5);
        glVertex3f(5,4,4.5);
        glVertex3f(5,4,0);
        glVertex3f(2.5,2,0);
    glEnd();

    //desenha tras
    glColor3f(0,1,0); //verde
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(10,0,0);
        glVertex3f(10,3,0);
        glVertex3f(10,3,4.5);
        glVertex3f(10,0,4.5);
    glEnd();

    //desenha vidro de tras
    glColor3f(0.3,0.3,0.3); //quase preto
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(10,3,0);
        glVertex3f(8,4,0);
        glVertex3f(8,4,4.5);
        glVertex3f(10,3,4.5);
    glEnd();

    //desenha teto
    glColor3f(0.498,1,0.831); //azul marinho
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(5,4,4.5);
        glVertex3f(8,4,4.5);
        glVertex3f(8,4,0);
        glVertex3f(5,4,0);
    glEnd();

    glPopMatrix();
}
