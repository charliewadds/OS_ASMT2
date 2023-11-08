//
// Created by Charlie Wadds on 2023-11-08.
//
#include <stdio.h>
#include "../include/osSimLib.h"


int testProcLL(){
    ProcessLL *list = createProcLL();
    Process *proc = malloc(sizeof(Process));
    proc->pid = 1;
    proc->arriv_time = 0;
    proc->total_time = 0;
    proc->io_freq = 0;
    proc->io_duration = 0;

    ProcessLNode *node = malloc(sizeof(ProcessLNode));
    node->proc = proc;
    node->next = NULL;
    node->prev = NULL;

    llProcPush(list, node);

    if(list->head->proc->pid != 1){
        return 1;
    }

    if(list->size != 1){
        return 1;
    }

    ProcessLNode *temp = llProcPop(list);

    if (temp->proc->pid != 1) {
        return 1;
    }
    return 0;
}


int main(void) {

    int test1 = testProcLL();
    printf("procLL fail: %d", test1);


    return 0;
}