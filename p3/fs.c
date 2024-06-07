#include "util.h"
#include "common.h"
#include "block.h"
#include "fs.h"

#ifdef FAKE
#include <stdio.h>
#define ERROR_MSG(m) printf m;
#else
#define ERROR_MSG(m)
#endif

void fs_init( void) {
    block_init();

    superblock_t superblock;
    
    block_read(0, (char*)&superblock);

    if (superblock.magic == MAGIC_NUMBER) {
        printf("Disco formatado encontrado. Montando o sistema de arquivos...\n");
    } else {
        printf("Disco não formatado encontrado.\n");
        fs_mkfs();
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

int fs_open( char *fileName, int flags) {
    return -1;
}

int fs_close( int fd) {
    return -1;
}

int fs_read( int fd, char *buf, int count) {
    return -1;
}
    
int fs_write( int fd, char *buf, int count) {
    return -1;
}

int fs_lseek( int fd, int offset) {
    return -1;
}

int fs_mkdir( char *fileName) {
    return -1;
}

int fs_rmdir( char *fileName) {
    return -1;
}

int fs_cd( char *dirName) {
    return -1;
}

int 
fs_link( char *old_fileName, char *new_fileName) {
    return -1;
}

int fs_unlink( char *fileName) {
    return -1;
}

int fs_stat( char *fileName, fileStat *buf) {
    return -1;
}

