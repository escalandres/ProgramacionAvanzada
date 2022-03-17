/*Alumno: Andres Rafael Escala Acosta*/
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256

void main(){
	int pid;
	char pipe1_nombre[]="myfifo1";
	char mensaje[MAX];
	int fifo1;
	int opt; //Escribir 1, leer 2 o salir 3
	char receptor[2];//Quein recibe el mensaje
	char emisor[2]; //Quien manda el mensaje
	int mensaje_total[MAX];//Mensaje a enviar

	mknod(pipe1_nombre, S_IFIFO|0666,0);
	
	if((pid=fork())==0){//codigo hijo1

		//Pregunta que proceso eres, solo se pregunta una vez a lo largo del programa
		printf("Cual proceso eres? (del 1 en adelante) \n\nNum: ");
		fflush(stdin);
		scanf("%s", &emisor);
		
		//Se podrá leer o escribir las veces que quiera mientras no tecleen el 3
		while (opt != 3){ 
			strcpy(mensaje_total, ""); //Se limpia el mensaje antes de enviar uno nuevo
			printf("\nDeseas escribir(1), leer(2) o salir(3)\n\nOpt: ");
			fflush(stdin);
			scanf("%d", &opt);

			//El proceso desea escribir
			if (opt == 1){
				
				//Aquien va dirigido el mensaje
				printf("\nA quien va dirigido\n\nDestinatario: ");
				fflush(stdin);
				scanf("%s", &receptor);
				
				//Lo que dira el mensaje
				printf("\nQue mensaje deseas escribir?\n\n Mensaje: ");
				fflush(stdin);
				scanf("%s",&mensaje);

				/*Se concatenará toda la información, el primer digito es para quien va dirigido
				el segundo es para saber quien lo envia, y la ultima es lo que dice el mensaje*/
				strcat(mensaje_total, receptor);
				strcat(mensaje_total, " ");
				strcat(mensaje_total, emisor);
				strcat(mensaje_total, " ");
				strcat(mensaje_total, mensaje);

				//Abre la tuberia y manda el mensaje
				fifo1=open(pipe1_nombre,O_WRONLY);
				printf("Soy el hijo [%s] el mensaje a enviar es para [%s] y dice: %s\n",emisor, receptor, mensaje);
				write(fifo1,mensaje_total, sizeof(mensaje_total));
				close(fifo1);

			}else if(opt == 2){ //El proceso quiere leer
				
				//Abre la tuberia en modo lectura y guarda el mensaje
				fifo1=open(pipe1_nombre,O_RDONLY);
				read(fifo1,mensaje,MAX);

				/*Esta parte es importante porque convertimos los valores
				receptor_tuberia ---> Obtiene el primer digito del mensaje: indica para quien es el mensaje
				emisor_tuberia ---> Obtiene el segundo digito del mensaje: indica el emisor pero del proceso que esta leyendo la tuberia, 
				*/
				int receptor_tuberia = (int) mensaje[0];
				int emisor_tuberia = (int) emisor[0];

				/*Se compara si el proceso actual es el receptor que selecciono el emisor*/
				if (emisor_tuberia == receptor_tuberia){
					printf("Era para mi. Soy el hijo [%c] y recibo el mensaje proveniente de [%c] y dice : %s\n",mensaje[0], mensaje[2], mensaje);
					close(fifo1);

				}else{
					/*El mensaje en la tuberia no es para el proceso actual*/
					printf("El mensaje no era para mi\n");
					close(fifo1);
					
					fifo1=open(pipe1_nombre,O_WRONLY);
					write(fifo1,mensaje, sizeof(mensaje));
					close(fifo1);
				}
				
			}
		
		
		}
		printf("\nSaliendo del programa...\n\n");
		sleep(3);
		exit(0);
	}
	
	else{
		wait(&pid);
		exit(0);
		}

}