#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <math.h>
#include <stdio.h>
#include "../props/props.h"
#include "carro.h"

Carro carro_criaCarro(){
    Carro _novoCarro;

    _novoCarro.dimensoes.width = 10;
    _novoCarro.dimensoes.height = 4;
    _novoCarro.dimensoes.depth = 4.5;
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

     _novoCarro.textura[1] = SOIL_load_OGL_texture(
         "textures/carro/tras.png",
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
       SOIL_FLAG_INVERT_Y
    );

    _novoCarro.textura[2] = SOIL_load_OGL_texture(
        "textures/carro/vidro_tras.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
   );

   _novoCarro.textura[3] = SOIL_load_OGL_texture(
       "textures/carro/common.png",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
  );

    return _novoCarro;
}

void carro_desenhaRoda(){
    printf("Hello");
}

void carro_desenhaCarro(Carro *carro, int corR, int corG, int corB){
    glPushMatrix();

    glTranslated(carro->posicao.x-(4.5/2),carro->posicao.y+0.5,carro->posicao.z);
    glRotated(90+carro->inclinacao,0,1,0);
    //desenha lado
    glColor3f(corR,corG,corB);

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

    glBindTexture(GL_TEXTURE_2D, carro->textura[1]);

    //desenha tras
    glColor3f(corR,corG,corB);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(1, 0); glVertex3f(10,0,0);
        glTexCoord2f(1, 1); glVertex3f(10,3,0);
        glTexCoord2f(0, 1); glVertex3f(10,3,4.5);
        glTexCoord2f(0, 0); glVertex3f(10,0,4.5);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, carro->textura[2]);

    //desenha vidro de tras
    glColor3f(1,1,1);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(1, 0); glVertex3f(10,3,0);
        glTexCoord2f(1, 1); glVertex3f(8,4,0);
        glTexCoord2f(0, 1); glVertex3f(8,4,4.5);
        glTexCoord2f(0, 0); glVertex3f(10,3,4.5);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, carro->textura[3]);

    //desenha teto
    glColor3f(corR,corG,corB);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(1, 0); glVertex3f(5,4,4.5);
        glTexCoord2f(1, 1); glVertex3f(8,4,4.5);
        glTexCoord2f(0, 1); glVertex3f(8,4,0);
        glTexCoord2f(0, 0); glVertex3f(5,4,0);
    glEnd();

    //desenha capo
    glColor3f(corR,corG,corB);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(1, 0); glVertex3f(0,2,4.5);
        glTexCoord2f(1, 1); glVertex3f(2.5,2,4.5);
        glTexCoord2f(0, 1); glVertex3f(2.5,2,0);
        glTexCoord2f(0, 0); glVertex3f(0,2,0);
    glEnd();

    glDisable(GL_BLEND);

    glPopMatrix();
}


ListaCarro *listacarro_adicionaCarro(ListaCarro *lista, Carro carro){
    ListaCarro *_novaLista = (ListaCarro *) malloc(sizeof(ListaCarro));
    _novaLista->carro = carro;
    _novaLista->proximo = lista;
    return _novaLista;
}

ListaCarro *listacarro_deletaCarro(ListaCarro *lista, Carro *carro){
    // Percorre a lista até achar o elemento
    ListaCarro *_elementoAnterior = NULL;
    ListaCarro *_primeiroElemento = lista; // Salva o primeiro elemento
    while(lista != NULL){
        if(&lista->carro == carro){
            if(_elementoAnterior == NULL) return lista->proximo; // Caso o anterior seja NULL apenas retorna
            _elementoAnterior->proximo = lista->proximo; // Pula o elemento atual e retorna a posição inicial da lista
            return _primeiroElemento;
        }
        _elementoAnterior = lista;
        lista = lista->proximo;
    }
    return _primeiroElemento; // Caso não tenha encontrado nada só retorna o primeiro elemento
}

int checaColisao(Carro c1, Carro c2){
    Vetor distancia;
    distancia.x = c1.posicao.x - c2.posicao.x;
    distancia.y = c1.posicao.y - c2.posicao.y;
    distancia.z = c1.posicao.z - c2.posicao.z;
    if(distancia.x < 0) distancia.x=distancia.x*-1;
    if(distancia.z < 0) distancia.z=distancia.z*-1;
    int checaX = distancia.x < c1.dimensoes.depth/2;
    int checaZ = distancia.z < c1.dimensoes.width/2;
    printf("%.2f %.2f %.2f - %.2f\n",distancia.x,distancia.y,distancia.z,vetor_calculaModulo(distancia));
    return checaX && checaZ;
}
