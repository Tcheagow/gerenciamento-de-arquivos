#include <stdio.h>
#include <assert.h>
#include <string.h>

#define FS_SIZE 1024  // Tamanho do disco em blocos
#define BLOCK_SIZE 2048  // Tamanho de cada bloco em bytes
#define MAGIC_NUMBER 0x12345678  // Número mágico para identificar um disco formatado

typedef struct {
    int magic;  // Número mágico para identificar o disco formatado
    int size;  // Tamanho do disco em blocos
    int root;  // Número do bloco do diretório raiz
} superblock_t;

static FILE *fd;

void block_init( void) {
	int ret;

	fd = fopen( "./disk", "r+");
	if ( fd == NULL) 
		fd = fopen( "./disk", "w+");
	assert( fd);

	ret = fseek( fd, 0, SEEK_SET);
	assert( ret == 0);
}

void block_write( int block, char *mem) {
	int ret;

	ret = fseek( fd, block * BLOCK_SIZE, SEEK_SET);
	assert( ret == 0);

	ret = fwrite( mem, 1, BLOCK_SIZE, fd);
	assert( ret == BLOCK_SIZE);
}

void bzero_block( char *block) {
	int i;
    printf("escreve 0");
	for ( i = 0; i < BLOCK_SIZE; i++)
		block[i] = 0;
}

void block_read(int block, char *mem) {
    int ret;

    ret = fseek(fd, block * BLOCK_SIZE, SEEK_SET);

    ret = fread(mem, 1, BLOCK_SIZE, fd);

    if (ret != BLOCK_SIZE) {
        bzero_block(mem + ret);
    }
}


int fs_mkfs( void) {
    superblock_t superblock;
    char block[BLOCK_SIZE];

    superblock.magic = MAGIC_NUMBER;
    superblock.size = FS_SIZE;
    superblock.root = 1;

    bzero_block(block); 
    memcpy(block, &superblock, sizeof(superblock));
    block_write(0, block);

    bzero_block(block);
    block_write(1, block);

    return 0;
}

void fs_init( void) {
    block_init();

    if(fd == NULL) {
        printf("null");
    }

    superblock_t superblock;
    char block[BLOCK_SIZE];

    block_read(0, block);

    int magic_number;
    memcpy(&magic_number, block, sizeof(int));
    printf("Número mágico: %d\n", magic_number);

    if (magic_number == MAGIC_NUMBER) {
        printf("Disco formatado encontrado. Montando o sistema de arquivos...\n");
    } else {
        printf("Disco não formatado encontrado.\n");
        fs_mkfs();
    }
}
//Carlos, usei esse arquivo pra testar o programa, aqui é mais fácil de executar

int main()
{
    fs_init();

    return 0;
}