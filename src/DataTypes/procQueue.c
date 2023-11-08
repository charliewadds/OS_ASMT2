//
// Created by Charlie Wadds on 2023-10-10.
//


#include "../../include/osSimLib.h"

#include <stdlib.h>
#include <stdio.h>

//TODO test this
ProcessLNode *procPush(ProcQueue* queue, ProcessLNode * proc){

    ProcessLNode *newProc = malloc(sizeof(ProcessLNode));
    *newProc = *proc;
    newProc->next = NULL;
    newProc->prev = NULL;

    if(queue->head == NULL){
        queue->head = newProc;
        queue->tail = newProc;
        queue->size++;
    }
    else{

        queue->tail->prev = newProc;//set the head's prev to the new n
        newProc->next = queue->tail;
        queue->tail = newProc;
        queue->size++;
    }

    return proc;
}

ProcessLNode *procPop(ProcQueue* queue){

    //remove and return head
    if(queue->size == 0){
        printf("Queue is empty\n");
        return NULL;
    }
    else if(queue->size == 1){
        ProcessLNode *temp = queue->head;
        queue->head = NULL;
        queue->tail = NULL;
        queue->size--;
        return temp;
    }
    else{
        ProcessLNode *temp = queue->head;
        queue->head = queue->head->prev;
        queue->head->next = NULL;
        queue->size--;
        return temp;
    }
}

void printQueue(ProcQueue* queue){
    printf("Printing Queue\n");
    ProcessLNode *temp = queue->tail;
    while(temp != queue->head){
        printf("pid: %d\n", temp->proc->pid);
        temp = temp->next;
    }
}