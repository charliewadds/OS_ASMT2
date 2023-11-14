//
// Created by Charlie Wadds on 2023-11-08.
//
#include <stdio.h>
#include "../include/osSimLib.h"






void asmt1(const char inFile[50], const char outFile[50]){
    //clear outfile
    FILE *file = fopen(outFile, "w"); // Open the file in append mode

    if (file == NULL) {
        perror("Error opening the file");
        return;
    }
    fprintf(file, "");//clear the file

    int32_t masterClock = 0;

    ProcessLL* newList = malloc(sizeof(ProcessLL));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    fileToLinked(inFile, newList);

    Memory *mem = malloc(sizeof(Memory));
    addPartitionToMem(mem,500, 0);
    addPartitionToMem(mem,250, 1);
    addPartitionToMem(mem,150, 2);
    addPartitionToMem(mem,100, 3);


    ProcQueue *readyQueue = malloc(sizeof(ProcQueue));
    readyQueue->head = NULL;
    readyQueue->tail = NULL;
    readyQueue->size = 0;

    ProcWaitQueue *waitingQueue = malloc(sizeof(ProcWaitQueue));
    waitingQueue->head = NULL;
    waitingQueue->tail = NULL;
    waitingQueue->size = 0;

    Process *runningProc = NULL;//currently running process


    int runningTimer = RRTimeout;
    int numProcs = newList->size;
    ProcessLL *terminated = malloc(sizeof(ProcessLL));
    addLineToCSV(outFile, "time of transition, pid, old state, new State,mem");

    int total_turnaround = 0;
    int total_time_in_wait = 0;
    while(terminated->size < numProcs) {//todo this should be logic

        total_time_in_wait += waitingQueue->size;
        //apply the scheduler to the ready queue every clock cycle
        if(scheduerAlgorithm == 1)
            orderQueueSJF(readyQueue);


        if(runningProc != NULL){
            runningProc->total_time--;
            runningTimer--;
        }
        while(getProcByArrival(newList, masterClock) != NULL){//while there are still processes to be added to the ready queue


            //remove process from new list and add it to the ready queue
            Process *newProc = getProcByArrival(newList, masterClock);
            removeProc(newList, newProc);
            procQueuePush(readyQueue, newProc);

            //add transition to csv and print
            addLineToCSV(outFile, transitionToString(0, masterClock, newProc,mem));


        }


        if(runningProc != NULL && runningProc->total_time <= 0){//if the currently running process is done
            //add transition to csv and print
            addLineToCSV(outFile, transitionToString(5, masterClock, runningProc,mem));

            //add process to terminated list
            llAddProc(terminated, *runningProc);

            if(useMemory){
                setPartitionFree(mem, runningProc->memPart);
            }
            printf("turnaround time for pid #%d: %d\n", runningProc->pid, masterClock - runningProc->arriv_time);
            total_turnaround += masterClock - runningProc->arriv_time;
            runningProc = NULL;


        }

        //if there is a process running and it is time for an io event to occur move it to the waiting queue OR it is a RR scheduler and the process is out of time
        if(runningProc != NULL && (runningProc->total_time -1 != 0 && ((runningProc->total_time - 1) % runningProc->io_freq == 0) || (runningTimer <= 0 && scheduerAlgorithm == 2))){


            if(runningTimer <= 0){
                runningTimer = 0;
            }
            addLineToCSV(outFile, transitionToString(2, masterClock, runningProc,mem));
            waitPush(waitingQueue, runningProc);
            runningProc = NULL;
        }

        //if the process is done waiting and there is a process in the waiting queue, add it to the ready queue and remove it from the waiting queue
        while( waitingQueue->size > 0 && timeLeft(waitingQueue) <= 0 && waitPeek(waitingQueue) != NULL){

            procQueuePush(readyQueue, waitPeek(waitingQueue)->proc);//add the waiting proc to the ready queue
            waitPop(waitingQueue);//remove the waiting proc from the waiting queue

            addLineToCSV(outFile, transitionToString(3, masterClock, readyQueue->tail->proc,mem));


        }

        if(waitingQueue->size > 0){
            decrementTime(waitingQueue);
        }


        if(readyQueue->head != NULL && runningProc == NULL){//if there is a process in the ready queue and no running processes

            if(useMemory && memCheck(mem, procQueuePeek(readyQueue)->proc->memReq) || procQueuePeek(readyQueue)->proc->memPart != 0) {

                readyQueue->head->proc->memPart = getClosestPartition(mem, procQueuePeek(readyQueue)->proc->memReq);
                setPartitionUsed(mem, procQueuePeek(readyQueue)->proc->memPart);
                runningProc = procQueuePop(readyQueue)->proc;
                addLineToCSV(outFile, transitionToString(1, masterClock, runningProc,mem));
            }else if(!useMemory){
                runningProc = procQueuePop(readyQueue)->proc;
                addLineToCSV(outFile, transitionToString(1, masterClock, runningProc,mem));
            }
        }

        ageQueue(readyQueue);
        masterClock ++;
    }
    printf("Average turnaround time: %d\n", total_turnaround/numProcs);
    printf("Average time in wait: %d\n", total_time_in_wait/numProcs);

    //free all malloc
    free(newList);
    free(readyQueue);
    free(waitingQueue);
    free(terminated);
    fclose(file);


}

int main(int argc, char* argv[]) {
    // Check if two command line arguments (file paths) are provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <inputFilePath> <outputFilePath>\n", argv[0]);
        return 1;  // Return non-zero to indicate an error
    }

    // Extract file paths from command line arguments
    const char* inputFilePath = argv[1];
    const char* outputFilePath = argv[2];

    // Call asmt1 function with the provided file paths
    asmt1(inputFilePath, outputFilePath);

    return 0;
}