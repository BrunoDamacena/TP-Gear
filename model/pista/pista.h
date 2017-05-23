typedef struct pista{
    Dimensoes dimensoes;
    int textura;
} Pista;

Pista criaPista();
void desenhaPistaUnitaria(Pista *pista);
void desenhaPista(Pista *pista);
