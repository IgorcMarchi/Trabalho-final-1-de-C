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
                mat = cria_matriz(3,4);
                if (mat == NULL) {
                    printf("Erro ao criar a matriz.\n");
                    return 1;
                }
                printf("Matriz criada com sucesso!\n");
                break;

            case 2: {
                printf("Fale a posicao (linha e coluna) do elemento: ");
                scanf("%d %d", &linha, &coluna);
                printf ("\nAgora digite o valor do elemento: ");
                scanf("%d", &valor);
                inserir_elemento(mat, linha, coluna, valor);
                printf("Elemento inserido com sucesso!\n");
                break;
            }
            case 3:
                printf("Opcao 3 selecionada.\n");
                break;

            case 4:
                printf("Opcao 4 selecionada.\n");
                break;

            case 5:
                printf("Fale a posicao (linha e coluna) do elemento: ");
                scanf("%d %d", &linha, &coluna);
                printf ("%d", consultar_posicao(mat, linha, coluna));
                break;

            case 6:
                printf("Opcao 6 selecionada.\n");
                break;

            case 7:
                printf("Fale a posicao (linha e coluna) do elemento: ");
                scanf("%d %d", &linha, &coluna);
                imprimir_vizinhos(mat, linha, coluna);
    
                break;

            case 8:
                liberar_matriz(mat);
                mat = NULL; // Define mat como NULL após liberar
                break;

            case 9:
                printf("Saindo.....\n");
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }
   }while(opcao != 9);
    return 0;
}