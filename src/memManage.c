//
// Created by Charlie Wadds on 2023-11-13.
//


#include "../include/osSimLib.h"

bool memCheck(Memory *mem, int32_t size){
    //check there is enough memory to allocate
    if(numPartitionsFree(mem) == 0){
        return false;
    }
    if(getClosestPartition(mem, size) != -1){
        return true;
    }

    return false;

}
int getClosestPartition(Memory *mem, int32_t size){
    //get the closest partition to the size of the process
    MemoryBlock *temp = mem->tail;
    int32_t closest = mem->totalSize;
    int32_t closestID = -1;
    while(temp != NULL){
        if(temp->size >= size && temp->size < closest){
            closest = temp->size;
            closestID = temp->id;
        }
        temp = temp->next;
    }
    return closestID;
}

void setPartitionFree(Memory *mem, int32_t id){
    //set a partition to free
    MemoryBlock *temp = mem->tail;
    while(temp != NULL){
        if(temp->id == id){
            temp->free = true;
            mem->freeSize += temp->size;
            return;
        }
        temp = temp->next;
    }
    printf("Error: partition not found\n");
    return;
}

void setPartitionUsed(Memory *mem, int32_t id){
    //set a partition to used
    MemoryBlock *temp = getBlockById(mem, id);
    while(temp != NULL){
        if(temp->id == id){
            temp->free = false;
            mem->freeSize -= temp->size;
            return;
        }
        temp = temp->next;
    }
    printf("Error: partition not found\n");

}

bool addPartitionToMem(Memory *mem, int32_t size, int32_t id){
    //add a partition to the memory
    MemoryBlock *newBlock = malloc(sizeof(MemoryBlock));


    newBlock->free = true;
    newBlock->size = size;
    newBlock->id = id;
    newBlock->next = NULL;
    newBlock->prev = mem->head;
    mem->head = newBlock;
    mem->totalSize += size;
    mem->freeSize += size;
    if(mem->numBlocks == 0){

        mem->tail = newBlock;
    }
    mem->numBlocks++;
    return true;
}

MemoryBlock *getBlockById(Memory *mem, int32_t id){
    //get the number of partitions that are free
    MemoryBlock *temp = mem->head;
    int32_t numFree = 0;
    while(temp != NULL){
        if(temp->id == id){
            return temp;
        }
        temp = temp->prev;
    }
    return NULL;
}

int numPartitionsFree(Memory *mem){
    //get the number of partitions that are free
    MemoryBlock *temp = mem->head;
    int32_t numFree = 0;
    while(temp != NULL){
        if(temp->free){
            numFree++;
        }
        temp = temp->prev;
    }
    return numFree;
}