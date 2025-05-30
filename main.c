#include <stdio.h>
#include <stdlib.h>

#include "matriz.h"
#include "matriz.c"

int main() {
int opcao;
    Mat *mat = NULL;

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

        case 2:
            printf("Opcao 2 selecionada.\n");
            break;

        case 3:
            printf("Opcao 3 selecionada.\n");
            break;

        // Adicione os outros casos conforme necessário

        case 9:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida.\n");
            break;
    }

    return 0;
}