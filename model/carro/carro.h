typedef struct roda{
    double raio;
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