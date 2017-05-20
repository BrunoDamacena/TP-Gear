#define CARRO_VELOCIDADE_MAXIMA 25

typedef struct carro{
    Dimensoes dimensoes;

    double inclinacao;
    int textura;
} Carro;

Carro carro_criaCarro();
void carro_desenhaCarro();
