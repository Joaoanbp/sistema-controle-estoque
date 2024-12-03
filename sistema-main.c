#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ------------------------------------ Definicao struct -----------------------------------------------

struct Produto {
    char nome[50];
    float preco;
    int codigo;
    int categorias;
    int quantidade;
    int nivelMinimo; // Nível mínimo de estoque
};

// ----------------------------- Função para ordenar os produtos pelo menor preço ---------------------------

void ordenarProdutosPorPreco(struct Produto produtos[], int tamanho) {
    struct Produto temp;
    // Bubble Sort para ordenar os produtos
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (produtos[j].preco > produtos[j + 1].preco) {
                // Troca os produtos de posição
                temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }

    // Exibe os produtos ordenados
    printf("\nProdutos ordenados pelo menor preço:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Nome: %s\n", produtos[i].nome);
        printf("Preço: R$ %.2f\n", produtos[i].preco);
        printf("Código: %d\n", produtos[i].codigo);
        printf("Quantidade: %d\n", produtos[i].quantidade);
        printf("Nível Mínimo: %d\n", produtos[i].nivelMinimo);
        printf("\n");
    }
}

// ----------------------------- Função para buscar produto pelo nome ---------------------------------------

int buscarProdutoPorNome(struct Produto produtos[], int tamanho, const char* nomeBusca) {
    for (int i = 0; i < tamanho; i++) {
        if (strncmp(produtos[i].nome, nomeBusca, strlen(produtos[i].nome)) == 0 &&
            nomeBusca[strlen(produtos[i].nome)] == '\n') {
            return i; // Retorna o índice do produto encontrado
        }
    }
    return -1; // Produto não encontrado
}

// ----------------------------- Função para verificar produtos com baixo estoque ---------------------------

void verificarEstoque(struct Produto produtos[], int tamanho) {
    int estoqueBaixo = 0;

    printf("\nProdutos com baixo estoque:\n");
    for (int i = 0; i < tamanho; i++) {
        if (produtos[i].quantidade < produtos[i].nivelMinimo) {
            printf("Nome: %s\n", produtos[i].nome);
            printf("Quantidade: %d\n", produtos[i].quantidade);
            printf("\n");
            estoqueBaixo = 1;
        }
    }
    if (!estoqueBaixo) {
        printf("\nNenhum produto com baixo estoque\n\n");
    }
}

//-------------------------------------------------- MAIN ---------------------------------------------------

int main(){
        struct Produto produtos[] = {        //define arrary de struct com os produtos
        {"Guitarra", 1200.50, 101, 10, 5},
        {"Pedal de Efeito", 450.00, 102, 4, 8},
        {"Amplificador", 2000.00, 103, 2, 1},
        {"Cabo P10", 50.00, 104, 30, 10},

    int tamanho = sizeof(produtos) / sizeof(produtos[0]); // sizeof[] parar definir o tamanho total dos vetores, [lembrar de sempre que adicionar algum vetor novo, rodar o sizeof de novo]

    int user;
    char password[256];
    int menu = 0;
    char opcao[20];
    int reset = 0;

    printf("Digite [1] para cliente ou [2] para administrador do sistema.\n");
    scanf("%d", &user);
    getchar();

    if (user == 1){ // se verdadeiro, então user = cliente
        while(menu !=5){
            if(reset==0){
                printf("\nEscolha a opção desejada:\n");
                printf("1 - Buscar produto pelo nome\n");
                printf("2 - Mostrar os produtos por ordem alfabetica\n");
                printf("3 - Ordenar produtos pelo menor valor\n");
                printf("4 - Voltar para o inicio\n");
                printf("5 - Finalizar o sistema\n");
                scanf("%d", &menu);
                reset =1;
            }
            switch(menu){
                case 1:  {  //chama a função buscar produto pelo nome
                    char nomeBusca[50];
                    printf("Digite o nome do produto que deseja buscar: ");
                    fgets(nomeBusca, sizeof(nomeBusca), stdin);

                    int indice = buscarProdutoPorNome(produtos, tamanho, nomeBusca);
                    if (indice != -1) {
                        printf("\nProduto encontrado:\n");
                        printf("Nome: %s\n", produtos[indice].nome);
                        printf("Preco: R$ %.2f\n", produtos[indice].preco);
                        printf("Quantidade: %d\n", produtos[indice].quantidade);
                    } else {
                        printf("\nProduto nao encontrado.\n");
                    }
                }
                    break;

                case 2: //chama função ordenar produtos por ordem alfabetica
                    printf("\nFuncao de ordenar por ordem alfabetica - AINDA NAO FEITA\n");
                    reset =0;
                    break;

                case 3: //chama funçao ordenar produtos menor valor
                    ordenarProdutosPorPreco(produtos, tamanho);
                    reset =0;
                    break;

                case 4: //voltar pro inicio do main, pergunta se é clinete ou adm
                    printf("Teste 4\n");
                    reset =0;
                    break;

                case 5: // finaliza a função
                    printf("\nSistema finalizado\n");
                    break;

                default:
                    printf("Opcoes invalidas, tente novamente.\n");
            }
        }
    }else{ // se falso, então user = administrador
        while(menu !=5){
            if(reset==0){
                printf("1- Verificar estoque\n");
                printf("2- Buscar produto pelo nome\n");
                printf("3- alterar estoque\n");
                printf("4 - Mostrar os produtos por ordem alfabetica\n");
                printf("5- Finalizar o sistema\n");
                printf("\nDigite a opção: \n");
                scanf("%d", &menu);
                reset =1;
                }

            switch(menu){

                case 1: //chama a função de verificar o estoque
                    verificarEstoque(produtos, tamanho);
                    reset =0;
                    break;

                case 2: //chama a função buscar produto pelo nome
                    {char nomeBusca[50];
                    printf("Digite o nome do produto que deseja buscar: ");
                    fgets(nomeBusca, sizeof(nomeBusca), stdin);

                    int indice = buscarProdutoPorNome(produtos, tamanho, nomeBusca);
                    if (indice != -1) {
                        printf("\nProduto encontrado:\n");
                        printf("Nome: %s\n", produtos[indice].nome);
                        printf("Preco: R$ %.2f\n", produtos[indice].preco);
                        printf("Codigo: %d\n", produtos[indice].codigo);
                        printf("Quantidade: %d\n", produtos[indice].quantidade);
                        printf("Nivel Minimo: %d\n", produtos[indice].nivelMinimo);
                    } else {
                        printf("\nProduto nao encontrado.\n");
                    }
                    reset =0;
                    break;}

                case 3: //chama função de alterar estoque
                    printf("\nFuncao de alterar o estoque - AINDA NAO FEITA\n\n");
                    reset =0;
                    break;

                case 4: //chama função ordenar produtos por ordem alfabetica
                    printf("\nFuncao de ordenar por ordem alfabetica - AINDA NAO FEITA\n\n");
                    reset =0;
                    break;

                case 5: // finaliza a função
                    printf("\nSistema finalizado\n");
                    break;

                default:
                printf("Opcoes invalidas, tente novamente.");
            }
        }
    }
return 0;
}