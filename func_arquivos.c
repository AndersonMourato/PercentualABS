#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "func_arquivos.h"
#include "func_percentual.h"

struct st_produtos{
    int codigo;
    char nome[50];
}produtos[20000]; //qtd linhas

struct st_prodControlado{
    int codigo;
    char nome[50];
}controlados[5000]; //qtd linhas

struct st_novaLista{
    int codigo;
    char nome[50];
    float preco, precoFinal;
    int prom1, prom2;
}novoProd[1000]; //qtd linhas

int lin;
int qtlin_contro;
int qtlin_novo;
int op = 0;


char parametros(char local[20]){
    char end[50],id[20];
    //Verificar parametro com endereço padrão para consulta dos dados
    FILE * param;
    param = fopen("Arquivos/param.txt","r");
    if(param == NULL){
        printf("ERRO! Parametro nao Definodo..");
    }
    for(int i =0; i<5;i++){
        fgets(end,50,param);
        strcpy(id,strtok(end,"\t"));
        strcpy(end,strtok(NULL,"\t"));

        if(id[20] == local[20]){
            //printf("RETORNOOOOO %s \b", end);
            return end[50];
            break;
        }
    }
    fclose(param);

}


void lerArquivoBase(){
    FILE * arq_produtos;
    char cont[100];
    arq_produtos = fopen("Arquivos/BaseGeral.txt","r");
    if(arq_produtos == NULL){
        printf("\n*Erro ao abrir arquvo BASE...*1*");
    }
    //contagem de linhas do arquivo
    while(!feof(arq_produtos)){
        fgets(cont,100,arq_produtos);
        lin++;
        if(feof(arq_produtos)){//fim do arquivo tem q abrir novamente
            fclose(arq_produtos);
            arq_produtos = fopen("Arquivos/BaseGeral.txt","r");
            if(arq_produtos == NULL){
                printf("\n*Erro ao abrir arquvo BASE...*2*");
            }
           break;
        }
    }
    //pegando informaçoes no arquivo
    for(int i=0;i<lin;i++){
        fscanf(arq_produtos,"%d",&produtos[i].codigo);
        fgets(produtos[i].nome,50,arq_produtos);
        //alterando caracter ; por um TAB
        for(int c=0;c < sizeof(produtos[i].nome);c++){
            if(produtos[i].nome[c] == ';'){
                produtos[i].nome[c] = '\t';
            }
        }
    }
    fclose(arq_produtos);
}

void lerArqControlados(){
    FILE * arq_controlados;
    char cont[100];
    arq_controlados = fopen("Arquivos/BaseControlados.txt","r");
    if(arq_controlados == NULL){
        printf("\n*Erro ao abrir arquvo CONTROLADOS...*1*");
    }
    //contagem de linhas do arquivo
    while(!feof(arq_controlados)){
        fgets(cont,100,arq_controlados);
        qtlin_contro++;
        if(feof(arq_controlados)){//fim do arquivo tem q abrir novamente
            fclose(arq_controlados);
            arq_controlados = fopen("Arquivos/BaseControlados.txt","r");
            if(arq_controlados == NULL){
                printf("\n*Erro ao abrir arquvo BASE...*2*");
            }
           break;
        }
    }
    //pegando informaçoes no arquivo
    for(int i=0;i<qtlin_contro;i++){
        fscanf(arq_controlados,"%d",&controlados[i].codigo);
        fgets(controlados[i].nome,50,arq_controlados);
        //alterando caracter ; por um TAB
        for(int c=0;c < sizeof(controlados[i].nome);c++){
            if(controlados[i].nome[c] == ';'){
                controlados[i].nome[c] = '\t';
            }
        }
    }
    fclose(arq_controlados);
}
void limparNovoArq(){
    FILE * arq_novo;
    arq_novo = fopen("Arquivos/Lista.txt","w");
    if(arq_novo == NULL){
        printf("\n----------> Erro ao criar novo arquivo!\n");
    }
   fclose(arq_novo);
}

