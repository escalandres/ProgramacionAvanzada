//Alumna:Cisneros Martíneza Daphne Liliana
//Grupo: 2TV3

#include<unistd.h>
#include<sys/stat.h>
#include<signal.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

#define MAX 256

int main(){
	int pid;
	int opcion;
	int fifo1;
	int escribir;
	int leer;
	char pipe_nombre [MAX]="FIFO1";
	char mjHermano1 [MAX];
	char mjHermano2 [MAX];
	char mjHermano3 [MAX];
	char lecHermano1[MAX]="Hola hermano 1.";
	char lecHermano2[MAX]="Hola hermano 2.";
	char lecHermano3[MAX]="Hola hermano 3.";
	char leerFIFO[MAX];
	
	mknod(pipe_nombre, S_IFIFO | 0666, 0);
	printf("Oprima 1 si desea leer \nOprima 2 si desea escribir\n");
	scanf("%d",&opcion);
	
	if(opcion==1){
		printf("\nHas elegido leer\nDe quien te gustaria leer:\n 1.Hermano 1\n 2.Hermano 2\n 3.Hermano 3\n");
		scanf("%d",&leer);
		switch(leer){
			case 1:
			if((pid=fork())==0){
				printf("\n Has elegido hermano 1 de PID %i, vamos a ver si hay algun mensaje\n", getpid());
				
				fifo1=open(pipe_nombre, O_RDONLY);
				read(fifo1,leerFIFO,MAX);
				close (fifo1);
				if(leerFIFO!=lecHermano1){
					printf("El mensaje recibido es no era para ti.\n");
					fifo1=open(pipe_nombre, O_WRONLY);
					write(fifo1,leerFIFO,strlen(leerFIFO)+1);
					close (fifo1);
					exit(0);
				}else{
					printf("El mensaje recibido es: %s\n",leerFIFO);
					exit(0);
				}
			}
			break;
			case 2:
			if((pid=fork())==0){
				printf("\n Has elegido hermano 2 de PID %i, vamos a ver si hay algun mensaje\n", getpid());
				fifo1=open(pipe_nombre, O_RDONLY);
				read(fifo1,leerFIFO,MAX);
				close (fifo1);
				if(leerFIFO!=lecHermano2){
					printf("El mensaje recibido es no era para ti.\n");
					fifo1=open(pipe_nombre, O_WRONLY);
					write(fifo1,leerFIFO,strlen(leerFIFO)+1);
					close (fifo1);
					exit(0);
				}else{
					printf("El mensaje recibido es: %s\n",leerFIFO);
					exit(0);
				}
			}
			break;
			case 3:
			if((pid=fork())==0){
				printf("\n Has elegido hermano 3 de PID %i, vamos a ver si hay algun mensaje\n", getpid());
				fifo1=open(pipe_nombre, O_RDONLY);
				read(fifo1,leerFIFO,MAX);
				close (fifo1);
				if(leerFIFO!=lecHermano3){
					printf("El mensaje recibido es no era para ti.\n");
					fifo1=open(pipe_nombre, O_WRONLY);
					write(fifo1,leerFIFO,strlen(leerFIFO)+1);
					close (fifo1);
					exit(0);
				}else{
					printf("El mensaje recibido es: %s\n",leerFIFO);
					exit(0);
				}
			}
			break;
		}
	} else if(opcion==2){
		printf("\nHas elegido escribir\nA quien te gustaria escribir:\n 1.Hermano 1\n 2.Hermano 2\n 3.Hermano 3\n");
		scanf("%d",&escribir);
		switch(escribir){
			case 1:
				printf("\n Has elegido hermano  escribir al hermano 1\n");
				//close (fifo1);	
				fifo1=open(pipe_nombre, O_WRONLY);
				strcpy(mjHermano1,"Hola hermano 1.");
				write(fifo1,mjHermano1,strlen(mjHermano1)+1);
				close (fifo1);
				printf("El mensaje escrito es: %s\n",mjHermano1);
			break;
			case 2:
				printf("\n Has elegido hermano  escribir al hermano 2\n");
				//close (fifo1);	
				fifo1=open(pipe_nombre, O_WRONLY);
				printf("\n Has");
				strcpy(mjHermano2,"Hola hermano 2.");
				printf("\n Hola");
				write(fifo1,mjHermano2,strlen(mjHermano2)+1);
				printf("\n lloro");
				close (fifo1);
				printf("El mensaje escrito es: %s\n",mjHermano2);
			break;
			case 3:
				printf("\n Has elegido hermano  escribir al hermano 3\n");	
				//close (fifo1);
				fifo1=open(pipe_nombre, O_WRONLY);
				strcpy(mjHermano3,"Hola hermano 3.");
				write(fifo1,mjHermano3,strlen(mjHermano3)+1);
				close (fifo1);
				printf("El mensaje escrito es: %s\n",mjHermano3);
			break;
		}
	}else{
		printf("Favor de seleccionar 1 o 2\n");
		wait(&pid);		
		exit(0);
	}
}
