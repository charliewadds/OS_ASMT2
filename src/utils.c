//
// Created by Charlie Wadds on 2023-11-08.
// this file includes all the utility functions for the osSimLib like loading files etc.
//


#include "../include/osSimLib.h"



int strLen(const char str[]){
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}


void strAppend(char str[], char toAppend[]){
    int i = strLen(str);
    int j = 0;
    while(toAppend[j] != '\0'){
        str[i] = toAppend[j];
        i++;
        j++;
    }
    str[i] = '\0';
}

//add values from a file to an existing linked list
ProcessLNode *fileToLinked(const char filename[], ProcessLL* LList){


    printf("filename: %s\n", filename);
    //ProcessLL* list = LList;
    FILE *file;

    file = fopen(filename, "r");


    if (file == NULL) {
        printf("Error: %d (%s)\n", errno, strerror(errno));
        //perror("Error opening file, check spelling and location");
        exit(1);
    }

    char line[255];
    fgets(line, sizeof(line), file);
    while (fgets(line, sizeof(line), file) != NULL) {

        Process proc;
        uint8_t indexList[7];
        uint8_t indexListLen = 0;
        //this could be done in one loop
        for(int i=0; i< sizeof(line)/sizeof(line[0]); i++){
            if(line[i] == csvBreakChar){

                indexList[indexListLen] = i;
                indexListLen++;
            }

            if((line[i] == '\r' || line[i] == '\n') && i >1){
                indexList[indexListLen] = i-1;
            }

        }
        char pid[10] = "";
        char arriv_time[10]= "";
        char total_time[10]= "";
        char io_freq[10]= "";
        char io_duration[10]= "";
        char priority[10] = "";
        char memReq[10] = "";

        for(int i = 0; i<sizeof(line)/sizeof(line[0]); i++){

            if(line[i] == '\r' || line[i] == '\n'){
                break;
            }
            if(i<indexList[0]){
                pid[strLen(pid)] = line[i];
            }
            else if(i<=indexList[1]){
                if(line[i] != ','){
                    arriv_time[strLen(arriv_time)]  = line[i];
                }

            }
            else if(i<=indexList[2]){
                total_time[strLen(total_time)] = line[i];
            }
            else if(i<=indexList[3]){
                io_freq[strLen(io_freq)] = line[i];
            }
            else if(i<=indexList[4]){
                io_duration[strLen(io_duration)] = line[i];
                if(scheduerAlgorithm != 1 && !useMemory){
                    break;
                }
            }else if(i<=indexList[5]){
                if(scheduerAlgorithm) {
                    priority[strLen(priority)] = line[i];
                }
            }else if(i<=indexList[6]){
                if(useMemory) {
                    memReq[strLen(memReq)] = line[i];
                }
            }

            else{
                break;
            }



        }
        proc.pid = (int32_t) atoi(pid);
        proc.arriv_time = atoi(arriv_time);
        proc.total_time = atoi(total_time);
        proc.io_freq = atoi(io_freq);
        proc.io_duration = atoi(io_duration);
        proc.priority = atof(priority);
        proc.memReq = atoi(memReq);


        llAddProc(LList, proc);

        printf("\n%d\n", proc.pid);

    }

    // Close the file when done
    fclose(file);


    return LList->head;
}
void addLineToCSV(const char *filename, const char *line) {
    FILE *file = fopen(filename, "a"); // Open the file in append mode

    if (file == NULL) {
        perror("Error opening the file");
        return;
    }

    // Check if the line contains a comma; if so, enclose it in double quotes

    fprintf(file, "%s\n", line); // Append the line to the CSV file as is


    fclose(file); // Close the file
}


char *transitionToString(int32_t transitionType, int32_t masterClock, Process* runningProc, Memory* mem){
    /*
     * - 0 is new to ready
     * - 1 is ready to running
     * - 2 is running to waiting
     * - 3 is waiting to ready
     * - 4 is running to ready
     * - 5 is running to terminated
     */
    char *formattedLine = malloc(sizeof(char)*255);
    printf("TRANSITION\n------------------------------------\n");
    sprintf(formattedLine, "time of transition: %d\tpid: %d\t", masterClock, runningProc->pid);
    switch(transitionType){
        case 0:

            strAppend(formattedLine, "old state: New\t");
            strAppend(formattedLine, "new state: Ready\t");
            break;
        case 1:
            strAppend(formattedLine, "old state: Ready\t");
            strAppend(formattedLine,"new state: Running\t");
            if(useMemory) {
                sprintf(formattedLine, "total memory used: %d\ttotal memory free: %d\ttotal free partitions: %d\t", mem->freeSize, mem->freeSize,numPartitionsFree(mem));

            }


            break;
        case 2:
            strAppend(formattedLine, "old state: Running\t");
            strAppend(formattedLine, "new state: Waiting\t");


            break;
        case 3:
            strAppend(formattedLine, "old state: Waiting\t");
            strAppend(formattedLine, "new state: Ready\t");

            break;
        case 4:
            strAppend(formattedLine, "old state: Running\t");
            strAppend(formattedLine, "new state: Ready\t");

            break;
        case 5:
            strAppend(formattedLine, "old state: Running\t");
            strAppend(formattedLine, "new state: Terminated\t");
            if(useMemory) {
                sprintf(formattedLine, "total memory used: %d\ttotal memory free: %d\ttotal free partitions: %d\t", mem->freeSize, mem->freeSize,numPartitionsFree(mem));

            }
            break;
        default:
            strAppend(formattedLine, "Error: invalid trantion type\t");

            break;
    }
    printf("%s\n", formattedLine);
    printf("------------------------------------\n\n\n");

    return formattedLine;

}