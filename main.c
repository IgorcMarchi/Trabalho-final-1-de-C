#include <stdio.h>
#include <stdlib.h>

#include "matriz.h"
#include "matriz.c"

int main() {
int opcao, linha, coluna, valor;
    Mat *mat = NULL;

   do{
        menu();
        printf("Digite a opcao: ");
        scanf("%d", &opcao);

        
        switch (opcao) {
            case 1:
                printf ("--------------------------------------------------\n");
                printf ("Quantas linhas e colunas deseja criar? \n");
                scanf("%d %d", &linha, &coluna);
                printf ("--------------------------------------------------\n");

                mat = cria_matriz(linha, coluna);

                if (mat == NULL) {
                    printf("Erro ao criar a matriz.\n");
                    return 1;
                }
                printf("Matriz criada com sucesso!\n");
                printf ("--------------------------------------------------\n");
                system("pause");
                system("cls");
                break;

            case 2: {
                if (mat == NULL) {
                    printf("Matriz ainda nao foi criada. Por favor, crie uma matriz primeiro.\n");
                    break;
                }

                printf("Fale a posicao (linha e coluna) do elemento: ");
                scanf("%d %d", &linha, &coluna);
                printf ("\nAgora digite o valor do elemento: ");
                scanf("%d", &valor);
                if(inserir_elemento(mat, linha, coluna, valor)) {
                    printf("Valor %d inserido na posicao (%d, %d).\n", valor, linha, coluna);
                } else {
                    printf("Erro ao inserir o valor na posicao (%d, %d).\n", linha, coluna);
                }
                printf ("--------------------------------------------------\n");
                system("pause");
                system("cls");
                break;
            }
            case 3:
                if (mat == NULL) {
                    printf("Matriz ainda nao foi criada. Por favor, crie uma matriz primeiro.\n");
                    break;
                }
                printf("Fale a posicao (linha e coluna) do elemento: ");
                scanf("%d %d", &linha, &coluna);
                consultar_posicao(mat, linha, coluna);
                printf("--------------------------------------------------\n");
                system("pause");
                system("cls");
                break;

            case 4:
                if (mat == NULL) {
                    printf("Matriz ainda nao foi criada. Por favor, crie uma matriz primeiro.\n");
                    break;
                }

                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor);
                printf("Buscando o valor %d...\n", valor);
                buscar_valor(mat, valor);
                printf ("--------------------------------------------------\n");
                system("pause");
                system("cls");
                break;

            case 5:
                if (mat == NULL) {
                    printf("Matriz ainda nao foi criada. Por favor, crie uma matriz primeiro.\n");
                    break;
                }

                printf("Fale a posicao (linha e coluna) do elemento: ");
                scanf("%d %d", &linha, &coluna);
                printf ("-------------------------------------------------\n");
                imprimir_vizinhos(mat, linha, coluna);
                printf ("-------------------------------------------------\n");
                system("pause");
                system("cls");
                break;

            case 6:
                if (mat == NULL) {
                    printf("Matriz ainda nao foi criada. Por favor, crie uma matriz primeiro.\n");
                    break;
                }
                printf("Liberando a matriz...\n");
                liberar_matriz(mat);
                mat = NULL; // Define mat como NULL após liberar
                system("pause");
                system("cls");
                break;
            case 7:
                if (mat == NULL) {
                    printf("Matriz ainda nao foi criada. Por favor, crie uma matriz primeiro.\n");
                    break;
                }
                printf ("-------------------------------------------------\n");
                imprimir_matriz(mat);
                printf ("-------------------------------------------------\n");
                system("pause");
                system("cls");
                break;
            
            case 8:
                if (mat == NULL) {
                    printf("Matriz ainda nao foi criada. Por favor, crie uma matriz primeiro.\n");
                    break;
                }
                printf("Fale a posicao (linha e coluna) do elemento: ");
                scanf("%d %d", &linha, &coluna);
                printf ("-------------------------------------------------\n");
                remover_dado_posicao_especifica(mat, linha, coluna);
                printf ("-------------------------------------------------\n");
                system("pause");
                system("cls");
                break;
            case 9:
                if (mat == NULL) {
                    printf("Matriz ainda nao foi criada. Por favor, crie uma matriz primeiro.\n");
                    break;
                }
                printf("Limpando todos os dados da matriz...\n");
                if (limpar_dados_matriz(mat)) {
                    printf("Todos os dados foram limpos com sucesso!\n");
                } else {
                    printf("Erro ao limpar os dados da matriz.\n");
                }
                system("pause");
                system("cls");
                break;
            case 10:
                printf("Saindo.....\n");
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }
   }while(opcao != 10);
    return 0;
}