#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <unistd.h>
#include<wait.h>

#define MAX 256

int main(){
    int pid;
    int pipe1[2];
    int pipe2[2];
    char mensaje[MAX];

    if (pipe(pipe1)==-1){
        printf("Error en creacion tubería 1\n");
        exit(-1);
    }
    if(pipe(pipe2)==-1){
        printf("Error en creacion tubería 2\n");
        exit(-1);
    }

    if((pid=fork())==0){
        while(strcmp(mensaje,"fin")!=0){
            read(pipe1[0],mensaje,MAX);
            printf("Soy %i y recibí: %s \n", getpid(), mensaje);
            printf("Soy el proceso: %i y escribo\n", getpid());
            scanf("%s", mensaje);
            write(pipe2[1], mensaje, strlen(mensaje)+1);
        }
        close(pipe1[0]);
        close(pipe1[1]);
        exit(0);
    } else{
        while(strcmp(mensaje,"fin")!=0){
            scanf("%s",mensaje);
            printf("soy el proceso: %i y escribi\n",getpid());
            write(pipe1[1],mensaje,strlen(mensaje)+1);
            if(strcmp(mensaje,"fin")!=0){
                read(pipe2[0],mensaje, MAX);
                printf("Soy el proceso: %i y leí: %s\n",getpid(),mensaje);
            }
        }
        close(pipe1[1]);
        close(pipe2[0]);
        exit(0);
    }
    return(0);
}
