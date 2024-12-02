#include <stdio.h>
#include <stdlib.h>

void Buscar_Nome() {

}

void Mostrar_Categoria() {

}

void Ordenar_Menor_Preco() {

}

void Mostrar_Prod_em_Estoque() {

}

struct Produtos {
    char name[50];
    int codigo_produto;
    float price;
    int quantidade;
};

int main(){ 

    struct Produtos Produto;

    char user[256];
    char password[256];
    int menu;

    //produtos[] //definir arrary de struct com os produtos
    // usar o sizeof[] parar definir o tamanho total dos vetores, lembrar de sempre que adicionar algum vetor novo, rodar o sizeof de novo

    printf("Você é cliente ou administrador?\n");
    scanf("%s", user);

    if(user == "cliente"){
            printf("\nEscolha a opção desejada:\n");
            printf("1 - Buscar produto pelo nome\n");
            printf("2 - Mostrar as categorias de produtos\n");
            printf("3 - Ordenar produtos pelo menor valor\n");
            printf("4 - Voltar para o inicio\n");
            printf("5 - Sair\n");

        switch(menu){
            case 1: //chama a função buscar produto pelo nome
                Buscar_Nome();
                break;
            case 2: //chama função mostrar categorias
                Mostrar_Categoria();
                break;
            case 3: //chama funçao ordenar produtos menor valor
                Ordenar_Menor_Preco();
                break;
            case 4: //voltar pro inicio do main, pergunta se é clinete ou adm

                break;
            case 5: // finaliza a função

                break;
        }

    }else{ //não é cliente, é adm
        if(user == "admin" && password == "admin"){
            printf("\nEscolha a opção desejada:\n");
            printf("1 - Buscar produto pelo nome\n");
            printf("2 - Mostrar as categorias de produtos\n");
            printf("3 - Mostrar produtos que precisam de estoque\n");
            printf("4 - Voltar para o inicio\n");
            printf("5 - Sair\n");

            switch(menu){
            case 1: //chama a função buscar produto pelo nome
                Buscar_Nome();
                break;
            case 2: //chama função mostrar categorias
                Mostrar_Categoria();
                break;
            case 3: //chama funçao produtos que precisam de estoque
                Mostrar_Prod_em_Estoque();
                break;
            case 4: //voltar pro inicio do main, pergunta se é clinete ou adm

                break;
            case 5: // finaliza a função

                break;
            }
        }
    }


    return 0;
}