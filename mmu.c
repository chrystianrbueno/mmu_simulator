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

Process newProcess(int id, int dataAmount);
Process findProcessById(int id);
void populateVirtualMemory();
void menu();
void saveProcess(Process process);
void mapVirtualToPrincipal(int id);
void showProcess();
void verifyPrincipalMemoryUsed(int id);
void listProcesses();
void mapAllProcessToPrincipal();
int verifyNumberOfPages(int dataAmount);
int verifyNextEmpty();

Page *virtualMemo;
Frame *principalMemo;
Process processes[10];
int lastPosition = 0;
int values[NUMBER_PROCESSES] = {80, 44, 120, 200, 110, 22, 150, 98, 78};

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

void saveProcess(Process process){
    for(int i = 0; i < process.numPages; i++){
        virtualMemo[lastPosition + i].data = 10;
        virtualMemo[lastPosition + i].posPage = lastPosition + i;
    }
    lastPosition += process.numPages;
}

void populateVirtualMemory(){
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

int verifyNumberOfPages(int dataAmount){
    if(dataAmount % PAGES == 0){
        return dataAmount / PAGES;
    }

    return (dataAmount / PAGES) + 1;
}


void verifyPrincipalMemoryUsed(int id){
    if(principalMemo[id].isUsed){
        printf("Processo %d utilizando o frame %d\n", principalMemo[id].nameProcess, id);
    }
}

int verifyNextEmpty(){
    int result = -1;
    for (int i= 0 ; i < (PRINCIPAL_MEMORY / FRAMES); i ++){
        if(!(principalMemo[i].isUsed)){
            return i;
        }
    }
    return result;
}

void listProcesses(){
    printf("\n\n\n\n\n");
    printf("Lista de Processos");
    printf("\n\n");

    for(int i = 0; i < NUMBER_PROCESSES; i++){
        printf("Processo %d\n", processes[i].id);
    }
    printf("\n\n\n\n\n");
}

void mapVirtualToPrincipal(int id){
    Process process = findProcessById(id);
    if(process.found){
        int count = 0;

        printf("Processo %d encontrado\n", process.id);
        int emptyValue = verifyNextEmpty();
        if(emptyValue == - 1){
            emptyValue = 0;
        }

        while(process.intialPosition + count < process.lastPosition){
            for(int i = emptyValue; process.intialPosition + count < process.lastPosition; i++){
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

    }else{
        printf("Processo %d nao encontrado\n", process.id);
    }
}


void showProcess(int id){
    Process process = findProcessById(id);
    if(process.found){
        printf("\n");
        printf("Processo %d\n", process.id);
        printf("Encontra-se na memoria virtual na posicao: %d\n", process.intialPosition);
        printf("Esta utilizando %d Pages\n", process.numPages);
    }else{
        printf("\n");
        printf("Processo nao encontrado\n");
    }
}


void mapAllProcessToPrincipal(){
    for(int i = 0; i < NUMBER_PROCESSES; i++){
        mapVirtualToPrincipal(i);
        printf("\n\n\n\nPausado para visualizacao\n\n");
        getchar();    
        scanf("c\n");
        system("clear");
    }
}

void menu(){
    int op;
    int id;
    do{
        printf("\n#######################\n");
        printf("\tMenu\n");
        printf("\n");
        printf("1- Detalhar Processo\n");
        printf("2- Consumir Processo\n");
        printf("3- Consumir Todos Processo\n");
        printf("0 - Sair\n");
        printf("\n\n\n\n\n");
        printf("Digite a opcao:  ");
        scanf("%d",&op);

        system("clear");
        switch(op){
            case 0:
                    break;
            case 1:
                    listProcesses();
                    printf("Detalhar Processo: ");
                    scanf("%d",&id);
                    showProcess(id);
                    break;
            case 2:
                    listProcesses();
                    printf("Consumir Processo: ");
                    scanf("%d",&id);
                    mapVirtualToPrincipal(id);
                    break;
            case 3:
                    printf("Consumindo todos Processos: ");
                    mapAllProcessToPrincipal();
                    break;
            default:
                    printf("Opcao invalida\n");
        }

    }while(op != 0);
}

int main(){
    virtualMemo = (Page *) malloc(sizeof(Page) * (VIRTUAL_MEMORY / PAGES));
    principalMemo = (Frame *) malloc(sizeof(Frame) * (PRINCIPAL_MEMORY / FRAMES));

    populateVirtualMemory();
    menu();

    free(virtualMemo);
    free(principalMemo);
    return 0;
}