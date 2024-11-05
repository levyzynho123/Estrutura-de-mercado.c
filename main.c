#include <stdlib.h>
#include <stdio.h>
#include "mercado.h"

int main() {
    Fruta *frutas = NULL;  
    int contador = 0;       
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar Fruta\n");
        printf("2. Listar Frutas\n");
        printf("3. Buscar Fruta\n");
        printf("4. Alterar Fruta\n");
        printf("5. Excluir Fruta\n");
        printf("6. Vender Fruta\n");
        printf("7. Sair\n");
        printf("---------------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                CadastrarFruta(&frutas, &contador);
                break;
            case 2:
                ListarFruta(frutas, contador);
                break;
            case 3:
                BuscarFruta(frutas, contador);
                break;
            case 4:
                AlterarFruta(frutas, contador);
                break;
            case 5:
                ExcluirFruta(&frutas, &contador);
                break;
            case 6:
                VenderFruta(frutas, &contador);
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 7);

    free(frutas);

    return 0;
}

