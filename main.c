#include "includes.h"


#define BUFF_SIZE 2500  // Pode ser assim, mas 2500 pode ser muito grande se não for necessário.
#define PARAMETROS_CONFIG 4

Transaction_pool *sh_transaction_pool;
Blockchain_ledger *sh_blockchain_ledger;

void cleanup(){    
    #ifdef DEBUG
    printf("A limpar\n");
    #endif
    exit(0);
}

void signalHandler(int sig){
    #ifdef DEBUG
    printf("Sinal recebido...\n");
    #endif
    cleanup();
}

int main() {
    int info[PARAMETROS_CONFIG];
    int num_child_processes=0;
    readConfig(info);
    int shmid_TP, shmid_BL;
    signal(SIGINT, signalHandler);

    //Criar e dar atach às shared memories
    shmid_TP = shmget(IPC_PRIVATE, sizeof(Transaction_pool) + info[1] * sizeof(Transaction), IPC_CREAT | 0700);

    if (shmid_TP < 0) {
        perror("Erro ao criar memória partilhada");
        exit(1);
    }
    sh_transaction_pool = shmat(shmid_TP,NULL,0);
    if (sh_transaction_pool == (void *)-1) { 
        perror("Erro ao associar memória compartilhada");
        exit(1);
    }

    shmid_BL = shmget(IPC_PRIVATE, sizeof(Blockchain_ledger) + info[3] * sizeof(Block), IPC_CREAT | 0700);
    if (shmid_BL < 0) {
        perror("Erro ao criar memória partilhada");
        exit(1);
    }
    sh_blockchain_ledger = shmat(shmid_BL,NULL,0);
    if (sh_transaction_pool == (void *)-1) {
        perror("Erro ao associar memória compartilhada");
        exit(1);
    }

    //Fim criação memoria partilhada
    
    #ifdef DEBUG
    printf("Sou o processo controller (PID: %d)\n", getpid());
    #endif
    
    createProcess(validator, &num_child_processes);
    createProcess(miner,&num_child_processes);
    createProcess(statistics,&num_child_processes);
    #ifdef DEBUG
    printf("Processos: %d\n",num_child_processes);
    #endif

    for (int i = 0; i < num_child_processes; i++) {
        wait(NULL); 
    }
    
    //Remover memória partilhada (temporariamente aqui)
    shmdt(sh_transaction_pool); 
    shmctl(shmid_TP, IPC_RMID, NULL);
    shmdt(sh_blockchain_ledger); 
    shmctl(shmid_BL, IPC_RMID, NULL);

    printf("Todos os processos terminaram.\n");
    #ifdef DEBUG
    while(1); //Só ter tempo para testar receção do sinal
    #endif
    return 0;
}

void readConfig(int info[]) {
    char linha[BUFF_SIZE];
    FILE *f = fopen("config.cfg", "r");
    if (!f) {
        printf("Erro ao abrir o arquivo 'config.cfg'\n");
        exit(1); // Encerrar o programa em caso de erro
    }
    
    int i = 0;
    while (fgets(linha, BUFF_SIZE, f) != NULL) { 
        linha[strcspn(linha, "\n")] = 0; // Remove newline
        if(strlen(linha)<1){
            printf("Erro na configuração ('config.cfg')\n");
            fclose(f);
            exit(1);
        }
        // Verifica se a linha contém apenas números
        int j = 0;
        while (linha[j]) {
            if (!isdigit(linha[j])) {
                printf("Erro na configuração ('config.cfg')\n");
                fclose(f);
                exit(1);
            }
            j++;
        }
        
        info[i++] = atoi(linha);
    }
    
    fclose(f);
    if (i != PARAMETROS_CONFIG) {
        printf("Erro na configuração ('config.cfg')\n");
        exit(1);
    }

}

void createProcess(void (*func)(), int *incrementar) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Erro ao criar processo");
        exit(1);
    }
    (*incrementar)++;
    if (pid == 0) {
        func();
        exit(0); // Garante que o filho não execute o código do pai
    }
}
