#include <time.h>

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
    Transaction* transactions; //Transaction transaction_pool[TRANSACTION_POOL_SIZE]; mas não sei qual vai ser o tamanho da pool before run
    //Alocar memoria no runtime para esta transcations e no fim, fazer free!
}Transaction_pool;

//POW TBD
//BLOCKCHAIN LEDGER TBD
