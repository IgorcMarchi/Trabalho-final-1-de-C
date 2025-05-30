#include "matriz.h"
#include <stdlib.h>
#include <stddef.h>

typedef struct Elemento{
    struct Elemento *prox;
    struct Elemento *ant;
    struct Elemento *cima;
    struct Elemento *baixo;
    int valor;
}Elemento;


typedef struct matriz{
    int linha;
    int coluna;
    Elemento* inicio;
    Elemento **elementos; // Vetor de ponteiros para os elementos
}Mat;

void menu() {
    printf("--------------------------------------------------\n");
    printf ("Menu : \n");
    printf ("Criar Matriz\n"); //Fizemo
    printf ("Inserir Elemento\n");
    printf ("Remover Elemento\n");
    printf ("Inserir dados em um valor especifico\n");
    printf ("COnsultar valor especifico\n");
    printf ("Buscar um valor qual quer:\n ");
    printf ("Imprimir Valor dos 4 vizinhos de (x, y):\n ");
    printf ("Liberar matriz: \n"); //Fizemos
    printf ("Sair..\n");
    printf("--------------------------------------------------\n");
}

//Função para criar matriz

Mat *cria_matriz(int linhas, int colunas) {
    Mat *mat = (Mat*)malloc(sizeof(Mat));
    if (mat == NULL) {
        return NULL; // Falha ao alocar memória
    }
    mat->linha = linhas;
    mat->coluna = colunas;
    mat->inicio = NULL;

    Elemento **no = (Elemento**)malloc(linhas * colunas * sizeof(Elemento*));
    if (no == NULL) {
        free(mat); // Libera a memória alocada para Mat
        return 0; // Falha ao alocar memória para os elementos
    }

    for(int l = 0; l < linhas; l++) {
        for(int c = 0; c < colunas; c++) {
           no[l * colunas + c] = (Elemento*)malloc(sizeof(Elemento));
           if(no[l * colunas + c] == NULL) {
                // Se falhar, libera a memória já alocada
                for(int i = 0; i < l * colunas + c; i++) {
                    free(no[i]);
                }
                free(no);
                free(mat);
                return NULL; // Falha ao alocar memória para um elemento
            }
            no[l * colunas + c]->valor = 0; // Inicializa o valor do elemento
            no[l * colunas + c]->prox = NULL;
            no[l * colunas + c]->ant = NULL;
            no[l * colunas + c]->cima = NULL;
            no[l * colunas + c]->baixo = NULL;

            if(c > 0)
                no[l * colunas + c]->ant = no[l * colunas + (c-1)];
            if(c < colunas - 1)
                no[l * colunas + c]->prox = no[l * colunas + (c+1)];
            if(l > 0)
                no[l * colunas + c]->cima = no[(l-1) * colunas + c];
            if(l < linhas - 1)
                no[l * colunas + c]->baixo = no[(l+1) * colunas + c];
        }
    }
    mat->inicio = no[0]; // Atribui o ponteiro de início da matriz
    // Na cria_matriz, salve o ponteiro:
    mat->elementos = no;

    return mat;
}

//Função para liberar memoria da matriz

void liberar_matriz(Mat *mat) {
    if (mat == NULL){
        printf("Matriz já liberada ou não existe!\n");
        return;
    }

    // Libere todos os elementos
    for (int i = 0; i < mat->linha * mat->coluna; i++) {
        free(mat->elementos[i]);
    }
    free(mat->elementos); // Libere o vetor de ponteiros

    free(mat); // Libere a struct Mat
    printf("Matriz liberada com sucesso!\n");
}


// Insere um valor na posição (linha, coluna) da matriz
int inserir_elemento(Mat *mat, int linha, int coluna, int valor) {
    if (mat == NULL) return 0;
    if (linha < 0 || linha >= mat->linha || coluna < 0 || coluna >= mat->coluna) return 0;

    int idx = linha * mat->coluna + coluna;
    mat->elementos[idx]->valor = valor;
    return 1; // Sucesso
}