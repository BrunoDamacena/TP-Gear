typedef struct grama{
    Dimensoes dimensoes;
    int textura;
} Grama;

Grama criaGrama();
void desenhaGramaUnitaria(Grama *grama);
void desenhaGrama(Grama *grama);
