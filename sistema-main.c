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

// ------------------------------------ Funcao de Alterar o Estoque -------------------------------------------

void alterarEstoque(struct Produto produtos[], int *tamanho, int capacidade) {
    int opcao;                                                            //declara a variavel opcao
    printf("\nOpcoes:\n");
    printf("1 - Adicionar um novo produto\n");
    printf("2 - Alterar os dados de um produto existente\n");
    printf("Digite sua escolha: ");
    scanf("%d", &opcao);                                                  //passa o valor digitado para o endereco OPCAO
    getchar();                                                            // Limpa o buffer do teclado

    if (opcao == 1) {                                                     // Opcao 1 = "Adicionar novo produto"
        if (*tamanho >= capacidade) {                                     // Se o valor do ponteiro tamanho é maior que a capacidade
            printf("\nCapacidade maxima atingida! Nao é possível adicionar mais produtos.\n");
            return;
        }

        struct Produto novoProduto;                                         //declara o Struct para Adicionar um novo produto
        printf("\nDigite o nome do produto: ");
        fgets(novoProduto.nome, sizeof(novoProduto.nome), stdin);           //Pega a string digita e joga pro nome do produto
        strtok(novoProduto.nome, "\n");                                     // Remove o '\n' no final da string
        printf("Digite o novo preco do produto: ");
        scanf("%f", &novoProduto.preco);                                    //Joga o float digitado para o preco do novo produto
        printf("Digite o novo codigo do produto: ");
        scanf("%d", &novoProduto.codigo);                                   //Joga o inteiro digitado para o codigo do novo produto
        printf("Digite a nova quantidade do produto: ");
        scanf("%d", &novoProduto.quantidade);                               //Joga o inteiro digitado para a quantidade do novo produto
        printf("Digite o novo nivel minimo de estoque: ");
        scanf("%d", &novoProduto.nivelMinimo);                              //Joga o inteiro digitado para o nivelminimo do novo produto


        produtos[*tamanho] = novoProduto;                                   // Valor da variavel tamanho é incrementada em 1 ao adicionar um novo produto
        (*tamanho)++;                                                       // usa aritmetica de ponteiro para adicionar um endereco ao vetor
        printf("\nProduto adicionado com sucesso!\n\n");

    } else if (opcao == 2) {                                                // Opcao 2 = "Alterar os dados de um produto existente"

        char nomeBusca[50];                                                 // Declara um vetor tipo char com 50 posiçoes para nomeBusca
        printf("\nDigite o nome do produto que deseja alterar: ");
        fgets(nomeBusca, sizeof(nomeBusca), stdin);                         // Joga o que o usuario digitar na variavel nomeBusca
        strtok(nomeBusca, "\n");                                            // Remove o '\n' no final da string

        int indice = buscarProdutoPorNome(produtos, *tamanho, nomeBusca);   // Declara a variavel indice como o retorno da funcao bsucarProdutoPorNome
        if (indice != -1) {                                                 // se o indice é diferente de -1 o produto existe
            printf("\nProduto encontrado! \nInsira os novos dados:\n\n");
            printf("Nome atual: %s\n", produtos[indice].nome);
            printf("Digite o novo nome (digite -1 para manter): ");
            char novoNome[50];                                              // Declara um vetor tipo char com 50 posiçoes para novoNome
            fgets(novoNome, sizeof(novoNome), stdin);                       // Joga o que o usuario digitar na variavel novoNome
            if (novoNome[0] != '\n') {                                      // Se a primeira posicao do vetor for um '\n'
                strtok(novoNome, "\n");                                     // retira a linha do vetor
                strcpy(produtos[indice].nome, novoNome);                    // Substitui o nome do produto antigo, pelo novo nome
            }

            printf("Preco atual: R$ %.2f\n", produtos[indice].preco);
            printf("Digite o novo preco (digite -1 para manter): ");
            float novoPreco;                                                // declara a variavel float novoPreco
            scanf("%f", &novoPreco);                                        // coloca o que foi digitado no endereco da variavel novoPreco
            if (novoPreco >= 0) {
                produtos[indice].preco = novoPreco;                         // Substitui o preco do produto antigo, pelo novo preco
            }

            printf("Quantidade atual: %d\n", produtos[indice].quantidade);
            printf("Digite a nova quantidade (digite -1 para manter): ");
            int novaQuantidade;                                             // declara a variavel int novoQuantidade
            scanf("%d", &novaQuantidade);                                   // coloca o que foi digitado no endereco da variavel novaQuantidade
            if (novaQuantidade >= 0) {
                produtos[indice].quantidade = novaQuantidade;               // Substitui a quantidade do produto antigo, pelo nova quantidade
            }

            printf("Nivel minimo atual: %d\n", produtos[indice].nivelMinimo);
            printf("Digite o novo nivel minimo (digite -1 para manter): ");
            int novoNivelMinimo;                                            // declara a variavel int novoNivelMinimo
            scanf("%d", &novoNivelMinimo);                                  // coloca o que foi digitado no endereco da variavel novoNivelMinimo
            if (novoNivelMinimo >= 0) {
                produtos[indice].nivelMinimo = novoNivelMinimo;             // Substitui a nivelMinimo do produto antigo, pelo novo NivelMinimo
            }

            printf("\nProduto atualizado com sucesso!\n\n");
        } else {
            printf("\nProduto nao encontrado\n");
        }
    } else {
        printf("\nOpcao invalida\n");
    }
}

