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

//add values from a file to an existing linked list
ProcessLL *fileToLinked(char filename[], ProcessLL* LList){

    printf("filename: %s\n", filename);
    ProcessLNode* head = LList->head;
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
        uint8_t indexList[5];
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

        for(int i = 0; i<sizeof(line)/sizeof(line[0]); i++){
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
        if(head == NULL){
            head = llAddProc(LList, &proc);
        }
        else{
            llAddProc(LList, &proc);
        }


    }

    // Close the file when done
    fclose(file);


    return head;
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