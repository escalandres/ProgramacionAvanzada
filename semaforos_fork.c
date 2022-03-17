#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//LIBRERIAS UEVAS
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>



void error(char* errorInfo){
	
	fprintf(stderr, "%s", errorInfo);
	exit(1);
}


void doSignal(int semid, int numSem){
	
	struct sembuf sops;
	
	sops.sem_num = numSem;
	sops.sem_op = 1;
	sops.sem_flg = 0;
	
	if (semop(semid, &sops, 1) == -1){
		
		perror(NULL);
		error("Error al hacer Signal \n");
	}
	
}



void doWait(int semid, int numSem){
	
	struct sembuf sops;
	
	sops.sem_num = numSem;
	sops.sem_op = -1;
	sops.sem_flg = 0;
	
	if (semop(semid, &sops, 1) == -1){
		
		perror(NULL);
		error("Error al hacer el Wait \n");
	}
	
}


void initSem(int semid, int numSem, int valor){
	
	if (semctl(semid, numSem, SETVAL, valor) < 0){
		
		perror(NULL);
		error("Error iniciando semaforo \n");
	}
}


int main(){
	
	puts("Sincronizacion con Semaforos \n");
	
	int semaforo;
	int pid;
	
	if((semaforo = semget(IPC_PRIVATE, 1, IPC_CREAT | 0700)) < 0){
		
		perror(NULL);
		error("Semaforo: semget \n");
		
	}
	
	initSem(semaforo, 0, 1);
	puts("Semaforo habilitado \n");
	pid = fork();
	
	switch(pid){
			
		case -1:
			error("Error en el fork\n");
			break;
			
		case 0:
			
			doWait(semaforo, 0);
			
			puts("Entro el hijo, el padre espera \n");
			sleep(2);
			puts("El hijo sale \n");
			
			doSignal(semaforo, 0);
			
			exit(0);
			break;
			
		default:
			
			doWait(semaforo, 0);
			
			puts("Entro el padre, el hijo espera\n");
			sleep(2);
			puts("El padre sale\n");
			
			doSignal(semaforo, 0);
			
			wait(&pid);
			break;
	}
	
	sleep(2);
	
	//Liberacion del semaforo	
	
	if ((semctl(semaforo, 0, IPC_RMID)) == -1){
		
		perror(NULL);
		error("Borrando semaforo\n");
	}
	
	return 0;
}