// ----------------------------- Função para ordenar os produtos pelo menor preço ---------------------------

int compararPorPreco(const void *a, const void *b) {                        // Dentro da funcao as constantes 'a' e 'b' sao declaradas como ponteiros
    struct Produto *produtoA = (struct Produto *)a;                         // transforma o ponteiro genérico 'a' em um ponteiro para struct Produto
    struct Produto *produtoB = (struct Produto *)b;                         // transforma o ponteiro genérico 'b' em um ponteiro para struct Produto
                                                                            // O operador de seta (->) é usado para acessar o campo preco dentro das estruturas apontadas pelos ponteiros
    if (produtoA->preco < produtoB->preco) return -1;                       // Se o preço de produtoA for menor que o de produtoB, retorna -1, indicando que produtoA vem antes de produtoB
    if (produtoA->preco > produtoB->preco) return 1;                        // Se o preço de produtoA for maior que o de produtoB, retorna 1, indicando que produtoA vem depois de produtoB
    return 0;                                                               // Se os preços forem iguais, retorna 0, indicando que a ordem dos dois produtos é irrelevante para a ordenação
}

void ordenarProdutosPorPreco(struct Produto produtos[], int tamanho) {      // funcao de ordenar produtos por preco, recebe o vetor produtos e a variavel tamanho
    qsort(produtos, tamanho, sizeof(struct Produto), compararPorPreco);     // usa a funcao do C para rodar o algoritmo "quick sort", e chama a funcao compararPorPreco

    printf("\nProdutos ordenados pelo menor preco:\n\n");
    for (int i = 0; i < tamanho; i++) {                                     // Laco para mostrar os produtos ordenados
        printf("Nome: %s\n", produtos[i].nome);
        printf("Preco: R$ %.2f\n", produtos[i].preco);
        printf("Codigo: %d\n", produtos[i].codigo);
        printf("Quantidade: %d\n", produtos[i].quantidade);
        printf("Nível Minimo: %d\n\n", produtos[i].nivelMinimo);
    }
}

// ----------------------------- Função para buscar produto pelo nome ---------------------------------------

int buscarProdutoPorNome(struct Produto produtos[], int tamanho, const char* nomeBusca) {   // funcao de buscar produtos pelo nome, recebe como argunto vetor produtos, o tamanho e um ponteiro char nomeBusca
    for (int i = 0; i < tamanho; i++) {                                                     // laco percorre o array
        if (strncasecmp(produtos[i].nome, nomeBusca, strlen(nomeBusca)) == 0) {             // compara cada caracter de cada posicao do vetor de struct com o nomeBusca
            return i;                                                                       // Retorna o índice do produto encontrado
        }
    }
    return -1;                                                                              // Produto não encontrado
}

// ----------------------------- Função para ordenar os produtos por ordem alfabética ---------------------------

int compararPorNome(const void *a, const void *b) {                                         // Dentro da funcao as constantes 'a' e 'b' sao declaradas como ponteiros
    struct Produto *produtoA = (struct Produto *)a;                                         // transforma o ponteiro genérico 'a' em um ponteiro para struct Produto
    struct Produto *produtoB = (struct Produto *)b;                                         // transforma o ponteiro genérico 'b' em um ponteiro para struct Produto

    return strcmp(produtoA->nome, produtoB->nome);                                          // Compara as duas strings produtoA->nome e produtoB->nome caractere por caractere
}

void ordenarProdutosPorNome(struct Produto produtos[], int tamanho, int user) {             // funcao de ordenar por ordem alfabetica, recebe como argunto vetor produtos, o tamanho e o valor de user

    qsort(produtos, tamanho, sizeof(struct Produto), compararPorNome);

    printf("\nProdutos ordenados por ordem alfabetica:\n\n");                                 // Exibe os produtos ordenados
    if(user == 0){                                                                          // User 0 (Admin)
        for (int i = 0; i < tamanho; i++) {
            printf("Nome: %s.\n", produtos[i].nome);
            printf("Preço: R$ %.2f.\n", produtos[i].preco);
            printf("Código: %d.\n", produtos[i].codigo);
            printf("Quantidade: %d.\n", produtos[i].quantidade);
            printf("Nível Mínimo: %d.\n\n", produtos[i].nivelMinimo);
            printf("\n");
        }
    }else{                                                                                  // Caso user seja 1 (Cliente), nao mostra o codigo e o nivel minimo
        for (int i = 0; i < tamanho; i++) {
            printf("Nome: %s\n", produtos[i].nome);
            printf("Preco: R$ %.2f\n", produtos[i].preco);
            printf("Quantidade: %d\n", produtos[i].quantidade);
            printf("\n");
        }
    }
}

