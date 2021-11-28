#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define VIRTUAL_MEMORY 1024
#define PRINCIPAL_MEMORY 64
#define PAGES 8
#define FRAMES 8
#define NUMBER_PROCESSES 9


typedef struct{
    int data;
} Page;

typedef struct{
    bool isUsed;
    int idProcess;
    int posPage;
} Frame;

typedef struct{
    int id;
    int intialPosition;
    int numPages;
    int dataAmount;
    bool found;
} Process;

Page *virtualMemo;
Frame *principalMemo;
Process processes[10];
int lastPosition = 0;
int values[NUMBER_PROCESSES] = {80, 44, 120, 200, 110, 22, 150, 98, 78};

void saveProcess(Process process){
    for(int i = 0; i < process.numPages; i++){
        virtualMemo[lastPosition + i].data = 10;
        printf("%d %d \n",lastPosition + i, virtualMemo[i].data);
    }
    lastPosition += process.numPages;
}

int verifyNumberOfPages(int dataAmount){
    if(dataAmount % PAGES == 0){
        return dataAmount / PAGES;
    }

    return (dataAmount / PAGES) + 1;
}

Process newProcess(int id, int dataAmount){
    Process process;
    process.id = id;
    process.intialPosition = lastPosition;
    process.numPages = verifyNumberOfPages(dataAmount);
    process.dataAmount = dataAmount;
    process.found = false;
    return process;
}

void populateProcess(){
    for(int i = 0; i < NUMBER_PROCESSES; i++){
        processes[i] = newProcess(i, values[i]);
        printf("process = %d\n",processes[i].id);
        saveProcess(processes[i]);
    }
}

Process findProcessById(int id){
    for(int i = 0; i < NUMBER_PROCESSES; i++){
        if(processes[i].id == id){
            processes[id].found = true;
            return processes[id];
        }
    }
    return processes[id];
}

void mapVirtualToPrincipal(){
    Process process = findProcessById(5);
    if(process.found){
        printf("Processo encontrado %d\n", process.intialPosition);
        process.found = false;        
    }else{
        printf("Processo nao encontrado\n");
    }
}

int main(){
    virtualMemo = (Page *) malloc(sizeof(Page) * (VIRTUAL_MEMORY / PAGES));
    principalMemo = (Frame *) malloc(sizeof(Frame) * (PRINCIPAL_MEMORY / FRAMES));

    populateProcess();
    mapVirtualToPrincipal();

    free(virtualMemo);
    free(principalMemo);
    return 0;
}
