#ifndef FS_INCLUDED
#define FS_INCLUDED

// #define FS_SIZE 2048 era essa
#define FS_SIZE 1024  // Tamanho do disco em blocos
#define BLOCK_SIZE 4096  // Tamanho de cada bloco em bytes
#define MAGIC_NUMBER 0x12345678  // Número mágico para identificar um disco formatado

typedef struct {
    int magic;  // Número mágico para identificar o disco formatado
    int size;  // Tamanho do disco em blocos
    int root;  // Número do bloco do diretório raiz
} superblock_t;

void fs_init( void);
int fs_mkfs( void);
int fs_open( char *fileName, int flags);
int fs_close( int fd);
int fs_read( int fd, char *buf, int count);
int fs_write( int fd, char *buf, int count);
int fs_lseek( int fd, int offset);
int fs_mkdir( char *fileName);
int fs_rmdir( char *fileName);
int fs_cd( char *dirName);
int fs_link( char *old_fileName, char *new_fileName);
int fs_unlink( char *fileName);
int fs_stat( char *fileName, fileStat *buf);

#define MAX_FILE_NAME 32
#define MAX_PATH_NAME 256  // This is the maximum supported "full" path len, eg: /foo/bar/test.txt, rather than the maximum individual filename len.
#endif
