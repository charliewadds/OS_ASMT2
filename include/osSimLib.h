#ifndef OS_ASMT2_OSSIMLIB_H
#define OS_ASMT2_OSSIMLIB_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

//constants
//-----------------------------------------------------
#define csvBreakChar ','

//-----------------------------------------------------

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
ProcessLL* llAddProc(ProcessLL* list, Process* proc);
ProcessLNode* llProcPop(ProcessLL* list);
void llProcPush(ProcessLL* list, ProcessLNode* node);
ProcessLNode* llProcPeek(ProcessLL* list);

//--------------------------------------------------------




//structs and functions for queue of processes
//--------------------------------------------------------
typedef struct procQueue {
    ProcessLNode *head;
    ProcessLNode *tail;
    int32_t size;
}ProcQueue;

ProcessLNode* stackProcPop(ProcQueue* stack);//TODO addProc
ProcessLNode* stackProcPush(ProcQueue* stack, Process* proc);//TODO addProc
ProcessLNode* stackProcPeek(ProcQueue* stack);//TODO addProc
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





#endif //OS_ASMT2_OSSIMLIB_H
