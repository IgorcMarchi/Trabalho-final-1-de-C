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
    printf ("                     MENU: \n");
    printf("--------------------------------------------------\n");
    printf ("1- Criar Matriz\n"); //Fizemo
    printf ("2- Inserir Elemento\n"); //Fizemos
    printf ("3- Consultar posicao: \n"); //Fizemos
    printf ("4- Buscar um valor qual quer:\n"); //fizemos
    printf ("5- Imprimir Valor dos 4 vizinhos de (x, y):\n"); // Fizemos
    printf ("6- Liberar matriz: \n"); //Fizemos
    printf ("7- Imprimir Matriz: \n"); // FEITO
    printf ("8- Remover dado de uma posicao especifica: \n"); //FEITO
    printf ("9- Limpar dados da matriz: \n"); //FEITO
    printf ("10- Sair..\n");
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
    if (mat == NULL) 
        return 0;
    if (linha < 0 || linha >= mat->linha || coluna < 0 || coluna >= mat->coluna)
        return 0;

    int idx = linha * mat->coluna + coluna;
    mat->elementos[idx]->valor = valor;
    return 1; // Sucesso
}

void consultar_posicao(Mat *mat, int linha, int coluna){
    if (mat == NULL || mat->elementos == NULL) 
        return;
    if (linha < 0 || linha >= mat->linha || coluna < 0 || coluna >= mat->coluna){
        printf("Posicao (%d, %d) fora dos limites da matriz.\n", linha, coluna);
        return;
    }
    int idx= linha * mat->coluna + coluna;
    if(mat->elementos[idx] == 0) 
        return ; // Verifica se o elemento existe
    if(mat->elementos[idx]->valor == 0) {
        printf("Valor nao inserido na posicao (%d, %d)\n", linha, coluna);
    }
    else
        printf("Valor na posicao (%d, %d): %d\n", linha, coluna, mat->elementos[idx]->valor);
}

void imprimir_vizinhos(Mat *mat, int linha, int coluna){
    if (mat == NULL || mat->elementos == NULL) 
        return;
    if (linha < 0 || linha >= mat->linha || coluna < 0 || coluna >= mat->coluna){
        printf("Posicao (%d, %d) fora dos limites da matriz.\n", linha, coluna);
        return;
    }

    int idx = linha * mat->coluna + coluna;
    Elemento *elem = mat->elementos[idx];
    
    if (elem->prox != NULL)
        if(elem->prox->valor == 0)
            printf("Direita: varlor nao inserido\n");
        else
            printf("Direita: %d\n", elem->prox->valor);
    else
        printf("Direita: NULO\n");

    if (elem->ant != NULL)
        if(elem->ant->valor == 0)
            printf("Esquerda: valor nao inserido\n");
        else
            printf("Esquerda: %d\n", elem->ant->valor);
    else
        printf("Esquerda: NULO\n");

    if (elem->cima != NULL)
        if(elem->cima->valor == 0)
            printf("Cima: varlor nao inserido\n");
        else
            printf("Cima: %d\n", elem->cima->valor);
    else
        printf("Cima: NULO\n");

    if (elem->baixo != NULL)
        if(elem->baixo->valor == 0)
            printf("Baixo: varlor nao inserido\n");
        else
            printf("Baixo: %d\n", elem->baixo->valor);
    else
        printf("Baixo: NULO\n");
}

void buscar_valor(Mat *mat, int valor) {
    if (mat == NULL || mat->elementos == NULL) 
        return;
    int contador = 0;
    for (int i = 0; i < mat->linha * mat->coluna; i++) {
        if (mat->elementos[i]->valor == valor) {
            printf("Valor %d encontrado na posicao (%d, %d)\n", valor, i / mat->coluna, i % mat->coluna);
            contador++;
        }
    }
    if(contador == 0)
        printf("Valor %d nao encontrado na matriz.\n", valor);
}

void imprimir_matriz(Mat *mat) {
    if (mat == NULL || mat->elementos == NULL) {
        printf("Matriz nao existe ou nao foi criada.\n");
        return;
    }

    printf("Matriz %dx%d:\n", mat->linha, mat->coluna);
    for (int l = 0; l < mat->linha; l++) {
        for (int c = 0; c < mat->coluna; c++) {
            int idx = l * mat->coluna + c;
            if(mat->elementos[idx]->valor == 0)
                printf(" X ");
            else
            printf(" %d ", mat->elementos[idx]->valor);
        }
        printf("\n");
    }
}

void remover_dado_posicao_especifica(Mat *mat, int linha, int coluna){
    if (mat == NULL || mat->elementos == NULL) return;
    if (linha < 0 || linha >= mat->linha || coluna < 0 || coluna >= mat->coluna){
        printf("Posicao (%d, %d) fora dos limites da matriz.\n", linha, coluna);
        return;
    }
    int idx= linha * mat->coluna + coluna;
    if(mat->elementos[idx] == 0) 
        return ; // Verifica se o elemento existe
    if(mat->elementos[idx]->valor == 0) {
        printf("A posicao (%d, %d), ja nao existe valor inserido!\n", linha, coluna);
    }
    else{
        mat->elementos[idx]->valor = 0; // Zera o valor do elemento
        printf("Valor na posicao (%d, %d), foi apagado!\n", linha, coluna);
    }
}

int limpar_dados_matriz(Mat *mat) {
    if (mat == NULL || mat->elementos == NULL) {
        return 0;
    }

    for (int l = 0; l < mat->linha; l++) {
        for (int c = 0; c < mat->coluna; c++) {
            int idx = l * mat->coluna + c;
            if(mat->elementos[idx]->valor != 0)
                mat->elementos[idx]->valor = 0; // Zera o valor do elemento
        }
    }
    return 1; // Sucesso
}