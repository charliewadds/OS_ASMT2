//
// Created by Charlie Wadds on 2023-11-08.
//this file contains all the functions for the ProcLL data type
//this is a linked list of processes
//
#include "../../include/osSimLib.h"


//this function creates a new ProcLL
ProcessLL* createProcLL(void) {
    ProcessLL *newProcLL = malloc(sizeof(ProcessLL));
    newProcLL->head = NULL;
    newProcLL->tail = NULL;
    newProcLL->size = 0;
    return newProcLL;
}

//this function adds a process to the end of the ProcLL
//TODO test this, double check that it should return a ProcLL* not a ProcessLNode*
ProcessLL* llAddProc(ProcessLL* list, Process proc) {
    ProcessLNode *newProc = malloc(sizeof(ProcessLNode));
    Process *newBaseProc = malloc(sizeof(Process));
    newBaseProc->pid = proc.pid;
    newBaseProc->arriv_time = proc.arriv_time;
    newBaseProc->total_time = proc.total_time;
    newBaseProc->io_freq = proc.io_freq;
    newBaseProc->io_duration = proc.io_duration;
    newBaseProc->priority = proc.priority;
    newBaseProc->memReq = proc.memReq;
    newBaseProc->memPart = -1;

    newProc->proc = newBaseProc;

    newProc->proc = newBaseProc;
    newProc->next = NULL;
    newProc->prev = NULL;

    if (list->head == NULL) {
        // If the list is empty, the new process becomes both the head and the tail
        list->head = newProc;
        list->tail = newProc;
        list->size++;
        return list;
    }

    newProc->next = list->head;  // Connect the new process to the current head
    list->head->prev = newProc;  // Set the current head's previous to the new process
    list->head = newProc;        // Update the head to be the new process

    list->size++;
    return list;

}

//this function removes a process from the front of the ProcLL
//TODO test this
ProcessLNode* llProcPop(ProcessLL* list) {
    if (list->head == NULL) {
        return NULL;
    }

    ProcessLNode *temp = list->head;
    list->head = list->head->next;
    list->size--;
    return temp;
}


//TODO test this
void llProcPush(ProcessLL* list, ProcessLNode* node) {
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
        list->size++;
        return;
    }

    list->tail->next = node;
    node->prev = list->tail;
    list->tail = node;
    list->size++;

}

//TODO test this
ProcessLNode* llProcPeek(ProcessLL* list) {
    return list->head;
}

Process *getProcByArrival(ProcessLL* list, int32_t arrivalTime) {
    ProcessLNode *temp = list->head;
    while (temp != NULL) {
        if (temp->proc->arriv_time == arrivalTime) {
            return temp->proc;
        }
        temp = temp->next;
    }
    return NULL;
}


int removeProc(ProcessLL* list, Process* proc) {
    ProcessLNode *temp = list->head;
    while (temp != NULL) {
        if (temp->proc->pid == proc->pid) {
            if(list->size == 1){
                list->head = NULL;
                list->tail = NULL;
                list->size--;
                return 0;
            }
            if (temp->prev == NULL) {
                list->head = temp->next;
                list->head->prev = NULL;
                list->size--;
                return 0;
            } else if (temp->next == NULL) {
                list->tail = temp->prev;
                list->tail->next = NULL;
                list->size--;
                return 0;
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                list->size--;
                return 0;
            }

        }
        temp = temp->next;
    }
    return -1;
}












