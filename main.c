#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "func_arquivos.h"
#include "func_percentual.h"
#include <time.h>

#include "func_arquivos.c"
#include "func_percentual.c"


int main(){

    int day = 29;
    int month = 3;
    int year = 2024;

    struct tm *data;
    time_t segundos;
    time(&segundos);
    data = localtime(&segundos);

    int current_day = data->tm_mday;
    int current_month = data->tm_mon+1;
    int current_year = data->tm_year+1900;

    if (month < current_month && year <= current_year)
    {
        printf("=========================== // CALCULO DE PERCENTUAL ABS // ================================\n\n");
        printf("Sistema Expirado em %d/%d/%d, consulte o desenvolvedor para mais informacoes.\n",day, (month), year);
        printf("\n\n\n\n\n\n=========================== // DEV. ANDERSON INACIO ...v_1.2 // ===========================\n\n");
        scanf(" %c");
    }else{
        // #EXECUTANDO O SISTEMA
        lerArquivoBase();
        lerArqControlados();
        menu();
    }


    return 0;
}

