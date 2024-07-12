#include <stdio.h>
#include <stdlib.h>

typedef struct CacheBlock
{
    int data;
    struct CacheBlock *prev;
    struct CacheBlock *next;
} CacheBlock;

typedef struct
{
    CacheBlock *head;
} DirectoryEntry;

typedef struct
{
    DirectoryEntry *directory;
    int numNodes;
} HomeNode;

// Create a new cache block
CacheBlock *createCacheBlock(int data)
{
    CacheBlock *newBlock = (CacheBlock *)malloc(sizeof(CacheBlock));
    newBlock->data = data;
    newBlock->prev = NULL;
    newBlock->next = NULL;
    return newBlock;
}

// Initialize the home node with a specified number of nodes
HomeNode *initializeHomeNode(int numNodes)
{
    HomeNode *homeNode = (HomeNode *)malloc(sizeof(HomeNode));
    homeNode->directory = (DirectoryEntry *)malloc(numNodes * sizeof(DirectoryEntry));
    for (int i = 0; i < numNodes; i++)
    {
        homeNode->directory[i].head = NULL;
    }
    homeNode->numNodes = numNodes;
    return homeNode;
}

// Read procedure
void readProcedure(HomeNode *homeNode, int nodeIndex, int data)
{
    DirectoryEntry *entry = &homeNode->directory[nodeIndex];
    CacheBlock *block = entry->head;

    // Check if the block is in the local cache
    while (block != NULL)
    {
        if (block->data == data)
        {
            printf("Data found in cache at node %d\n", nodeIndex);
            return;
        }
        block = block->next;
    }

    // If not found, simulate fetching from the home node's main memory
    printf("Data not found in cache at node %d. Fetching from home node.\n", nodeIndex);
    CacheBlock *newBlock = createCacheBlock(data);

    // Insert the new block at the head of the list
    if (entry->head != NULL)
    {
        entry->head->prev = newBlock;
    }
    newBlock->next = entry->head;
    entry->head = newBlock;
    printf("Data inserted into cache at node %d\n", nodeIndex);
}

// Write procedure
void writeProcedure(HomeNode *homeNode, int nodeIndex, int data)
{
    DirectoryEntry *entry = &homeNode->directory[nodeIndex];
    CacheBlock *block = entry->head;

    // Check if the block is in the local cache
    while (block != NULL)
    {
        if (block->data == data)
        {
            printf("Data found in cache at node %d. Updating.\n", nodeIndex);
            block->data = data; // Update the data
            return;
        }
        block = block->next;
    }

    // If not found, simulate fetching from the home node's main memory and updating
    printf("Data not found in cache at node %d. Fetching and updating from home node.\n", nodeIndex);
    CacheBlock *newBlock = createCacheBlock(data);

    // Insert the new block at the head of the list
    if (entry->head != NULL)
    {
        entry->head->prev = newBlock;
    }
    newBlock->next = entry->head;
    entry->head = newBlock;
    printf("Data inserted and updated in cache at node %d\n", nodeIndex);
}

// Function to display the cache blocks in a node
void displayCacheBlocks(HomeNode *homeNode, int nodeIndex)
{
    DirectoryEntry *entry = &homeNode->directory[nodeIndex];
    CacheBlock *block = entry->head;
    printf("Cache blocks in node %d: ", nodeIndex);
    while (block != NULL)
    {
        printf("%d ", block->data);
        block = block->next;
    }
    printf("\n");
}

int main()
{
    int numNodes = 3;
    HomeNode *homeNode = initializeHomeNode(numNodes);

    // Simulate read and write operations
    readProcedure(homeNode, 0, 10);
    readProcedure(homeNode, 1, 20);
    writeProcedure(homeNode, 0, 30);
    writeProcedure(homeNode, 2, 40);

    // Display cache blocks
    displayCacheBlocks(homeNode, 0);
    displayCacheBlocks(homeNode, 1);
    displayCacheBlocks(homeNode, 2);

    // Free memory
    for (int i = 0; i < numNodes; i++)
    {
        CacheBlock *block = homeNode->directory[i].head;
        while (block != NULL)
        {
            CacheBlock *temp = block;
            block = block->next;
            free(temp);
        }
    }
    free(homeNode->directory);
    free(homeNode);

    return 0;
}
