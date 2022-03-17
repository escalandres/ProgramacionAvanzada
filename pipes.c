#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 256

int main(){

    int pid, *estado;
    char pipe1_nombre[MAX]="myfifo";
    char mensaje[MAX];
    int fifo1;
    
    mknod(pipe1_nombre, S_IFIFO | 0666, 0);
    
    if((pid=fork()) == 0) //CODIGO DEL HIJO 1
    {
        fifo1=open(pipe1_nombre, O_WRONLY);
        strcpy(mensaje, "ENVIANDO");
        printf("Soy el hijo 1 el mensaje a enviar: %s\n", mensaje);
        write(fifo1, mensaje, strlen(mensaje)+1);
        close(fifo1);
        exit(0);
    }//Fin del codigo del hijo
    
    if((pid=fork())==0) //CODIGO DEL HIJO 2
    {
        fifo1=open(pipe1_nombre, O_RDONLY);
        read(fifo1, mensaje, MAX);
        printf("Soy el hijo 2 y recibo el mensaje: %s\n", mensaje);
        close(fifo1);
        exit(0);
    }//Fin del codigo hijo
    
    else //codigo padre
    {
        exit(0);
    }
    
}
