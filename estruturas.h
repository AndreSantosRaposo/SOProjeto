#include <time.h>

typedef struct block //Temporário só até Paulo criar
{
    int merda; 
}Block;

typedef struct transaction{
    int id; //Ia fazer estas cenas char*, mas depois tinha de estar a alocar memória e fazer frees e tal, e não vale a pena
    int reward;
    int sender_id;
    int reciever_id;
    int value;
    time_t timestamp;
} Transaction;

//POW TBD~


//Criar as estruturas aqui
//num_miners, transacton pool slots, tansactions_per_block,blockchain_blocks
typedef struct transaction_pool{
    int current_block_id;
    Transaction *transaction_pool; //numero de slots do config file
    int empty; //se a posição está disponivel ou não
    int age;
}Transaction_pool;

//BLOCKCHAIN LEDGER
typedef struct blockchain_ledger
{
    Block *blocks; //tamanho blockchain_blocks
}Blockchain_ledger;
