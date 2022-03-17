//TUBERIAS SIN NOMBRE
//VARGAS SANCHEZ ANDREA LILIANA

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
    int pid1;
    int pid2;
    int pipe1[2];
    int pipe2[2];
    int pipe3[2];
    int pipe4[2];
    
    char mensaje[MAX];
    int ban=1;


    if (pipe(pipe1)==-1){
        printf("Error en creacion tubería 1\n");
        exit(-1);
    }
    if(pipe(pipe2)==-1){
        printf("Error en creacion tubería 2\n");
        exit(-1);
    }
    if(pipe(pipe3)==-1){
        printf("Error en creacion tubería 2\n");
        exit(-1);
    }
    if(pipe(pipe4)==-1){
        printf("Error en creacion tubería 2\n");
        exit(-1);
    }

	//HIJO 1 A PAPÁ
    if((pid1=fork())==0){
    
        while(strcmp(mensaje,"fin")!=0){
            read(pipe1[0],mensaje,MAX);
            printf("Soy %i y recibí: %s \n", getpid(), mensaje);
            printf("Soy el proceso (hijo 1): %i \nEscribo:\n", getpid());
            scanf("%s", mensaje);
            write(pipe2[1], mensaje, strlen(mensaje)+1);
            printf("ENVIANDO A HIJO 2\n");
        }
        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);

        //HIJO 2 A PAPÁ
    } else if ((pid2=fork())==0){
    
     	while(strcmp(mensaje,"fin")!=0){
            read(pipe3[0],mensaje,MAX);
            printf("Soy %i y recibí: %s \n", getpid(), mensaje);
            printf("Soy el proceso (hijo 2): %i\nEscribo:\n", getpid());
            scanf("%s", mensaje);
            write(pipe4[1], mensaje, strlen(mensaje)+1);
            printf("ENVIANDO A HIJO 1\n");
        }
        close(pipe3[0]);
        close(pipe4[1]);
        exit(0);
        
    }else{
       
        while(strcmp(mensaje,"fin")!=0){    
        	if(ban==1){
        	  scanf("%s",mensaje);
        	}
        	
            printf("Soy el proceso (papá): %i \n",getpid());
            write(pipe1[1],mensaje,strlen(mensaje)+1);
            if(strcmp(mensaje,"fin")!=0){
                read(pipe2[0],mensaje, MAX);
                printf("Soy el proceso: %i y leí: %s\n",getpid(),mensaje);
                write(pipe3[1],mensaje,strlen(mensaje)+1);
            	if(strcmp(mensaje,"fin")!=0){
            	    read(pipe4[0],mensaje, MAX);
            	    ban=2;
            	}
            }
        }
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe3[1]);
        close(pipe4[0]);
        exit(0);
    }
    return(0);
}
