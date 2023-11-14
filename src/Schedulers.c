//
// Created by Charlie Wadds on 2023-11-13.
//

#include "../include/osSimLib.h"

void orderQueueSJF(ProcQueue *queue) {
    //order the queue so that the highest priority is at the head using bubble sort

    if (queue->size <= 1) {
        return;
    }
    while(1) {
        int swapped = 0;
        ProcessLNode *temp = queue->tail;

        while (temp != NULL && temp->next != NULL) {
            if (temp->proc->priority > temp->next->proc->priority) {
                // Swap temp and temp->next
                ProcessLNode *tempNext = temp->next;
                ProcessLNode *tempPrev = temp->prev;
                ProcessLNode *tempNextNext = tempNext->next;

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
                swapped = 1;
            } else {
                temp = temp->next;
            }
        }
        if(swapped == 0){
            break;
        }
    }


}

void ageQueue(ProcQueue *queue) {
    //age the queue by the aging increment
    ProcessLNode *temp = queue->tail;
    while (temp != NULL) {
        temp->proc->priority += ageIncrement;
        temp = temp->next;
    }
}

//------------------------------------------------------------



