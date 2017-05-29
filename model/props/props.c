#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <math.h>
#include "props.h"

double vetor_calculaModulo(Vetor v){
    double _moduloVetor = sqrt(pow(v.x,2)+pow(v.y,2)+pow(v.z,2));
    return _moduloVetor;
}
