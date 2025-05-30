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
}Mat;

void menu() {
    printf("--------------------------------------------------\n");
    printf ("Menu : \n");
    printf ("Criar Matriz\n");
    printf ("Inserir Elemento\n");
    printf ("Remover Elemento\n");
    printf ("Inserir dados em um valor especifico\n");
    printf ("COnsultar valor especifico\n");
    printf ("Buscar um valor qual quer:\n ");
    printf ("Imprimir Valor dos 4 vizinhos de (x, y):\n ");
    printf ("Liberar matriz: \n");
    printf ("Sair..\n");
    printf("--------------------------------------------------\n");
}



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

    return mat;
}
void liberar_matriz(Mat *mat) {
    if (mat == NULL) 
        return 0;

    Elemento *no = mat->inicio;
    Elemento *atual = NULL;
    Elemento *aux = NULL;

    for(int l = 0; l < mat->linha; l++) {
        atual = no;
        for(int c = 0; c < mat->coluna; c++) {
            aux = no->prox;
            free(atual); // Libera o elemento atual
            atual = aux; // Avança para o próximo elemento
        }
        if(no != NULL)
            no = no->baixo; // Avança para a próxima linha
    }

    free(mat); // Libera a memória da estrutura Mat
    printf("Matriz liberada com sucesso!\n");
}