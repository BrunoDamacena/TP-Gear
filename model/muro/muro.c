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

    return _novoMuro;
}

void muro_desenhaMuroUnitario(Muro *muro){

    glColor3f(1,1,1);

    //desenha lado do muro
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(-(muro->dimensoes.width)/2,-(muro->dimensoes.height/2),(muro->dimensoes.depth/2));
        glVertex3f(-(muro->dimensoes.width)/2,(muro->dimensoes.height/2),(muro->dimensoes.depth/2));
        glVertex3f(-(muro->dimensoes.width)/2,(muro->dimensoes.height/2),-(muro->dimensoes.depth/2));
        glVertex3f(-(muro->dimensoes.width)/2,-(muro->dimensoes.height/2),-(muro->dimensoes.depth/2));
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glVertex3f((muro->dimensoes.width)/2,-(muro->dimensoes.height/2),-(muro->dimensoes.depth/2));
        glVertex3f((muro->dimensoes.width)/2,(muro->dimensoes.height/2),-(muro->dimensoes.depth/2));
        glVertex3f((muro->dimensoes.width)/2,(muro->dimensoes.height/2),(muro->dimensoes.depth/2));
        glVertex3f((muro->dimensoes.width)/2,-(muro->dimensoes.height/2),(muro->dimensoes.depth/2));

    glEnd();

    glColor3f(0,0,0);

    //desenha topo do muro
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(-(muro->dimensoes.width/2),  (muro->dimensoes.height/2), (muro->dimensoes.depth/2));
        glVertex3f((muro->dimensoes.width/2),  (muro->dimensoes.height/2), (muro->dimensoes.depth/2));
        glVertex3f((muro->dimensoes.width/2),  (muro->dimensoes.height/2), -(muro->dimensoes.depth/2));
        glVertex3f(-(muro->dimensoes.width/2),  (muro->dimensoes.height/2), -(muro->dimensoes.depth/2));
    glEnd();
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