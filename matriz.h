#ifndef MATRIZ_H
#define MATRIZ_H
typedef struct matriz Mat;

void menu();
Mat *cria_matriz(int linhas, int colunas) ;
void liberar_matriz(Mat *mat);
int inserir_elemento(Mat *mat, int linha, int coluna, int valor);



#endif
