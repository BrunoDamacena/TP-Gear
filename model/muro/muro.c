#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <math.h>
#include "../props/props.h"
#include "muro.h"

Muro muro_criaMuro(){
    Muro _novoMuro;
    _novoMuro.dimensoes.width = 3;
    _novoMuro.dimensoes.height = 2.5;
    _novoMuro.dimensoes.depth = 5;

    _novoMuro.textura = SOIL_load_OGL_texture(
        "textures/brick.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);

    return _novoMuro;
}

void muro_desenhaMuroUnitario(Muro *muro){
    glColor3f(1,1,1);
    // Desenha a pista com a textura
    glEnable(GL_TEXTURE_2D);

    // WRAP para resolver linhas pretas entre as texturas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, muro->textura);

    //desenha lado do muro
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(1, 0); glVertex3f(-(muro->dimensoes.width)/2,-(muro->dimensoes.height/2),(muro->dimensoes.depth/2));
        glTexCoord2f(1, 1); glVertex3f(-(muro->dimensoes.width)/2,(muro->dimensoes.height/2),(muro->dimensoes.depth/2));
        glTexCoord2f(0, 1); glVertex3f(-(muro->dimensoes.width)/2,(muro->dimensoes.height/2),-(muro->dimensoes.depth/2));
        glTexCoord2f(0, 0); glVertex3f(-(muro->dimensoes.width)/2,-(muro->dimensoes.height/2),-(muro->dimensoes.depth/2));
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f((muro->dimensoes.width)/2,-(muro->dimensoes.height/2),-(muro->dimensoes.depth/2));
        glTexCoord2f(0, 1); glVertex3f((muro->dimensoes.width)/2,(muro->dimensoes.height/2),-(muro->dimensoes.depth/2));
        glTexCoord2f(1, 1); glVertex3f((muro->dimensoes.width)/2,(muro->dimensoes.height/2),(muro->dimensoes.depth/2));
        glTexCoord2f(1, 0); glVertex3f((muro->dimensoes.width)/2,-(muro->dimensoes.height/2),(muro->dimensoes.depth/2));

    glEnd();

    //desenha topo do muro
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(1, 0); glVertex3f(-(muro->dimensoes.width/2),  (muro->dimensoes.height/2), (muro->dimensoes.depth/2));
        glTexCoord2f(1, 1); glVertex3f((muro->dimensoes.width/2),  (muro->dimensoes.height/2), (muro->dimensoes.depth/2));
        glTexCoord2f(0, 1); glVertex3f((muro->dimensoes.width/2),  (muro->dimensoes.height/2), -(muro->dimensoes.depth/2));
        glTexCoord2f(0, 0); glVertex3f(-(muro->dimensoes.width/2),  (muro->dimensoes.height/2), -(muro->dimensoes.depth/2));
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void muro_desenhaMuro(Muro *muro){
    int k;
    for(k=-5; k<100; k++){
        glPushMatrix();
            glTranslated(0,(muro->dimensoes.height)/2,k*(muro->dimensoes.depth));
            muro_desenhaMuroUnitario(muro);
        glPopMatrix();
    }
}