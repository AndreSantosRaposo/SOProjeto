#include "includes.h"

#define BUFF_SIZE 2500 //Posso fazer isto assim?
#define PARAMETROS_CONFIG 4
void readConfig(int info[]) {
    char linha[BUFF_SIZE];
    FILE *f;
    f = fopen("config.cfg", "r");
    if (!f) {
        printf("Erro ao abrir o arquivo 'config.cfg'\n");
        return;
    }

    int i = 0;
    while (fgets(linha, BUFF_SIZE, f) != NULL) { 
        // Remove o \n do final
        linha[strcspn(linha, "\n")] = 0;

        // Verifica se a linha contém apenas números
        int j = 0;
        while (linha[j]) {
            if (!isdigit(linha[j])) {
                printf("Erro na configuração ('config.cfg')\n");
                fclose(f);
                return;
            }
            j++;
        }

        info[i++] = atoi(linha);
    }

    fclose(f);

    if (i != PARAMETROS_CONFIG) {
        printf("Erro na configuração ('config.cfg')\n");
    }
}

int main(){
    int info[PARAMETROS_CONFIG];
    int i;
    int id;
    readConfig(info);
    //Criar os miner processes
    if((id = fork())==0){
        validator();
    }else{
        printf("Sou o processo controller\n");
    }

    for(i=0;i<1;i++){
        wait(NULL);
    }
    return 1;
}