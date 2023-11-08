#ifndef OS_ASMT2_OSSIMLIB_H
#define OS_ASMT2_OSSIMLIB_H

#include <stdint.h>
#include <stdlib.h>



//structs and functions for process datatypes
//-----------------------------------------------------
typedef struct process{
    int32_t pid;
    int32_t arriv_time;
    int32_t total_time;
    int32_t io_freq;
    int32_t io_duration;
}Process;

typedef struct processLNode {//linked node containing a process
    struct process proc;
    struct node *next;
    struct node *prev;
}ProcessLNode;
//-------------------------------------------------------0




//structs and functions for linked list of processes
//--------------------------------------------------------
typedef struct processLL {
    struct processLNode *head;
    struct processLNode *tail;
    int32_t size;
}ProcessLL;

ProcessLL* createProcLL(void);
ProcessLL* llAddProc(ProcessLL* list, Process* proc);//TODO addProc
ProcessLNode* llProcPop(ProcessLL* list);//TODO addProc
void llProcPush(ProcessLL* list, ProcessLNode* node);//TODO addProc
ProcessLNode* llProcPeek(ProcessLL* list);//TODO addProc

//--------------------------------------------------------




//structs and functions for queue of processes
//--------------------------------------------------------
typedef struct procStack {
    struct ProcessLNode *head;
    struct ProcessLNode *tail;
    int32_t size;
}ProcStack;

ProcessLNode* stackProcPop(ProcStack* stack);//TODO addProc
ProcessLNode* stackProcPush(ProcStack* stack, Process* proc);//TODO addProc
ProcessLNode* stackProcPeek(ProcStack* stack);//TODO addProc
//--------------------------------------------------------




//structs and functions for queue of waiting processes
//--------------------------------------------------------

typedef struct processLWaitNode{
    struct process proc;
    struct processLWaitNode *next;
    struct processLWaitNode *prev;
    int32_t timeLeft;
}processLWaitNode;

typedef struct waitQueue {
    struct ProcessLNode *head;
    struct ProcessLNode *tail;
    int32_t size;
}ProcWaitQueue;
ProcWaitQueue *orderWait(ProcWaitQueue *queue);//TODO reorder wait queue by time left
ProcessLNode* waitPop(ProcWaitQueue* queue);//TODO waitPop
ProcessLNode* waitPush(ProcWaitQueue* queue, Process* proc);//TODO waitPush
ProcessLNode* waitPeek(ProcWaitQueue* queue);//TODO waitPeek
int32_t timeLeft(ProcWaitQueue* queue);//TODO timeLeft
int32_t decrementTime(ProcWaitQueue* queue);//TODO decrementTime





#endif //OS_ASMT2_OSSIMLIB_H