// ----------------------------- Função para verificar produtos com baixo estoque ---------------------------

void verificarEstoque(struct Produto produtos[], int tamanho) {                             // funcao para verificar o estoque, recebe como argunto vetor produtos e o tamanho
    int estoqueBaixo = 0;
    printf("\nProdutos com baixo estoque:\n");
    for (int i = 0; i < tamanho; i++) {
        if (produtos[i].quantidade < produtos[i].nivelMinimo) {                             // verifica se algum produto do vetor esta abaixo do seu estoque minimo pre definido
            printf("Nome: %s.\n", produtos[i].nome);
            printf("Quantidade: %d.\n\n", produtos[i].quantidade);
            estoqueBaixo = 1;
        }
    }
    if (!estoqueBaixo) {                                                                    // nenhum produto esta abaixo do estoque minimo
        printf("\nNenhum produto com baixo estoque.\n\n");
    }
}

// ----------------------------- Função para entrada numérica segura ---------------------------------------

int lerInteiro(const char* mensagem) {                                                      // Funcao lerInteiro, recebe como argumento uma constatnte char tipo ponteiro para mensagem
    int valor;                                                                              // declara uma variavel inteiro valor
    while (1) {                                                                             // enquanto 1
        printf("%s", mensagem);                                                             // printa a string da mensagem
        if (scanf("%d", &valor) == 1) {                                                     // se o valor digitado (colocado no endereco de memoria da variavel valor) for igual a 1
            while (getchar() != '\n');                                                      // Limpa o buffer
            return valor;                                                                   // retorna o que foi digitado
        } else {                                                                            // se o scanf for 0 - entrada invalida
            printf("Entrada invalida! Tente novamente.\n");
            while (getchar() != '\n');                                                      // Limpa o buffer
        }
    }
}

//-------------------------------------------------- MAIN ---------------------------------------------------

