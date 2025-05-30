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
    printf("\n--------------------------------------------------\n");
    printf ("Menu : \n");
    printf ("1- Criar Matriz\n"); //Fizemo
    printf ("2- Inserir Elemento\n"); //Fizemos
    printf ("3- Remover Elemento\n");
    printf ("4- Inserir dados em um valor especifico\n");
    printf ("5- Consultar posicao: \n");
    printf ("6- Buscar um valor qual quer:\n ");
    printf ("7- Imprimir Valor dos 4 vizinhos de (x, y):\n ");
    printf ("8- Liberar matriz: \n"); //Fizemos
    printf ("9- Sair..\n");
    printf("--------------------------------------------------\n");
}

//Função para criar matriz

Mat *cria_matriz(int linhas, int colunas) {
    Mat *mat = (Mat*)malloc(sizeof(Mat));
    if (mat == NULL) {
        return NULL; // Falha ao alocar memória para a estrutura da matriz
    }

    mat->linha = linhas;
    mat->coluna = colunas;
    mat->inicio = NULL;

    // Aloca o vetor de ponteiros para os elementos
    Elemento **no = (Elemento**)malloc(linhas * colunas * sizeof(Elemento*));
    if (no == NULL) {
        free(mat);
        return NULL;
    }

    // Etapa 1: Alocar todos os elementos
    for (int l = 0; l < linhas; l++) {
        for (int c = 0; c < colunas; c++) {
            int idx = l * colunas + c;
            no[idx] = (Elemento*)malloc(sizeof(Elemento));
            if (no[idx] == NULL) {
                // Libera tudo o que foi alocado até agora
                for (int i = 0; i < idx; i++) {
                    free(no[i]);
                }
                free(no);
                free(mat);
                return NULL;
            }
            // Inicializa o elemento
            no[idx]->valor = 0;
            no[idx]->prox = NULL;
            no[idx]->ant = NULL;
            no[idx]->cima = NULL;
            no[idx]->baixo = NULL;
        }
    }

    // Etapa 2: Fazer ligações entre os elementos
    for (int l = 0; l < linhas; l++) {
        for (int c = 0; c < colunas; c++) {
            int idx = l * colunas + c;
            Elemento *elem = no[idx];

            if (c > 0)
                elem->ant = no[l * colunas + (c - 1)];
            if (c < colunas - 1)
                elem->prox = no[l * colunas + (c + 1)];
            if (l > 0)
                elem->cima = no[(l - 1) * colunas + c];
            if (l < linhas - 1)
                elem->baixo = no[(l + 1) * colunas + c];
        }
    }

    mat->inicio = no[0];
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

int consultar_posicao(Mat *mat, int linha, int coluna){
    if (mat == NULL || mat->elementos == NULL) return 0;
    if (linha < 0 || linha >= mat->linha || coluna < 0 || coluna >= mat->coluna) return 0;

    int idx= linha * mat->coluna + coluna;
    return mat->elementos[idx]->valor;
}

void imprimir_vizinhos(Mat *mat, int linha, int coluna){
    if (mat == NULL || mat->elementos == NULL) return;
    if (linha < 0 || linha >= mat->linha || coluna < 0 || coluna >= mat->coluna) return;

    int idx = linha * mat->coluna + coluna;
    Elemento *elem = mat->elementos[idx];
    
    if (elem->prox != NULL)
        printf("Direita: %d\n", elem->prox->valor);
    else
        printf("Direita: NULO\n");

    if (elem->ant != NULL)
        printf("Esquerda: %d\n", elem->ant->valor);
    else
        printf("Esquerda: NULO\n");

    if (elem->cima != NULL)
        printf("Cima: %d\n", elem->cima->valor);
    else
        printf("Cima: NULO\n");

    if (elem->baixo != NULL)
        printf("Baixo: %d\n", elem->baixo->valor);
    else
        printf("Baixo: NULO\n");
}