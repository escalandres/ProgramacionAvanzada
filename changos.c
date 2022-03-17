//Integrantes:
//Vargas Sánchez Andrea Liliana			
//Cisneros Martínez Daphne Liliana
//Escala Acosta Andres Rafael

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
int comunidad_Norte=10;
int comunidad_Sur=8;
int liana_Norte=0;
int liana_Sur=0;
sem_t norte;
sem_t sur;
void Comunidad_Norte(void*);
void Comunidad_Sur(void*);
void usar_Liana(void*);


void main(void){
    printf("\n\t-----Changos filosofos----\n\n");
    int i=0,j=0;
    pthread_t th_n1, th_n2, th_n3, th_n4, th_n5,th_n6,th_n7,th_n8,th_n9,th_n10;
    pthread_t th_s1, th_s2, th_s3, th_s4, th_s5,th_s6,th_s7,th_s8;
    pthread_t com_norte[]={th_n1, th_n2, th_n3, th_n4, th_n5,th_n6,th_n7,th_n8,th_n9,th_n10};
    pthread_t com_sur[]={th_s1, th_s2, th_n3, th_s4, th_s5,th_s6,th_s7,th_s8};

    for(i=0;i<comunidad_Norte;i++){
        pthread_create(&com_norte[i],NULL,(void*)Comunidad_Norte,(void*)1);
    }
    for(j=0;j<comunidad_Sur;j++){
        pthread_create(&com_sur[j],NULL,(void*)Comunidad_Sur,(void*)2);
    }

    /*inicializar los semaforos */
    sem_init(&norte,0,1);
    sem_init(&sur,0,1);

    for(i=0;i<comunidad_Norte;i++){
        pthread_join(com_norte[i],NULL);
    }
    for(j=0;j<comunidad_Sur;j++){
        pthread_join(com_sur[j],NULL);
    }

    sem_destroy(&norte);
    sem_destroy(&sur);
    exit(0);
}

void usar_Liana(void *a){
    int x=(int *)a;
    // printf("\nX: %d\n",x);
    if (x==1){
    printf("\nEl mono es del norte\n");
        if(liana_Sur==0){
            sem_wait(&norte); //Los monos del Sur tienen que esperar a que pasen los del norte
            liana_Norte++;
            
            sem_post(&norte);
            do{
                
                printf("\n----Mono del norte cruzando por la liana! Hay otros monos formados!\n");
                int time = 3+rand()%4;
                sleep(time);
                sem_wait(&norte);
                liana_Norte--;
                printf("\n-----Mono del norte ya cruzo!\n");
                
                comunidad_Norte--;
                comunidad_Sur++; //La poblacion de la comunidad sur aumenta
                sem_post(&norte); //Los monos del Sur pueden usar la liana
                a=2;
                Comunidad_Sur(a);
            }while(liana_Norte!=0&&liana_Norte>0);
            printf("\nListo lo del norte\n");
            
        }
        else{
            //En caso de que hayan monos del Sur en la liana
            printf("\nLos monos del Sur estan ocupando la liana! Los monos del norte se estan poniendo en fila mientras esperan!\n");
        }
    } 
    else{
    printf("\nEl mono es del sur\n");
        if(liana_Norte==0){
            sem_wait(&sur); //Los monos del norte tienen que esperar a que pasen los del Sur
            liana_Sur++;
            sem_post(&sur);
            do{
                printf("\n----Mono del sur cruzando por la liana! Hay otros monos formados!\n");
                int time = 3+rand()%4;
                sleep(time);
                sem_wait(&sur);
                liana_Sur--;
                comunidad_Sur--;
                comunidad_Norte++; //La poblacion de la comunidad sur aumenta
                sem_post(&sur); //Los monos del Norte pueden usar la liana
                a=1;
                Comunidad_Norte(a);
            }while(liana_Sur!=0&&liana_Sur>0);
            printf("\nListo lo del sur\n");
        }
        else{
            //En caso de que hayan monos del Norte en la liana
            printf("\nLos monos del Norte estan ocupando la liana! Los monos del Sur se estan poniendo en fila mientras esperan!\n");
        }
    }
}

void Comunidad_Norte(void *a){
int time = 3+rand()%3;// entre 3 a 10 seg para pensar si quiere viajar o quiere quedarse jugando
sleep(time);
//Usamos un random para decidir quienes van a usar la liana
int migrar = rand()%2;// entre 0 (no quiere) y 1 (si quiere) 
if (migrar == 1){
    printf("\nMono del norte quiere cruzar\n");
	usar_Liana(a);
}
else
	printf("\nMono del norte prefiere quedarse para jugar un rato\n");
	int jugar = 3+rand()%4; //de 3 a 15 segundos para que juegue
	sleep(jugar);
	Comunidad_Norte(a); //Se vuelve a llamar a la funcion para repetir el proceso y ver si el mono cambio de opinion
}

void Comunidad_Sur(void *a){
    int time = 3+rand()%2; //entre 3 a 10 seg para pensar si quiere viajar o quiere quedarse jugando
    sleep(time);
    //Usamos un random para decidir quienes van a usar la liana
    int migrar = rand()%2; //entre 0 (no quiere) y 1 (si quiere) 
    if (migrar == 1){
        printf("\nMono del sur quiere cruzar\n");
        usar_Liana(a);
    }
    else{
        printf("\nMono del sur prefiere quedarse para jugar un rato\n");
        int jugar = 3+rand()%4; //de 3 a 15 segundos para que juegue
        sleep(jugar);
        Comunidad_Sur(a); //Se vuelve a llamar a la funcion para repetir el proceso y ver si el mono cambio de opinion
    }
}