#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <math.h>
#include "../props/props.h"
#include "carro.h"

Carro carro_criaCarro(){
    Carro _novoCarro;

    _novoCarro.dimensoes.width = 64;
    _novoCarro.dimensoes.height = 64;
    _novoCarro.posicao.x = 0;
    _novoCarro.posicao.y = 0;
    _novoCarro.posicao.z = 0;
    _novoCarro.velocidade = 0;
    _novoCarro.inclinacao = 0;

    _novaBalista.textura = SOIL_load_OGL_texture(
        "textures/....png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);

    return _novoCarro;
}

void carro_desenhaCarro(Carro *carro){
    
}