int main() {
    int capacidade = 100;                                                                   // Capacidade máxima do vetor de produtos
    struct Produto produtos[] = {
        {"Guitarra", 1200.50, 101, 5, 10},
        {"Pedal de Efeito", 450.00, 102, 8, 4},
        {"Amplificador", 2000.00, 103, 1, 2},
        {"Cabo P10", 50.00, 104, 10, 30},
    };

    int user, menu = 0, reset = 0, tamanho = 4;                                             // Declara a variaveis do tipo inteiro;

    user = lerInteiro("Digite [1] para cliente ou [2] para administrador do sistema: ");    // A variavel user recebe o que for digitado em lerInteiro
    if (user == 1) {                                                                        // user = 1 -> CLIENTE
        while (menu != 4) {                                                                 // enquanto Menu for diferente de 4, o laço fica mostrando o menu
            if (reset == 0) {                                                               // variavel reset colocada para evitar loops extras
                printf("\n------------------CLIENTE-------------------\n");
                printf("1 - Buscar produto pelo nome\n");
                printf("2 - Mostrar os produtos por ordem alfabetica\n");
                printf("3 - Mostrar produtos pelo menor valor\n");
                printf("4 - Finalizar o sistema\n");
                menu = lerInteiro("Digite a opcao: ");                                      // A variavel menu recebe o que for digitado em lerInteiro
                reset = 1;                                                                  // sempre que termina de mostrar o menu, muda a variavel reset para 1
            }
            switch (menu) {                                                                 // Inicia o switch do menu
                case 1: {                                                                   // Caso 1 - "Buscar produto pelo nome"
                    char nomeBusca[50];
                    printf("\nDigite o nome do produto que deseja buscar: ");
                    fgets(nomeBusca, sizeof(nomeBusca), stdin);                             // Joga o que o usuario digitar na variavel nomeBusca
                    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';                             // Remove o \n

                    int indice = buscarProdutoPorNome(produtos, tamanho, nomeBusca);        // Declara a variavel indice como o retorno da funcao buscarProdutoPorNome
                    if (indice != -1) {                                                     // Se o retorno da funcao for diferente de -1 signfica que um produto foi encontrado
                        printf("\nProduto encontrado:\n");
                        printf("Nome: %s\n", produtos[indice].nome);                       // Usa o indice do produto encontrado para achar o nome
                        printf("Preco: R$ %.2f\n", produtos[indice].preco);                // Usa o indice do produto encontrado para achar o preco
                        printf("Quantidade: %d\n\n", produtos[indice].quantidade);         // Usa o indice do produto encontrado para achar o quantidade
                    } else {
                        printf("\nProduto nao encontrado.\n\n");
                    }
                }
                reset = 0;                                                                  // sempre que roda um case, muda a variavel reset para 0 antes do break
                break;

                case 2:                                                                     // Caso 2 - "Mostrar os produtos por ordem alfabetica"
                    ordenarProdutosPorNome(produtos, tamanho, user);                        // Chama a funcao ordenarProdutosPorNome
                    reset = 0;
                    break;

                case 3:                                                                     // Caso 3 - "Mostrar produtos pelo menor valor"
                    ordenarProdutosPorPreco(produtos, tamanho);                             // Chama a funcao ordenarProdutosPorPreco
                    reset = 0;
                    break;

                case 4:                                                                     // Caso 4 - "Finaliza o Sistema"
                    printf("\nSistema finalizado.\n");
                    break;

                default:                                                                    // Caso nenhuma opcao digitada seja valida
                    printf("Opcao invalida! Tente novamente.\n");
                    reset = 0;
            }
        }
    } else if (user == 2) {                                                                 // user = 2 -> ADMINISTRADOR
        int senhaAdmin = lerInteiro("\nDigite a senha de administrador: ");                   // A variavel senhaAdmin recebe o que for digitado em lerInteiro
        if (senhaAdmin == 1234) {                                                           // verifica se a senha é igual a 1234, se for acesso permitido
            printf("\nSenha correta! Acesso permitido.\n\n");
            while (menu != 5) {                                                             // enquanto Menu for diferente de 5, o laço fica mostrando o menu
                if (reset == 0) {
                    printf("----------------ADMINISTRADOR-----------------\n");
                    printf("1- Verificar estoque\n");
                    printf("2- Buscar produto pelo nome\n");
                    printf("3- Alterar estoque\n");
                    printf("4- Mostrar os produtos por ordem alfabetica\n");
                    printf("5- Finalizar o sistema\n");
                    menu = lerInteiro("Digite a opcao: ");                                  // A variavel menu recebe o que for digitado em lerInteiro
                    reset = 1;
                }
                switch (menu) {                                                             // Inicia o switch do menu
                    case 1:                                                                 // Caso 1 - "Verificar Estoque"
                        verificarEstoque(produtos, tamanho);                                // Chama a funcao verificarEstoque
                        reset = 0;
                        break;

                    case 2: {                                                               // Caso 2 - "Buscar produto pelo nome"
                        char nomeBusca[50];
                        printf("\nDigite o nome do produto que deseja buscar: ");
                        fgets(nomeBusca, sizeof(nomeBusca), stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                        int indice = buscarProdutoPorNome(produtos, tamanho, nomeBusca);
                        if (indice != -1) {                                                 // Busca é a mesma funcao ja comentada em cliente
                            printf("\nProduto encontrado!\n\n");                              // Quando admin, mostra tambem o Codigo e o Nivel minimo do produto
                            printf("Nome: %s\n", produtos[indice].nome);
                            printf("Preco: R$ %.2f\n", produtos[indice].preco);
                            printf("Codigo: %d\n", produtos[indice].codigo);
                            printf("Quantidade: %d\n", produtos[indice].quantidade);
                            printf("Nivel Minimo: %d\n\n", produtos[indice].nivelMinimo);
                        } else {
                            printf("\nProduto nao encontrado.\n\n");
                        }
                        reset = 0;
                        break;
                    }

                    case 3:                                                                 // Caso 3 - "Alterar estoque"
                        alterarEstoque(produtos, &tamanho, capacidade);                     // Chama a funcao alterarEstoque
                        reset = 0;
                        break;

                    case 4:                                                                 // Caso 4 - "Mostrar os produtos por ordem alfabetica"
                        user = 0;
                        ordenarProdutosPorNome(produtos, tamanho, user);                    // Chama a funcao ordenarProdutosPorNome
                        reset = 0;
                        break;

                    case 5:                                                                 // Caso 5 - Finaliza o sistema
                        printf("\nSistema finalizado.\n");
                        break;

                    default:                                                                // Caso nenhuma opcao digitada seja valida
                        printf("Opcao invalida! Tente novamente.");
                        reset = 0;
                }
            }
        } else {                                                                            // senha incorreta, acesso negado
            printf("\nSenha incorreta! Acesso negado.\n\n");
        }
    } else {                                                                                // caso nao coloque uma opcao valida de cliente ou admin
        printf("Opcao invalida! Reinicie o sistema.\n");
    }
    return 0;
}