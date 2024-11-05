
#ifndef MERCADO_H
#define MERCADO_H

#include <stdio.h>


typedef struct {
    int codigo;          
    char nome[50];      
    int quantidade;     
    float preco;         
} Fruta;


void CadastrarFruta(Fruta **frutas, int *contador);
void ListarFruta(Fruta *frutas, int contador);
void BuscarFruta(Fruta *frutas, int contador);
void AlterarFruta(Fruta *frutas, int contador);
void ExcluirFruta(Fruta **frutas, int *contador);
void SalvarVendas(Fruta *frutas, int codigoFruta, int quantidadeVendida);
void VenderFruta(Fruta *frutas, int *contador);



void SalvarVendas(Fruta *frutas, int codigoFruta, int quantidadeVendida) {
    FILE *file = fopen("vendas.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de vendas.\n");
        return;
    }

    fprintf(file, "Código: %d, Quantidade Vendida: %d\n", codigoFruta, quantidadeVendida);
    fclose(file);
}

void VenderFruta(Fruta *frutas, int *contador) {
    if (*contador == 0) {
        printf("Nenhuma fruta cadastrada.\n");
        return;
    }

    int codigo;
    int quantidadeVendida;
    printf("Digite o código da fruta que deseja vender: ");
    scanf("%d", &codigo);

    for (int i = 0; i < *contador; i++) {
        if (frutas[i].codigo == codigo) {
            printf("Quantidade disponível: %d\n", frutas[i].quantidade);
            printf("Digite a quantidade que deseja vender: ");
            scanf("%d", &quantidadeVendida);

            if (quantidadeVendida > frutas[i].quantidade) {
                printf("Quantidade solicitada maior que a disponível em estoque.\n");
                return;
            }

            frutas[i].quantidade -= quantidadeVendida; 
            SalvarVendas(frutas, codigo, quantidadeVendida); 
            printf("Venda realizada com sucesso!\n");
            return;
        }
    }

    printf("Fruta com código %d não encontrada.\n", codigo);
}



void ExcluirFruta(Fruta **frutas, int *contador) {
    if (*contador == 0) {
        printf("Nenhuma fruta cadastrada.\n");
        return;
    }

    int codigo;
    printf("Digite o código da fruta que deseja excluir: ");
    scanf("%d", &codigo);

    for (int i = 0; i < *contador; i++) {
        if ((*frutas)[i].codigo == codigo) {
            if ((*frutas)[i].quantidade > 0) {
                printf("Não é possível excluir a fruta. Estoque maior que zero.\n");
                return;
            }

            for (int j = i; j < *contador - 1; j++) {
                (*frutas)[j] = (*frutas)[j + 1]; 
            }

            Fruta *temp = (Fruta *)realloc(*frutas, (*contador - 1) * sizeof(Fruta));
            if (temp == NULL && (*contador - 1) > 0) {
                printf("Erro ao realocar memória.\n");
                return;
            }
            *frutas = temp;

            (*contador)--;
            printf("Fruta excluída com sucesso!\n");
            return;
        }
    }

    printf("Fruta com código %d não encontrada.\n", codigo);
}



void AlterarFruta(Fruta *frutas, int contador) {
    if (contador == 0) {
        printf("Nenhuma fruta cadastrada.\n");
        return;
    }

    int codigo;
    printf("Digite o código da fruta que deseja alterar: ");
    scanf("%d", &codigo);

    for (int i = 0; i < contador; i++) {
        if (frutas[i].codigo == codigo) {
            printf("Fruta encontrada:\n");
            printf("Código: %d\n", frutas[i].codigo);
            printf("Nome atual: %s\n", frutas[i].nome);
            printf("Quantidade atual: %d\n", frutas[i].quantidade);
            printf("Preço atual: %.2f\n", frutas[i].preco);
            printf("--------------------------------\n");
            printf("Digite o novo nome da fruta: ");
            scanf(" %[^\n]", frutas[i].nome);
            printf("Digite a nova quantidade em estoque: ");
            scanf("%d", &frutas[i].quantidade);
            printf("Digite o novo preço da fruta: ");
            scanf("%f", &frutas[i].preco);

            printf("Fruta alterada com sucesso!\n");
            return;
        }
    }

    printf("Fruta com código %d não encontrada.\n", codigo);
}



void BuscarFruta(Fruta *frutas, int contador){
    if (contador == 0){
        printf("Nenhuma fruta cadastrada.\n");
        return;
    }
    
    int codigo;
    printf("Digite o código da fruta que deseja buscar:");
    scanf("%d", &codigo);
    
    for(int i = 0; i<contador; i++){
        if (frutas[i].codigo == codigo){
            printf("fruta encontrada:\n");
            printf("código: %d\n", frutas[i].codigo);
            printf("nome: %s\n", frutas[i].nome);
            printf("quantidade: %d\n",frutas[i].quantidade);
            printf("preço: %.2f\n", frutas[i].preco);
            return;
        }
    }
    
    printf("Fruta com código %d não encontrada.\n", codigo);
}



void ListarFruta(Fruta *frutas, int contador){
    if (contador == 0){
        printf("Nenhuma Fruta cadastrada.\n");
        return;
    }
    
    printf("Frutas cadastradas:\n");
    for (int i = 0; i< contador; i++){
        printf("código: %d\n", frutas[i].codigo);
        printf("nome: %s\n", frutas[i].nome);
        printf("quantidade: %d\n", frutas[i].quantidade);
        printf("preço: %.2f\n", frutas[i].preco);
        printf("--------------------------------\n");
    }
}



void CadastrarFruta(Fruta **frutas, int *contador) {
    Fruta novaFruta;

    printf("Digite o código da fruta: ");
    scanf("%d", &novaFruta.codigo);
    getchar(); 

    for (int i = 0; i < *contador; i++) {
        if ((*frutas)[i].codigo == novaFruta.codigo) {
            printf("Código já cadastrado. Tente novamente.\n");
            return;
        }
    }

    printf("Digite o nome da fruta: ");
    scanf(" %[^\n]", novaFruta.nome);

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &novaFruta.quantidade);

    printf("Digite o preço da fruta: ");
    scanf("%f", &novaFruta.preco);

    Fruta *temp = (Fruta *)realloc(*frutas, (*contador + 1) * sizeof(Fruta));    
    if (temp == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    *frutas = temp;


    (*frutas)[*contador] = novaFruta;
    (*contador)++; 

    printf("Fruta cadastrada com sucesso!\n");
}


#endif 
