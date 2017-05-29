typedef struct roda{
    double raio;
    double espessura;
    int textura;
} Roda;

typedef struct carro{
    Vetor posicao;
    Dimensoes dimensoes;
    double velocidade;
    double inclinacao;
    int textura[3];
    Roda roda;
} Carro;

typedef struct listaCarro{
    Carro carro;
    struct listaCarro *proximo;
} ListaCarro;

Carro carro_criaCarro();
void carro_desenhaCarro();


ListaCarro *listacarro_adicionaCarro(ListaCarro *lista, Carro carro);
ListaCarro *listacarro_deletaCarro(ListaCarro *lista, Carro *carro);

int checaColisao(Carro c1, Carro c2);