void imprimirProdutos(){
    //LISTA imprimindo informaçoes do arquivo
    for(int i=0;i<lin;i++){
        printf("%d|\t%d", i, produtos[i].codigo);
        printf("%s", produtos[i].nome);
    }
    system("pause");
    menu();
}

void imprimirControlados(){
    //LISTA imprimindo informaçoes do arquivo
    for(int i=0;i<qtlin_contro;i++){
        printf("%d|\t%d", i, controlados[i].codigo);
        printf("%s", controlados[i].nome);
    }
    system("pause");
    menu();
}

void pesquisaControlado(){
    char opcao[10];
    int codigo;
    int r_cod = 0;
    do{
        printf("\nDigite o Codigo: ");
        scanf(" %s",&opcao);

        operacao(opcao);
        codigo = atoi(opcao);

        for(int i = 0; i<qtlin_contro;i++){
            if(controlados[i].codigo == codigo){
                r_cod = i;
                break;
            }
        }
        if(r_cod != 0){
            printf("\n----------> Produto Encontrado na Base de CONTROLADOS!");
            printf("\n-----------------------------------------------------------------------------------\n");
            printf("\t%d\t%s",controlados[r_cod].codigo, controlados[r_cod].nome);
            printf("-----------------------------------------------------------------------------------\n");
        }else{
            printf("\n----------> Produto 'NAO' Encontrado na Base de CONTROLADOS!\n");
        }
    r_cod = 0;
    }while(1);
}

void imprimirListaNova(){
    int qtlin = 0;
    FILE * arq_novo;
    arq_novo = fopen("Arquivos/Lista.txt","r");

    while(!feof(arq_novo)){
        qtlin++;
        fgets(novoProd[qtlin].nome,100,arq_novo);
        if(feof(arq_novo)){//fim do arquivo tem q abrir novamente
            fclose(arq_novo);
            arq_novo = fopen("Arquivos/Lista.txt","r");
            if(arq_novo == NULL){
                printf("\n*Erro ao abrir arquvo LISTA...*2*");
            }
           break;
        }
    }
    printf("|---------------------------------------- LISTA PERSONALIZADA ----------------------------------------------------|");
    printf("\n|-----------------------------------------------------------------------------------------------------------------|\n");
    for(int i=1;i <qtlin; i++){
        printf("|%i|   %s",i, novoProd[i].nome);
        printf("|-----------------------------------------------------------------------------------------------------------------|\n");
    }
    system("pause");
}

void gravarNovoArq(){
    char opcao[10];
    int codigo;
    int retorno;
    FILE * arq_novo;

    //criando e gravando um novo arquivo
    arq_novo = fopen("Arquivos/Lista.txt","a+");
    if(arq_novo == NULL){
        printf("\n----------> Erro ao criar novo arquivo!\n");
    }
        printf("------> Infome codigo a codigo para montar uma LISTA.\n");
    do{
        printf("Codigo: ");
        scanf(" %s", &opcao);

        codigo = atoi(opcao);
        if(codigo == 0){
            fclose(arq_novo);
            opcao[0] = toupper(opcao[0]);// Convertendo o caracter p maiusculo
            if(opcao[0] =='S' || opcao[0] =='M'){
                imprimirListaNova();
            }
            operacao(opcao);
        }
        //procura prod registrado na base
        for(int i = 0; i<lin;i++){
            if(produtos[i].codigo == codigo){
                printf("\t|\t%d", produtos[i].codigo);
                printf("%s", produtos[i].nome);
                printf("-----------------------------------------------------------------------------------\n");
                fprintf(arq_novo,"%d", produtos[i].codigo);
                fprintf(arq_novo,"%s", produtos[i].nome);

                novoProd[qtlin_novo].codigo = produtos[i].codigo;
                strcpy(novoProd[qtlin_novo].nome, produtos[i].nome);

                qtlin_novo++;
                retorno = 1;
                break;
            }else{
                retorno = 0;
            }
        }
        //nao encontrou na base - informa manualmente
        if(retorno == 0){
            char resp = 'N';
            printf("    *Nao localizado.. Informar a descricao manualmente? [S]sim / [N]nao\n");
            scanf(" %c", &resp);
            fflush(stdin); // LIMPAR BULFFER
            if(resp == 'S'||resp == 's'){
                novoProd[qtlin_novo].codigo = codigo;
                printf("DESCRICAO: ");
                gets(novoProd[qtlin_novo].nome);
                printf("\t|\t%d\t", novoProd[qtlin_novo].codigo);
                printf("%s", novoProd[qtlin_novo].nome);
                printf("\n-----------------------------------------------------------------------------------\n");

                fprintf(arq_novo,"%d\t", novoProd[qtlin_novo].codigo);
                fprintf(arq_novo,"%s \n", novoProd[qtlin_novo].nome);
                qtlin_novo++;
            }else{
                printf("Continuar com Outro ");
            }
        }
    }while(1);
    fclose(arq_novo);
}

