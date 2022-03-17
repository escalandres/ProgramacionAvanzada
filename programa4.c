#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>

//recibe como parametro el nombre del archivo
void crearArchivo(char *);
//recibe como parametro el nombre del archivo y el mensaje que se escribirá
void escribirArchivo(char *, int, char*);
//recibe como parametro el nombre del archivo
void leerArchivo(char* ,int );

int main(){
	
	
	int proc;
	int i;
	int arr[3];
	int sleepTime = 20000;
	char nombreArchivo[20] = "procesos.txt";
	FILE *archivo;
	
	printf("\n");
	
	for(i=0; i<3; i++){
		
	 proc = fork(); //pid_t proc;
	
	if(proc < 0)
		printf("ocurrio un error\n");
	if(proc == 0){
		printf("proceso hijo: %i, papa: %i\n", getpid(), getppid());
		arr[i] = getpid();
		break;
	}
	else{
		//wait(&proc);
	}
	
		
	}
	
	while(1){
		
		if(i == 0){
			usleep(sleepTime*100);
			printf("proceso 1 %i\n", getpid());
			
			if(archivo = fopen(nombreArchivo,"r")){
				int vacio;
				fscanf(archivo, "%i", &vacio);
				//usleep(sleepTime*10);
				printf("entro\n");
				
				//Comprueba si esta vacio el archivo
				//if(feof(archivo) != 0 || strcmp(vacio, "leido") == 0){
				if(feof(archivo) != 0 || vacio == -1){
					fclose(archivo);
					printf("El proceso 1 no encontro nada,entonces, escribira\n");
					escribirArchivo(nombreArchivo, getpid(), "Hola");
					usleep(sleepTime*10);
				}
				else{
					printf("El proceso 1 encontro algo escrito, lo leera\n");
					leerArchivo(nombreArchivo, getpid());
				}
					
				fclose(archivo);
				
			}else{
				printf("No existe Archivo desde proceso 1\n");
				crearArchivo("procesos.txt");
				escribirArchivo("procesos.txt", getpid(), "Hola");
			}
			
			//usleep(sleepTime*100);
		}
		if(i==1){
			
			usleep(sleepTime*200);
			printf("proceso 2 %i\n", getpid());
			if(archivo = fopen(nombreArchivo,"r")){
				int vacio;
				fscanf(archivo, "%i", &vacio);
				//usleep(sleepTime*10);
				
				//Comprueba si esta vacio el archivo
				//if(feof(archivo) != 0 || strcmp(vacio, "leido") == 0){
				if(feof(archivo) != 0 || vacio == -1){
					fclose(archivo);
					printf("El proceso 2 no encontro nada,entonces, escribira\n");
					escribirArchivo(nombreArchivo, getpid(), "Hola");
					usleep(sleepTime*10);
				}
				else{
					printf("El proceso 2 encontro algo escrito, lo leera\n");
					leerArchivo(nombreArchivo, getpid());
				}
					
				fclose(archivo);
				
			}else{
				printf("No existe Archivo desde proceso 2\n");
				crearArchivo("procesos.txt");
				escribirArchivo("procesos.txt", getpid(), "Hola");
			}
		}
		if(i==2){
			usleep(sleepTime*300);
			printf("proceso 3 %i\n", getpid());
			if(archivo = fopen(nombreArchivo,"r")){
				int vacio;
				fscanf(archivo, "%i", &vacio);
				//usleep(sleepTime*10);
				printf("entro\n");
				
				//Comprueba si esta vacio el archivo
				//if(feof(archivo) != 0 || strcmp(vacio, "leido") == 0){
				if(feof(archivo) != 0 || vacio == -1){
					fclose(archivo);
					printf("El proceso 3 no encontro nada,entonces, escribira\n");
					escribirArchivo(nombreArchivo, getpid(), "Hola");
					usleep(sleepTime*10);
				}
				else{
					printf("El proceso 3 encontro algo escrito, lo leera\n");
					leerArchivo(nombreArchivo, getpid());
				}
					
				fclose(archivo);
				
			}else{
				printf("No existe Archivo desde proceso 3\n");
				crearArchivo("procesos.txt");
				escribirArchivo("procesos.txt", getpid(), "Hola");
			}
		}
			
		
	
	}
	
	wait(&proc);
	exit(0);
	
	
	
}

void crearArchivo(char *nombre){
	FILE *archivo = fopen(nombre,"w");
	fclose(archivo);
}

void escribirArchivo(char* nombre, int proceso, char *mensaje){
	FILE *archivo = fopen(nombre, "w+");
	if(proceso != -1)
		fprintf(archivo,"%i %s", proceso, mensaje);
	else
		fprintf(archivo,"%i", proceso);
	fclose(archivo);
}

void leerArchivo(char* nombre, int pidLector){
	FILE *archivo = fopen(nombre,"r");
	char palabra[15];
	char mensaje[200];
	int pidProceso;
	
	/*
	while(feof(archivo)==0){
		fscanf(archivo, "%s", &palabra);
		strcat(mensaje, palabra);
		strcat(mensaje, " ");
	}*/
	
	fscanf(archivo, "%i %s", &pidProceso, &mensaje);
	fclose(archivo);
	escribirArchivo(nombre, -1, "Nada");
	printf("Lo recibio el proceso: %i, lo mando el proceso: %i y el mensaje era: %s\n",pidLector, pidProceso, mensaje);
	
	
}