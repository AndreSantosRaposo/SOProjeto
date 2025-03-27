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


typedef struct transaction_pool{
    int current_block_id;
    Transaction transaction_pool[1000]; //mas não sei qual vai ser o tamanho da pool before run
}Transaction_pool;

//POW TBD

//BLOCKCHAIN LEDGER
typedef struct blockchain_ledger
{
    Block blocks[1000]; //tamanho temporário
}Blockchain_ledger;
