typedef struct muro{
    Dimensoes dimensoes;
    int textura;
} Muro;

Muro muro_criaMuro();
void muro_desenhaMuroUnitario(Muro *muro);
void muro_desenhaMuro(Muro *muro);
