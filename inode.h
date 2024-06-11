#include <block.h>

#ifndef INODE_INCLUDED
#define INODE_INCLUDED
#define NUMBER_DIRECT_BLOCKS 40 // Número total de blocos indiretos por i-node
#define MAX_LENGTH_FILE_NAME 32 /* Tamanho máximo para o nome de arquivo
    TODO: Verificar se é necessário realizar algum cálculo para obter esse valor
*/
#define MAX_DIR_ENTRIES (BLOCK_SIZE / sizeof(dir_entry_t)) 
/*  Tamanho máximo de entradas em um diretório
    TODO: Verificar se o cálculo está correto
*/

typedef struct {
    char* name;
    int inode_id;
    char* content;
} data_block_t;

typedef struct {
    data_block_t data_blocks[NUMBER_DIRECT_BLOCKS];
} single_indirect_block_t;

typedef struct {
    single_indirect_block_t single_indirect_blocks[2];
} double_indirect_block_t;

typedef struct {
    double_indirect_block_t double_indirect_blocks[2];
} triple_indirect_block_t;

typedef enum {
    FILE_T,
    DIRECTORY_TYPE
} inode_type_t;

typedef struct {
    char name[MAX_LENGTH_FILE_NAME];
    int inode_id;
} dir_entry_t;


typedef struct {
    dir_entry_t entries[MAX_DIR_ENTRIES];
    int num_entries;
} directory_t;

typedef struct {
    int id;
    inode_type_t type;
    union {
        data_block_t direct_blocks[NUMBER_DIRECT_BLOCKS];
        directory_t* directory;
    };
    single_indirect_block_t* single_indirect_pointer;
    double_indirect_block_t* double_indirect_pointer;
    triple_indirect_block_t* triple_indirect_pointer;
} inode_t;

/*
    @description: Esta função recebe como parâmetro um ponteiro para um i-node
    e um inteiro. Inicializa o i-node com o tipo DIRECTORY_TYPE e atribui a este
    o id recebido.
    @params ponteiro para um i-node e um id para este.
    @return void
*/
void initialize_directory(inode_t* inode, int id);

#endif