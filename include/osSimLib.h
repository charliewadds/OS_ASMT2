#ifndef OS_ASMT2_OSSIMLIB_H
#define OS_ASMT2_OSSIMLIB_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

//constants
//-----------------------------------------------------
#define csvBreakChar ','
#define ageIncrement 0.1
#define scheduerAlgorithm 0 //0 for FCFS, 1 for EP, 2 for RR
#define RRTimeout 100
#define useMemory 1//0 for no memory, 1 for memory

//-----------------------------------------------------

//structs and functions for process datatypes
//-----------------------------------------------------
typedef struct process{
    int32_t pid;
    int32_t arriv_time;
    int32_t total_time;
    int32_t io_freq;
    int32_t io_duration;
    int32_t memReq;
    int8_t memPart;
    double priority;
}Process;

typedef struct processLNode {//linked node containing a process
    Process* proc;
    struct processLNode *next;
    struct processLNode *prev;
}ProcessLNode;
//-------------------------------------------------------0




//structs and functions for linked list of processes
//--------------------------------------------------------
typedef struct processLL {
    ProcessLNode *head;
    ProcessLNode *tail;
    int32_t size;
}ProcessLL;

ProcessLL* createProcLL(void);
ProcessLL* llAddProc(ProcessLL* list, Process proc);
ProcessLNode* llProcPop(ProcessLL* list);
void llProcPush(ProcessLL* list, ProcessLNode* node);
ProcessLNode* llProcPeek(ProcessLL* list);
Process* getProcByArrival(ProcessLL* list, int32_t arrivalTime);
int removeProc(ProcessLL* list, Process* proc);
//--------------------------------------------------------




//structs and functions for queue of processes
//--------------------------------------------------------
typedef struct procQueue {
    ProcessLNode *head;
    ProcessLNode *tail;
    int32_t size;
}ProcQueue;

ProcessLNode* procQueuePop(ProcQueue* queue);//TODO addProc
ProcessLNode* procQueuePush(ProcQueue* queue, Process* proc);//TODO addProc
ProcessLNode* procQueuePeek(ProcQueue* queue);//TODO addProc
//--------------------------------------------------------




//structs and functions for queue of waiting processes
//--------------------------------------------------------


typedef struct processLWaitNode{
    Process *proc;
    int32_t time_left;
    struct processLWaitNode *next;
    struct processLWaitNode *prev;

}ProcessLWaitNode;

typedef struct waitQueue {
    ProcessLWaitNode *head;
    ProcessLWaitNode *tail;
    int32_t size;
}ProcWaitQueue;

ProcWaitQueue *orderWait(ProcWaitQueue *queue);//TODO reorder wait queue by time left
ProcessLWaitNode* waitPop(ProcWaitQueue* queue);//TODO waitPop
ProcessLWaitNode* waitPush(ProcWaitQueue* queue, Process* proc);//TODO waitPush
ProcessLWaitNode* waitPeek(ProcWaitQueue* queue);//TODO waitPeek
int32_t timeLeft(ProcWaitQueue* queue);//TODO timeLeft
int32_t decrementTime(ProcWaitQueue* queue);//TODO decrementTime


void addLineToCSV(const char *fileName, const char *line);//TODO addLineToCSV



ProcessLNode *fileToLinked(const char *fileName, ProcessLL *list);//TODO fileToLinked


//--------------------------------------------------------
//Schedulers
//--------------------------------------------------------
void orderQueueSJF(ProcQueue *queue);//TODO orderQueueSJF
void ageQueue(ProcQueue *queue);//TODO ageQueue

void orderQueueRR(ProcQueue *queue);//TODO orderQueueRR
//--------------------------------------------------------


//--------------------------------------------------------
//Memory Management

typedef struct memoryBlock{
    bool free;
    int32_t size;
    int32_t id;

    struct memoryBlock *next;
    struct memoryBlock *prev;
}MemoryBlock;
typedef struct memory{
    MemoryBlock *head;
    MemoryBlock *tail;
    int8_t numBlocks;
    int32_t totalSize;
    int32_t freeSize;
}Memory;
char *transitionToString(int32_t transitionType, int32_t masterClock, Process *runingProc, Memory *mem);
bool memCheck(Memory *mem, int32_t size);//check there is enough memory space
bool addPartitionToMem(Memory *mem, int32_t size, int32_t id);//add a partition to the memory
int addProcToBlock(Memory *mem, Process *proc);//add a process to a memory block, bonus points because it rhymes?
int removeProcFromBlock(Memory *mem, Process *proc);//remove a process from a memory block
int getClosestPartition(Memory *mem, int32_t size);//get the closest partition to the size of the process
void setPartitionFree(Memory *mem, int32_t id);//set a partition to free
void setPartitionUsed(Memory *mem, int32_t id);//set a partition to used
int numPartitionsFree(Memory *mem);//get the number of partitions that are free
MemoryBlock *getBlockById(Memory *mem, int32_t id);//get a memory block by its id
#endif //OS_ASMT2_OSSIMLIB_H
