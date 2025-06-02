#ifndef MATRIZ_H
#define MATRIZ_H
typedef struct matriz Mat;

void menu();
Mat *cria_matriz(int linhas, int colunas) ;
void liberar_matriz(Mat *mat);
int inserir_elemento(Mat *mat, int linha, int coluna, int valor);
void consultar_posicao(Mat *mat, int linha, int coluna);
void imprimir_vizinhos(Mat *mat, int linha, int coluna);
void buscar_valor(Mat *mat, int valor);
void imprimir_matriz(Mat *mat);



#endif
