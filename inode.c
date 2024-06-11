#include <inode.h>
#include <stdlib.h>

void initialize_directory(inode_t* inode, int id) {
    inode->id = id;
    inode->type = DIRECTORY_TYPE;
    inode->directory = (directory_t*)malloc(sizeof(directory_t));
    inode->directory->num_entries = 0;
    inode->single_indirect_pointer = NULL;
    inode->double_indirect_pointer = NULL;
    inode->triple_indirect_pointer = NULL;
}