void gravarNovoArqPromo(){
    char opcao[10];
    int codigo;
    int retorno;
    FILE * arq_novo;

    //criando e gravando um novo arquivo
    arq_novo = fopen("Arquivos/Lista.txt","a+");
    if(arq_novo == NULL){
        printf("\n----------> Erro ao criar novo arquivo c/ promo!\n");
    }

    printf("------> Infome codigo a codigo para montar uma LISTA.\n");
    do{
        printf("Codigo: ");
        scanf(" %s", &opcao);

        codigo = atoi(opcao);
        if(codigo == 0){
            fclose(arq_novo);
            opcao[0] = toupper(opcao[0]);// Convertendo o caracter p maiusculo
            if(opcao[0] =='S' || opcao[0] =='M'){
                imprimirListaNova();
            }
            operacao(opcao);
        }

        //procura prod registrado na base e inclui preços calculando promo
        for(int i = 0; i<lin;i++){
            if(produtos[i].codigo == codigo){

                char preco[8], precoFinal[8];
                float prom1, prom2;
                double soma, pfinal, pvenda;

                printf("PRECO VENDA: R$ ");
                scanf(" %s", &preco);
                printf("PROMO INI.: ");
                scanf(" %f", &prom1);
                printf("PROMO FIM.: ");
                scanf(" %f", &prom2);
                printf("PRECO FINAL: R$ ");
                scanf(" %s", &precoFinal);

                pvenda = virgula(preco);
                pfinal = virgula(precoFinal);

                if(prom2 >0){// se bonificaçao
                    soma = prom1 + prom2;
                    pfinal = prom1 * pvenda / soma;
                    pfinal = roundf(pfinal * 999.999)/999.999;
                }
                // gravando informaçoes na STRUCT do arquivo novo
                novoProd[qtlin_novo].preco = pvenda;
                novoProd[qtlin_novo].prom1 = (int)prom1;
                novoProd[qtlin_novo].prom2 = (int)prom2;
                novoProd[qtlin_novo].precoFinal = pfinal;
                novoProd[qtlin_novo].codigo = produtos[i].codigo;
                strcpy(novoProd[qtlin_novo].nome, produtos[i].nome);

                //eliminando quebra de linha no fim da string "\n"
                for(int i = 0; i <sizeof(novoProd[qtlin_novo].nome);i++){
                    if(novoProd[qtlin_novo].nome[i] == '\n'){
                        novoProd[qtlin_novo].nome[i] = '\0';
                    }
                }
                printf("\n-----------------------------------------------------------------------------------------------------------------\n");
                printf("|| \t%d", novoProd[qtlin_novo].codigo);
                printf("%s", novoProd[qtlin_novo].nome);
                printf("\t%.2f", novoProd[qtlin_novo].preco);
                printf("\t%d", novoProd[qtlin_novo].prom1);
                printf("\t%d", novoProd[qtlin_novo].prom2);
                printf("\t%.2f", novoProd[qtlin_novo].precoFinal);
                printf("\n-----------------------------------------------------------------------------------------------------------------\n");

                // grava informaçoes no arquivo
                fprintf(arq_novo,"%d", novoProd[qtlin_novo].codigo);
                fprintf(arq_novo,"%s", novoProd[qtlin_novo].nome);
                fprintf(arq_novo,"\t%.2f", novoProd[qtlin_novo].preco);
                fprintf(arq_novo,"\t%d", novoProd[qtlin_novo].prom1);
                fprintf(arq_novo,"\t%d", novoProd[qtlin_novo].prom2);
                fprintf(arq_novo,"\t%.2f \n", novoProd[qtlin_novo].precoFinal);

                qtlin_novo++;
                retorno = 1;
                break;
            }else{
                retorno = 0;
            }
        }
        //nao encontrou na base - informa manualmente
        if(retorno == 0){
            char resp = 'N';
            printf("    *Nao localizado.. Informar a descricao manualmente? [S]sim / [N]nao\n");
            scanf(" %c", &resp);
            fflush(stdin); // LIMPAR BULFFER
            if(resp == 'S'||resp == 's'){


                printf("DESCRICAO: ");
                gets(novoProd[qtlin_novo].nome);

                char preco[8], precoFinal[8];
                float prom1, prom2;
                double soma, pfinal, pvenda;

                printf("PRECO VENDA: R$ ");
                scanf(" %s", &preco);
                printf("PROMO INI.: ");
                scanf(" %f", &prom1);
                printf("PROMO FIM.: ");
                scanf(" %f", &prom2);
                printf("PRECO FINAL: R$ ");
                scanf(" %s", &precoFinal);

                pvenda = virgula(preco);
                pfinal = virgula(precoFinal);

                if(prom2 >0){// se bonificaçao
                    soma = prom1 + prom2;
                    pfinal = prom1 * pvenda / soma;
                    pfinal = roundf(pfinal * 999.999)/999.999;
                }
                // gravando informaçoes na STRUCT do arquivo novo
                novoProd[qtlin_novo].codigo = codigo;
                novoProd[qtlin_novo].preco = pvenda;
                novoProd[qtlin_novo].prom1 = (int)prom1;
                novoProd[qtlin_novo].prom2 = (int)prom2;
                novoProd[qtlin_novo].precoFinal = pfinal;

                //eliminando quebra de linha no fim da string "\n"
                for(int i = 0; i <sizeof(novoProd[qtlin_novo].nome);i++){
                    if(novoProd[qtlin_novo].nome[i] == '\n'){
                        novoProd[qtlin_novo].nome[i] = '\0';
                    }
                }
                printf("\n-----------------------------------------------------------------------------------------------------------------\n");
                printf("|| \t%d\t", novoProd[qtlin_novo].codigo);
                printf("%s", novoProd[qtlin_novo].nome);
                printf("\t%.2f", novoProd[qtlin_novo].preco);
                printf("\t%d", novoProd[qtlin_novo].prom1);
                printf("\t%d", novoProd[qtlin_novo].prom2);
                printf("\t%.2f", novoProd[qtlin_novo].precoFinal);
                printf("\n-----------------------------------------------------------------------------------------------------------------\n");

                // grava informaçoes no arquivo
                fprintf(arq_novo,"%d\t", novoProd[qtlin_novo].codigo);
                fprintf(arq_novo,"%s", novoProd[qtlin_novo].nome);
                fprintf(arq_novo,"\t%.2f", novoProd[qtlin_novo].preco);
                fprintf(arq_novo,"\t%d", novoProd[qtlin_novo].prom1);
                fprintf(arq_novo,"\t%d", novoProd[qtlin_novo].prom2);
                fprintf(arq_novo,"\t%.2f \n", novoProd[qtlin_novo].precoFinal);
                qtlin_novo++;
            }else{
                printf("Continuar com Outro ");
            }
        }
    }while(1);

    fclose(arq_novo);
}
