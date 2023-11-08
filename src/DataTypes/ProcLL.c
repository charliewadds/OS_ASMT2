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
ProcessLL* llAddProc(ProcessLL* list, Process* proc) {
    ProcessLNode *newProc = malloc(sizeof(ProcessLNode));
    newProc->proc = *proc;
    newProc->next = NULL;
    newProc->prev = NULL;

    if (list->head == NULL) {
        list->head = newProc;
        list->tail = newProc;
        list->size++;
        return list;
    }

    list->tail->next = newProc;
    newProc->prev = list->tail;
    list->tail = newProc;
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