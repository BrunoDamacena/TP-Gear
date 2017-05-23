#define CARRO_VELOCIDADE_MAXIMA 25

typedef struct carro{
    Vetor posicao;
    Dimensoes dimensoes;
    double velocidade;
    double inclinacao;
    int textura;
} Carro;

Carro carro_criaCarro();
void carro_desenhaCarro();
