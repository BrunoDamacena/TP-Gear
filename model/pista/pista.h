typedef struct pista{
    Dimensoes dimensoes;
    int textura;
} Pista;

Pista criaPista();
void desenhaPistaUnitaria(Pista *pista, int last);
void desenhaPista(Pista *pista);
