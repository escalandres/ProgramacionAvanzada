/*tUBERIAS SIN NOMBRE. sE COMUNICAN DOS PROCESOS A TRAVES DE TUBERIAS SIN NOMBRE*/
/*Alumno: Andres Rafael Escala Acosta*/
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAX 256

void main(){
    int inicio=0;
    int pid,pid2;
    int pipe1[2]; // 1 Escribir
    int pipe2[2]; // 1 Leer
    int pipe3[2]; // 2 Escribir
    int pipe4[2]; // 2 Leer
    char mensaje[MAX];

    if(pipe(pipe1)==-1){
        printf("error en creacion tuberia 1\n");
        exit(-1);
    }
    if(pipe(pipe2)==-1){
        printf("error en creacion tuberia 2\n");
        exit(-1);
    }
    if(pipe(pipe3)==-1){
        printf("error en creacion tuberia 3\n");
        exit(-1);
    }
    if(pipe(pipe4)==-1){
        printf("error en creacion tuberia 4\n");
        exit(-1);
    }

    if((pid=fork())==0){ //Codigo hijo 1
        while(strcmp(mensaje,"fin")!=0){
            read(pipe2[0],mensaje,MAX);
            if(mensaje==""){
                printf("\nSoy hijo[1]: %i y no he recibido nada del hijo 2\n", getpid());
            }
            else{
                printf("\nSoy hijo[1]: %i y recibi: %s\n", getpid(),mensaje);
            }
            printf("\n[1] Ingresa tu mensaje\nMensaje: ");
            scanf("%s",mensaje);
            write(pipe1[1],mensaje,strlen(mensaje)+1);
        }
        close(pipe1[1]);
        close(pipe2[0]);
    }
    if((pid2=fork())==0){ //Codigo hijo 2
        while(strcmp(mensaje,"fin")!=0){
            read(pipe4[0],mensaje,MAX);
            if(mensaje==""){
                printf("\nSoy hijo[2]: %i y no he recibido nada del hijo 2\n", getpid());
            }
            else{
                printf("\nSoy hijo[2]: %i y recibi: %s\n", getpid(),mensaje);
            }
            printf("\n[2] Ingresa tu mensaje\nMensaje: ");
            scanf("%s",mensaje);
            write(pipe3[1],mensaje,strlen(mensaje)+1);
        }
        close(pipe3[1]);
        close(pipe4[0]);
    }
    else{
        while(strcmp(mensaje,"fin")!=0){
            printf("\nIniciando...\n");
            if(inicio==0){
                printf("\nMensaje: ");
                scanf("%s",mensaje);
                inicio++;
            }
            // printf("\nSoy el proceso Father: %i y escribi: %s\n",getpid(),mensaje);
            write(pipe2[1],mensaje,strlen(mensaje)+1);
            if(strcmp(mensaje,"fin")!=0){
                read(pipe1[0],mensaje,MAX);
                if(mensaje==""){
                    printf("\nEl hijo 1 no ha enviado ningun mensaje!\n");
                }
                else{
                    printf("\nEl hijo 1 envio un mensaje!\n");
                    write(pipe4[1],mensaje,strlen(mensaje)+1);
                }
                read(pipe3[0],mensaje,MAX);
                if(mensaje==""){
                    printf("\nEl hijo 2 no ha enviado ningun mensaje!\n");
                }
                else{
                    printf("\nEl hijo 2 envio un mensaje!\n");
                    write(pipe2[1],mensaje,strlen(mensaje)+1);
                }
            }
        }
        
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe3[1]);
        close(pipe4[0]);
        exit(0);
    }
}