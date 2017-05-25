typedef struct roda{
    double raio;
} Roda;

typedef struct carro{
    Vetor posicao;
    Dimensoes dimensoes;
    double velocidade;
    double inclinacao;
    int textura[8];
    Roda roda;
} Carro;

Carro carro_criaCarro();
void carro_desenhaCarro();
