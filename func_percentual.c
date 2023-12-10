#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "func_arquivos.h"
#include "func_percentual.h"



void operacao(char op[10]);

void menu(){
    char opcao;
    system("cls"); // Limpa a tela
    printf("\n===================== // MENU // =====================\n");
    printf("|  [B] - BONIFICACAO (PERCENTUAL)\n");
    printf("|  [D] - DESCONTO (PERCENTUAL)\n");
    printf("|  [P] - PRECO FINAL (CALCULO)\n");
    printf("|  [C] - CONSULTA CONTROLADO\n");
    printf("|  [L] - LISTA PERSONALIZADA (ARQUIVO)\n");
    printf("|  [O] - OUTROS\n");
    printf("|  [S] - SAIR\n");
    printf("=======================================================\n");
    printf("---------> Selecione uma das opcoes: ");
    scanf(" %c", &opcao);

    opcao = toupper(opcao);// Convertendo o caracter p maiusculo
    int tipo;
    char op[1];
    switch (opcao){
        case 'B':
            calc_bonifica();
            menu();
            break;
        case 'D':
            calc_desconto();
            menu();
            break;
        case 'P':
            calc_pfinal();
            menu();
            break;
        case 'C':
            pesquisaControlado();
            menu();
            break;
        case 'L':
            tipo = 0;
            printf("LISTA COM OU SEM PRECO?... [1]S/PRECO / [2]C/PRECO\n");
            scanf(" %d",&tipo);
            if(tipo == 1){
                    printf("------> SEM PRECO\n");
                gravarNovoArq();
            }
            printf("------> COM PRECO\n");
            gravarNovoArqPromo();
            break;
        case 'M':
            menu();
            break;
        case 'I':
            imprimirListaNova();
            menu();
            break;
        case 'O':
            system("cls"); // Limpa a tela
            printf("\n===================== // SUBI MENU // =====================\n");
            printf("|  [I] - EXIBIR LISTA DE ARQUIVO\n");
            printf("|  [X] - LIMPAR LISTA DE ARQUIVO\n");
            printf("|  [A] - INICIAR LISTA C/ PRECO\n");
            printf("|  [R] - INICIAR LISTA S/ PRECO\n");
            printf("|  [M] - RETORNA MENU INICIAL\n");
            printf("=======================================================\n");
            system("pause");
            menu();
            break;
        case 'X':
            limparNovoArq();
            printf("-----> Limpo!\n");
            system("pause");
            menu();
            break;
        case 'A':
            gravarNovoArqPromo();
            break;
        case 'R':
            gravarNovoArq();
            break;
        case 'S':
            printf("\n\t Programa Encerrado.. Precione Qualquer Tecla Para Fechar!\n\n");
            exit(0);
    }
}
void operacao(char op[10]){

    op[0] = toupper(op[0]);// Convertendo o caracter p maiusculo
    int tipo;
    switch (op[0]){
        case 'B':
            calc_bonifica();
            break;
        case 'D':
            calc_desconto();
            break;
        case 'P':
            calc_pfinal();
            break;
        case 'C':
            pesquisaControlado();
            break;
        case 'L':
            tipo = 0;
            printf("LISTA COM OU SEM PRECO?... [1]S/PRECO / [2]C/PRECO\n");
            scanf(" %d",&tipo);
            if(tipo == 1){
                    printf("------> SEM PRECO\n");
                gravarNovoArq();
            }
            printf("------> COM PRECO\n");
            gravarNovoArqPromo();
            break;
        case 'M':
            menu();
        case 'I':
            imprimirListaNova();
            break;
        case 'S':
            menu();
            break;
    }
}

// FUN��O PARA CONVERTER VIRGULA EM PONTO
float virgula(char vlr[10]){ // Entrando com o valor Char
    float resul;
    for(int i = 0; i <= 10; i++){ //Analisando cada caracter
        if(vlr[i] == ','){ //Convertendo a virgula em ponto
            vlr[i] = '.';
        }
    }
    resul = atof(vlr); //Convertendo para valor Float
    return resul;
}

void calc_desconto(){
    float desconto, valor_1, valor_2, resul;
    char num1[10], num2[10];
    char opcao[0];

    do{
        printf("--------------------> DESCONTO %%\n\n");
        printf("PRECO DE TABELA: R$");
        scanf(" %s", &num1);

        operacao(num1);

        printf("PRECO DA PROMOCAO: R$");
        scanf(" %s", &num2);

        valor_1 = virgula(num1); //passando na fun��o para converter a virgula em ponto
        valor_2 = virgula(num2);

        desconto = valor_1 - valor_2;
        resul = desconto * 100 / valor_1;

        printf(" /-------------------------------------\n");
        printf(" /    PR.VENDA_______R$%.2f \n", valor_1);
        printf(" /    PR.PROMOCAO____R$%.2f \n", valor_2);
        printf(" /    PERCENTUAL___________%.2f%% \n", resul);
        printf(" /-------------------------------------\n");
        printf("\n\n");
    }while(1);
}

void calc_bonifica(){
    float resul;
    float num1, num2;
    char opcao[0], num[10];

    do{
        printf("--------------------> BONIFICACAO %%\n\n");
        printf("COMPRE:");
        scanf(" %s", &num);

        operacao(num);

        printf("GANHE:");
        scanf(" %f", &num2);

        num1 = atof(num);
        resul = num2 / num1;

        printf(" /-------------------------------------\n");
        printf(" /    COMPRA___%d \n", (int)num1);
        printf(" /    GANHA____%d \n", (int)num2);
        printf(" /    PERCENTUAL__%.2f%% \n", resul);
        printf(" /-------------------------------------\n");
        printf("\n\n");
    }while(1);
}

void calc_pfinal(){
    float num1, num2;
    double prfinal, valor, soma;
    char preco[10];
    char opcao[0];
    do{
        printf("--------------------> PRECO FINAL R$\n\n");
        printf("PRECO DE VENDA: R$");
        scanf(" %s", &preco);

        operacao(preco);

        printf("COMPRA:__");
        scanf(" %f", &num1);
        printf("GANHA:___");
        scanf(" %f", &num2);

        valor = virgula(preco);//passando na fun��o para converte virgula em ponto

        soma = num1 + num2;                     //floorf <-- ARREDONDAMENTO PARA BAIXO
        prfinal = num1 * valor / soma;          //roundf <-- ARREDONDAMENTO PARA O VALOR MAIS PROXIMO
        prfinal = roundf(prfinal * 999.999)/999.999;  //ceilf <-- ARREDONDAMENTO PARA CIMA

        printf("--------------------\n");
        printf("PRECO FINAL____R$%.2f\n", prfinal);
        printf("--------------------\n");
        printf("\n\n");
    }while(1);
}
