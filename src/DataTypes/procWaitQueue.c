//
// Created by Charlie Wadds on 2023-10-13.
//


#include "../../include/osSimLib.h"

ProcWaitQueue *orderWait(ProcWaitQueue *queue) {
    // Order the queue by time left from most to least
    if (queue->size <= 1) {
        return queue;
    }

    ProcessLWaitNode *temp = queue->tail;

    while (temp != NULL && temp->next != NULL) {
        if (temp->time_left < temp->next->time_left) {
            // Swap temp and temp->next
            ProcessLWaitNode *tempNext = temp->next;
            ProcessLWaitNode *tempPrev = temp->prev;
            ProcessLWaitNode *tempNextNext = tempNext->next;

            temp->next = tempNextNext;
            temp->prev = tempNext;
            tempNext->next = temp;
            tempNext->prev = tempPrev;

            if (tempPrev != NULL) {
                tempPrev->next = tempNext;
            } else {
                queue->tail = tempNext;
            }

            if (tempNextNext != NULL) {
                tempNextNext->prev = temp;
            } else {
                queue->head = temp;
            }

            temp = tempPrev;
        } else {
            temp = temp->next;
        }
    }

    return queue;
}


ProcessLWaitNode *waitPush(ProcWaitQueue* queue, Process* proc){
    ProcessLWaitNode *newProc = malloc(sizeof(ProcessLWaitNode));
    newProc->proc = proc;
    newProc->next = NULL;
    newProc->prev = NULL;
    newProc->time_left = proc->io_duration;

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
    orderWait(queue);
    return (ProcessLWaitNode *) proc;
}

int32_t decrementTime(ProcWaitQueue* queue){
    //decrement all the times and return the time left for head
    if(queue->size == 0){
        return -1;
    }else if(queue->size == 1){
        queue->head->time_left--;
        return queue->head->time_left;
    }
    ProcessLWaitNode *temp = queue->tail;
    for(int i = 0; i < queue->size-1; i++){

        temp->time_left--;
        temp = temp->next;
    }
    queue->head->time_left--;
    return queue->head->time_left;
}

ProcessLWaitNode* waitPop(ProcWaitQueue* queue){

    if(queue->size == 0){
        return NULL;
    }
    else if(queue->size == 1){
        ProcessLWaitNode *temp = queue->head;
        queue->head = NULL;
        queue->tail = NULL;
        queue->size--;
        return temp;
    }
    else{
        ProcessLWaitNode *temp = queue->head;
        queue->head = queue->head->prev;
        queue->head->next = NULL;
        queue->size--;
        return temp;
    }
}

ProcessLWaitNode *waitPeek(ProcWaitQueue* queue){
    if(queue->size == 0){
        return NULL;
    }
    else{
        return queue->head;
    }
}

int32_t timeLeft(ProcWaitQueue* queue){
    if(queue->size == 0){
        return -1;
    }
    else{
        return queue->head->time_left;
    }
}

void printWait(ProcWaitQueue queue){
    printf("\n\nPrinting Wait Queue\n");
    ProcessLWaitNode *temp = queue.tail;
    while(temp != queue.head){
        printf("pid: %d\n", temp->proc->pid);
        printf("time left: %d\n", temp->time_left);
        temp = temp->next;
    }
    printf("pid: %d\n", temp->proc->pid);
    printf("time left: %d\n", temp->time_left);
    printf("End of Wait Queue\n\n\n");

}