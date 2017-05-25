#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <math.h>
#include "../props/props.h"
#include "pista.h"

Pista criaPista(){
    Pista _novaPista;

    _novaPista.dimensoes.width = 9;
    _novaPista.dimensoes.height = 0;
    _novaPista.dimensoes.depth = 5;

    _novaPista.textura = SOIL_load_OGL_texture(
        "textures/asphalt.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);

    return _novaPista;
}

void desenhaPistaUnitaria(Pista *pista, int last){
    glColor3f(1,1,1);
    // Desenha a pista com a textura
    glEnable(GL_TEXTURE_2D);

    // WRAP para resolver linhas pretas entre as texturas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, pista->textura);
    if(!last){
        glBegin(GL_TRIANGLE_FAN);
                glTexCoord2f(0.5, 0.5); glVertex3f(-(pista->dimensoes.width/2),  0, (pista->dimensoes.depth/2));
                glTexCoord2f(1, 0.5); glVertex3f((pista->dimensoes.width/2), 0, (pista->dimensoes.depth/2));
                glTexCoord2f(1, 1); glVertex3f((pista->dimensoes.width/2),  0, -(pista->dimensoes.depth/2));
                glTexCoord2f(0.5, 1); glVertex3f(-(pista->dimensoes.width/2),  0, -(pista->dimensoes.depth/2));
        glEnd();
    } else {
        glBegin(GL_TRIANGLE_FAN);
                glTexCoord2f(1, 0.5); glVertex3f(-(pista->dimensoes.width/2),  0, (pista->dimensoes.depth/2));
                glTexCoord2f(0.6, 0.5); glVertex3f((pista->dimensoes.width/2), 0, (pista->dimensoes.depth/2));
                glTexCoord2f(0.6, 1); glVertex3f((pista->dimensoes.width/2),  0, -(pista->dimensoes.depth/2));
                glTexCoord2f(1, 1); glVertex3f(-(pista->dimensoes.width/2),  0, -(pista->dimensoes.depth/2));
        glEnd();
    }

    glDisable(GL_TEXTURE_2D);
}

void desenhaPista(Pista *pista){
    int i,k;
    for(i=-1; i<2; i++){
        for(k=-5; k<100; k++){
            glPushMatrix();
                glTranslated(i*(pista->dimensoes.width),0,k*(pista->dimensoes.depth));
                desenhaPistaUnitaria(pista, (i == -1));
            glPopMatrix();
        }
    }
}
