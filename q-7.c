#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 10
#define MAX_FILES 5

// Structures to simulate the disk and files
typedef struct {
    int block_number;
    int is_free;  // 1 if free, 0 if occupied
} DiskBlock;

typedef struct {
    char file_name[20];
    int size;  // File size in terms of number of blocks
    int *blocks;  // Blocks allocated to the file
} File;

// Disk simulation (max number of blocks)
DiskBlock disk[MAX_BLOCKS];

// Function to initialize the disk
void initialize_disk() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        disk[i].block_number = i;
        disk[i].is_free = 1;  // All blocks are initially free
    }
}

// Function to allocate contiguous blocks to a file
int allocate_contiguous(File *file) {
    int start = -1;
    int count = 0;

    // Find a contiguous space for the file
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (disk[i].is_free) {
            if (count == 0) {
                start = i;  // Found the start of a contiguous region
            }
            count++;
            if (count == file->size) {
                // Allocate blocks to the file
                for (int j = start; j < start + file->size; j++) {
                    disk[j].is_free = 0;  // Mark the block as occupied
                    file->blocks[j - start] = j;  // Store the allocated block
                }
                return 1;  // Allocation successful
            }
        } else {
            count = 0;  // Reset count if a block is not free
        }
    }
    return 0;  // Not enough contiguous space
}

// Function to allocate blocks using linked allocation
int allocate_linked(File *file) {
    int previous_block = -1;
    int first_block = -1;

    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (disk[i].is_free) {
            if (first_block == -1) {
                first_block = i;  // First block of the file
            }
            if (previous_block != -1) {
                // Set the pointer from the previous block
                file->blocks[previous_block] = i;
            }
            previous_block = i;
            disk[i].is_free = 0;  // Mark the block as occupied
            file->blocks[i] = -1;  // Link the block to the next one
        }
    }

    if (first_block != -1) {
        file->blocks[previous_block] = -1;  // End of the file, no next block
        return 1;
    }
    return 0;
}

// Function to allocate blocks using indexed allocation
int allocate_indexed(File *file) {
    int index_block = -1;
    int count = 0;

    // Find a free index block
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (disk[i].is_free) {
            index_block = i;
            disk[i].is_free = 0;  // Mark the index block as occupied
            break;
        }
    }

    if (index_block == -1) return 0;  // No free index block

    // Allocate data blocks using the index block
    for (int i = 0; i < file->size; i++) {
        for (int j = 0; j < MAX_BLOCKS; j++) {
            if (disk[j].is_free) {
                disk[j].is_free = 0;  // Mark the block as occupied
                file->blocks[i] = j;  // Assign block to the file
                break;
            }
        }
    }
    return 1;
}

// Function to print the file allocation
void print_file_allocation(File file) {
    printf("File: %s, Size: %d blocks\n", file.file_name, file.size);
    printf("Allocated Blocks: ");
    for (int i = 0; i < file.size; i++) {
        printf("%d ", file.blocks[i]);
    }
    printf("\n");
}

int main() {
    File files[MAX_FILES];
    int choice;

    // Initialize the disk and files
    initialize_disk();

    // File details for simulation
    strcpy(files[0].file_name, "File1");
    files[0].size = 3;
    files[0].blocks = (int *)malloc(sizeof(int) * files[0].size);

    strcpy(files[1].file_name, "File2");
    files[1].size = 4;
    files[1].blocks = (int *)malloc(sizeof(int) * files[1].size);

    strcpy(files[2].file_name, "File3");
    files[2].size = 2;
    files[2].blocks = (int *)malloc(sizeof(int) * files[2].size);

    strcpy(files[3].file_name, "File4");
    files[3].size = 5;
    files[3].blocks = (int *)malloc(sizeof(int) * files[3].size);

    strcpy(files[4].file_name, "File5");
    files[4].size = 1;
    files[4].blocks = (int *)malloc(sizeof(int) * files[4].size);

    // Main loop to simulate file allocation strategies
    while (1) {
        printf("Select File Allocation Strategy:\n");
        printf("1. Contiguous Allocation\n");
        printf("2. Linked Allocation\n");
        printf("3. Indexed Allocation\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                for (int i = 0; i < MAX_FILES; i++) {
                    if (allocate_contiguous(&files[i])) {
                        print_file_allocation(files[i]);
                    } else {
                        printf("Not enough space for %s using contiguous allocation.\n", files[i].file_name);
                    }
                }
                break;
            case 2:
                for (int i = 0; i < MAX_FILES; i++) {
                    if (allocate_linked(&files[i])) {
                        print_file_allocation(files[i]);
                    } else {
                        printf("Not enough space for %s using linked allocation.\n", files[i].file_name);
                    }
                }
                break;
            case 3:
                for (int i = 0; i < MAX_FILES; i++) {
                    if (allocate_indexed(&files[i])) {
                        print_file_allocation(files[i]);
                    } else {
                        printf("Not enough space for %s using indexed allocation.\n", files[i].file_name);
                    }
                }
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
