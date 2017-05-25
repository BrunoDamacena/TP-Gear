#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <math.h>
#include "../props/props.h"
#include "grama.h"

Grama criaGrama(){
    Grama _novaGrama;

    _novaGrama.dimensoes.width = 10;
    _novaGrama.dimensoes.height = 0;
    _novaGrama.dimensoes.depth = 10;

    _novaGrama.textura = SOIL_load_OGL_texture(
        "textures/grass.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);

    return _novaGrama;
}

void desenhaGramaUnitaria(Grama *grama){
    glColor3f(1,1,1);
    // Desenha a grama com a textura
    glEnable(GL_TEXTURE_2D);

    // WRAP para resolver linhas pretas entre as texturas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, grama->textura);
    glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0); glVertex3f(-(grama->dimensoes.width/2),  0, (grama->dimensoes.depth/2));
            glTexCoord2f(1, 0); glVertex3f((grama->dimensoes.width/2), 0, (grama->dimensoes.depth/2));
            glTexCoord2f(1, 1); glVertex3f((grama->dimensoes.width/2),  0, -(grama->dimensoes.depth/2));
            glTexCoord2f(0, 1); glVertex3f(-(grama->dimensoes.width/2),  0, -(grama->dimensoes.depth/2));
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void desenhaGrama(Grama *grama){
    int i,k;
    for(i=-10; i<11; i++){
        for(k=-5; k<20; k++){
            glPushMatrix();
                glTranslated(i*(grama->dimensoes.width),-.1,k*(grama->dimensoes.depth));
                desenhaGramaUnitaria(grama);
            glPopMatrix();
        }
    }
}
