#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define VIRTUAL_MEMORY 1024
#define PRINCIPAL_MEMORY 64
#define PAGES 8
#define FRAMES 8


typedef struct{
    int data;
    bool isUsed;
} MemoryPosition;

typedef struct{
    int id;
    int intialPosition;
    int lastPosition;
    int dataAmount;
} Process;

MemoryPosition *virtualMemo;
MemoryPosition *principalMemo;
Process processes[10];
int lastPosition = 0;
int spaceFree = 1024;
int values[10] = {80, 44, 120, 200, 110, 22, 150, 98, 78, 122};

void saveProcess(Process process){
    printf("%d\n", process.id);
    for(int i = 0; i < process.dataAmount; i++){
        virtualMemo[lastPosition + i + 1].data = i*10;
        virtualMemo[lastPosition + i + 1].isUsed = true;
        printf("%d %d %d\n",lastPosition + i, virtualMemo[i].data, virtualMemo[i].isUsed);
    }
    lastPosition += process.dataAmount;
    spaceFree -= process.dataAmount; 
}

Process newProcess(int id, int dataAmount){
    Process process;
    process.id = id;
    process.intialPosition = lastPosition;
    process.lastPosition = lastPosition + dataAmount;
    process.dataAmount = dataAmount;
    return process;
}

void populateProcess(){
    for(int i = 0; i < 10; i++){
        processes[i] = newProcess(i, values[i]);
        saveProcess(processes[i]);
    }
}

Process findProcess(int id){
}

int main(){
    int page;
    virtualMemo = (MemoryPosition *) malloc(sizeof(MemoryPosition) * (VIRTUAL_MEMORY / PAGES));
    principalMemo = (MemoryPosition *) malloc(sizeof(MemoryPosition) * (PRINCIPAL_MEMORY / FRAMES));

    populateProcess();



    free(virtualMemo);
    free(principalMemo);
    return 0;
}