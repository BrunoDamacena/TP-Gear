#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <math.h>
#include "../props/props.h"
#include "pista.h"

void desenhaPista(Vetor o, Vetor t){
    glPushMatrix();
    glTranslated(o.x, o.y, o.z);
    glBegin(GL_TRIANGLE_FAN);
            glVertex3f(o.x-t.x/2,  0, o.z);
            glVertex3f(o.x-t.x/2, 0, o.z+t.z);
            glVertex3f(o.x+t.x/2,  0, o.z+t.z);
            glVertex3f(o.x+t.x/2,  0, o.z);
        glEnd();
    glPopMatrix();
}
