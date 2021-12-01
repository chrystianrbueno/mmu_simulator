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
    int posPage;
} Page;

typedef struct{
    bool isUsed;
    int posPage;
    int nameProcess;
} Frame;

typedef struct{
    int id;
    int intialPosition;
    int lastPosition;
    int numPages;
    int dataAmount;
    bool found;
} Process;

void saveProcess(Process process);
int verifyNumberOfPages(int dataAmount);
Process newProcess(int id, int dataAmount);
void populateProcess();
Process findProcessById(int id);
Process findProcessById(int id);
void verifyPrincipalMemoryUsed(int id);
void mapVirtualToPrincipal(int id);
void menu();
void showProcess();

Page *virtualMemo;
Frame *principalMemo;
Process processes[10];
int lastPosition = 0;
int values[NUMBER_PROCESSES] = {80, 44, 120, 200, 110, 22, 150, 98, 78};

void saveProcess(Process process){
    for(int i = 0; i < process.numPages; i++){
        virtualMemo[lastPosition + i].data = 10;
        virtualMemo[lastPosition + i].posPage = lastPosition + i;
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
    process.lastPosition = process.intialPosition + process.numPages; 
    process.dataAmount = dataAmount;
    process.found = false;
    return process;
}

void populateProcess(){
    for(int i = 0; i < NUMBER_PROCESSES; i++){
        processes[i] = newProcess(i, values[i]);
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

void verifyPrincipalMemoryUsed(int id){
    if(principalMemo[id].isUsed){
        printf("Processo %d utilizando o frame %d\n", principalMemo[id].nameProcess, id);
    }
}

void mapVirtualToPrincipal(int id){
    Process process = findProcessById(id);
    if(process.found){
        int count = 0;

        printf("Processo %d encontrado\n", process.id);
        while(process.intialPosition + count < process.lastPosition){
            for(int i = 0; process.intialPosition + count < process.lastPosition; i++){
                if(i < (PRINCIPAL_MEMORY / FRAMES)){
                    verifyPrincipalMemoryUsed(i);
                    principalMemo[i].posPage = virtualMemo[process.intialPosition + count].posPage;
                    principalMemo[i].isUsed = true;
                    principalMemo[i].nameProcess = process.id;
                    printf("Memoria principal frame %d acessado pelo Processo %d de page %d\n", i, process.id, principalMemo[i].posPage);
                }else{
                    break;
                }
                count ++;
            }
        }

        process.found = false;
    }else{
        printf("Processo %d nao encontrado\n", process.id);
    }
}


void showProcess(int id){
    Process process = findProcessById(id);
    if(process.found){
        printf("Processo %d\n", process.id);
        printf("Encontra-se na memoria virtual na posicao: %d\n", process.intialPosition);
        printf("Esta utilizando %d Pages\n", process.numPages);
        printf("Conteúdo %d\n", virtualMemo[id].data);
    }else{
        printf("Processo nao encontrado\n");
    }
}

void menu(){
    int op;
    int id;
    do{
        //system("clear");
        printf("#####Menu#####\n");
        printf("1- Detalhar Processo\n");
        printf("2- Consumir Processo\n");
        printf("0 - Sair\n");
        printf("\n\n\n\n\n");
        printf("Digite a opcao:  ");
        scanf("%d",&op);
        switch(op){
            case 0:
                    break;
            case 1: 
                    printf("Detalhar - Selecione o nome do Processo: ");
                    scanf("%d",&id);
                    showProcess(id);
                    break;
            case 2:
                    printf("Consumir - Selecione o nome do Processo: ");
                    scanf("%d",&id);
                    mapVirtualToPrincipal(id);
                    break;
            default:
                    printf("Opcao invalida\n");
        }

    }while(op != 0);
}

int main(){
    virtualMemo = (Page *) malloc(sizeof(Page) * (VIRTUAL_MEMORY / PAGES));
    principalMemo = (Frame *) malloc(sizeof(Frame) * (PRINCIPAL_MEMORY / FRAMES));

    populateProcess();
    menu();

    free(virtualMemo);
    free(principalMemo);
    return 0;
}