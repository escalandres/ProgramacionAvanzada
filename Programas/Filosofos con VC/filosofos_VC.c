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
int sema[5]; //lleva la cuenta de los palillos ocupados y disponibles

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexJ = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  palillo1= PTHREAD_COND_INITIALIZER;
pthread_cond_t  palillo2= PTHREAD_COND_INITIALIZER;
pthread_cond_t  palillo3= PTHREAD_COND_INITIALIZER;
pthread_cond_t  palillo4= PTHREAD_COND_INITIALIZER;
pthread_cond_t  palillo0= PTHREAD_COND_INITIALIZER;
pthread_cond_t  jarra= PTHREAD_COND_INITIALIZER;
// sem_t jarra;
// //Cada filosofo tiene un palillo con su numero y usa el del otro filosofos a su lado
// sem_t palillo1;
// sem_t palillo2;
// sem_t palillo3;
// sem_t palillo4;
// sem_t palillo0;

void Comer(void*);
void Beber(void*);
void Pensar(void*);
void Filosofo(void*);

void main(void){
    int i=0;
    for(i=0;i<5;i++){
        sema[i]=1;
        //Todos los palillos estan disponibles al inicio
    }
    pthread_t th_f1, th_f2, th_f3, th_f4, th_f0;
    printf("\n\t-----Filosofos chinos-----\n\n");
    // /*inicializar los semaforos */
    // sem_init(&jarra,0,1); //Jarra disponible al inicio
    // //Todos los palillos estan disponibles al inicio
    // sem_init(&palillo1,0,1);
    // sem_init(&palillo2,0,1);
    // sem_init(&palillo3,0,1);
    // sem_init(&palillo4,0,1);
    // sem_init(&palillo0,0,1);

    /* crear los procesos ligeros*/
    pthread_create(&th_f1,NULL,(void*)Pensar,(void*)1);
    pthread_create(&th_f2,NULL,(void*)Pensar,(void*)2);
    pthread_create(&th_f3,NULL,(void*)Pensar,(void*)3);
    pthread_create(&th_f4,NULL,(void*)Pensar,(void*)4);
    pthread_create(&th_f0,NULL,(void*)Pensar,(void*)0);

    /*esperar su finalizacion*/
    pthread_join(th_f1,NULL);
    pthread_join(th_f2,NULL);
    pthread_join(th_f3,NULL);
    pthread_join(th_f4,NULL);
    pthread_join(th_f0,NULL);

    // sem_destroy(&jarra);
    // sem_destroy(&palillo1);
    // sem_destroy(&palillo2);
    // sem_destroy(&palillo3);
    // sem_destroy(&palillo4);
    // sem_destroy(&palillo0);
    
    pthread_cond_destroy(&jarra);
	pthread_cond_destroy(&palillo0);
    pthread_cond_destroy(&palillo1);
    pthread_cond_destroy(&palillo2);
    pthread_cond_destroy(&palillo3);
    pthread_cond_destroy(&palillo4);
    exit(0);
}

void Beber(void *a){
    printf("\nEl filosofo %i: %li quiere beber\n",(int *)a,pthread_self());
    pthread_mutex_lock(&mutex); 
    // sem_wait(&jarra); //Jarra ocupada
    // pthread_cond_wait(&jarra, &mutex);
    int drink = 2+rand()%5;
    sleep(drink); //Tiempo para beber
    // sem_post(&jarra); //Jarra disponible
    // pthread_cond_signal(&jarra);
    pthread_mutex_unlock(&mutex); 
    printf("\nEl filosofo %i: %li termino de beber en %d seg\n",(int *)a,pthread_self(),drink);
    Pensar(a); //Cuando termina de beber, se va a pensar
}

void Comer(void *a){
    printf("\nEl filosofo %i: %li quiere comer\n",(int *)a,pthread_self());
    int x=(int *)a; //Para revisar el numero del filosofo

    if(x==0){
        printf("\nEl filosofo %i: %li va a comer\n",(int *)a,pthread_self());
        pthread_mutex_lock(&mutex); 
        printf("\nEl filosofo %i: %li va a agarrar el palillo 4\n",(int *)a,pthread_self());

        if(sema[4]==1){
            pthread_cond_wait(&palillo4, &mutex);
            sema[4]=0;
            printf("\nEl filosofo %i: %li agarro el palillo 4\n",(int *)a,pthread_self());
            
            if(sema[0]==1){
                pthread_cond_wait(&palillo0, &mutex);
                sema[0]=0;
                printf("\nEl filosofo %i: %li agarro el palillo 0\n",(int *)a,pthread_self());

                printf("\nEl filosofo %i: %li va a comer\n",(int *)a,pthread_self());
                int eat = 4+rand()%5;
                sleep(eat);
                sema[0]=1;
                sema[4]=1;
                pthread_cond_signal(&palillo0);
                pthread_cond_signal(&palillo4);
                pthread_mutex_unlock(&mutex); 
                printf("\nEl filosofo %i: %li termino de comer en %d seg. Ahora va a pensar\n",(int *)a,pthread_self(),eat);
                Pensar(a);
            }
            else{
                pthread_cond_signal(&palillo4);
                pthread_mutex_unlock(&mutex);
                printf("\nEl filosofo %i: %li no pudo comer! Ahora va a beber\n",(int *)a,pthread_self());
                Beber(a);
            }
        }
        else{
            pthread_mutex_unlock(&mutex);
        	//Si el filosofo no puede comer, procede a beber agua
            printf("\nEl filosofo %i: %li no pudo comer! Ahora va a beber\n",(int *)a,pthread_self());
            Beber(a);
        }
    }
    else if(x==4){
        printf("\nEl filosofo %i: %li va a comer\n",(int *)a,pthread_self());
        pthread_mutex_lock(&mutex); 
        printf("\nEl filosofo %i: %li va a agarrar el palillo 3\n",(int *)a,pthread_self());
        if(sema[3]==1){
            pthread_cond_wait(&palillo3, &mutex);
            sema[3]=0;
            printf("\nEl filosofo %i: %li agarro el palillo 3\n",(int *)a,pthread_self());

            if(sema[4]==1){
                pthread_cond_wait(&palillo4, &mutex);
                sema[4]=0;
                printf("\nEl filosofo %i: %li agarro el palillo 4\n",(int *)a,pthread_self());

                printf("\nEl filosofo %i: %li va a comer\n",(int *)a,pthread_self());
                int eat = 4+rand()%5;
                sleep(eat);
                sema[3]=1;
                sema[4]=1;
                pthread_cond_signal(&palillo3);
                pthread_cond_signal(&palillo4);
                pthread_mutex_unlock(&mutex); 
                printf("\nEl filosofo %i: %li termino de comer en %d seg. Ahora va a pensar\n",(int *)a,pthread_self(),eat);
                Pensar(a);
            }
            else{
                pthread_cond_signal(&palillo3);
                pthread_mutex_unlock(&mutex);
                printf("\nEl filosofo %i: %li no pudo comer! Ahora va a beber\n",(int *)a,pthread_self());
                Beber(a);
            }
        }
        else{
            pthread_mutex_unlock(&mutex);
        	//Si el filosofo no puede comer, procede a beber agua
            printf("\nEl filosofo %i: %li no pudo comer! Ahora va a beber\n",(int *)a,pthread_self());
            Beber(a);
        }
    }
    else{
        printf("\nEl filosofo %i: %li va a comer\n",(int *)a,pthread_self());
        pthread_mutex_lock(&mutex); 
        
        printf("\nEl filosofo %i: %li va a agarrar el palillo %d\n",(int *)a,pthread_self(),x-1);

        if(sema[x-1]==1){
            if(x==1){pthread_cond_wait(&palillo0, &mutex);}
            else if(x==2){pthread_cond_wait(&palillo1, &mutex);}
            else {pthread_cond_wait(&palillo2, &mutex);}
            sema[x-1]=0;
            printf("\nEl filosofo %i: %li agarro el palillo %d\n",(int *)a,pthread_self(),x-1);

            if(sema[x]==1){
                if(x==1){
                    sema[x]=0;
                    pthread_cond_wait(&palillo1, &mutex);
                    printf("\nEl filosofo %i: %li agarro el palillo 1\n",(int *)a,pthread_self());

                    printf("\nEl filosofo %i: %li va a comer",(int *)a,pthread_self());
                    int eat = 4+rand()%5;
                    printf("Por %d segundos\n",eat);
                    sleep(eat);
                    sema[0]=1;
                    sema[1]=1;
                    pthread_cond_signal(&palillo0);
                    pthread_cond_signal(&palillo1);
                    
                }
                else if(x==2){
                    sema[x]=0;
                    pthread_cond_wait(&palillo2, &mutex);
                    printf("\nEl filosofo %i: %li agarro el palillo 2\n",(int *)a,pthread_self());

                    printf("\nEl filosofo %i: %li va a comer",(int *)a,pthread_self());
                    int eat = 4+rand()%5;
                    printf("Por %d segundos\n",eat);
                    sleep(eat);
                    sema[1]=1;
                    sema[2]=1;
                    pthread_cond_signal(&palillo1);
                    pthread_cond_signal(&palillo2);
                }
                else{ //x==3
                    sema[x]=0;
                    pthread_cond_wait(&palillo3, &mutex);
                    printf("\nEl filosofo %i: %li agarro el palillo 3\n",(int *)a,pthread_self());

                    printf("\nEl filosofo %i: %li va a comer",(int *)a,pthread_self());
                    int eat = 4+rand()%5;
                    printf("Por %d segundos\n",eat);
                    sleep(eat);
                    sema[x-1]=1;
                    sema[x]=1;
                    pthread_cond_signal(&palillo2);
                    pthread_cond_signal(&palillo3);
                }
                pthread_mutex_unlock(&mutex); 
                printf("\nEl filosofo %i: %li termino de comer. Ahora va a pensar\n",(int *)a,pthread_self());
                Pensar(a);
            }
            else{
                if(x==1){pthread_cond_signal(&palillo0);}
                else if(x==2){pthread_cond_signal(&palillo1);}
                else {pthread_cond_signal(&palillo2);}
                pthread_mutex_unlock(&mutex);
                printf("\nEl filosofo %i: %li no pudo comer! Ahora va a beber\n",(int *)a,pthread_self());
                Beber(a);
            }
        }
        else{
            pthread_mutex_unlock(&mutex);
        	//Si el filosofo no puede comer, procede a beber agua
            printf("\nEl filosofo %i: %li no pudo comer! Ahora va a beber\n",(int *)a,pthread_self());
            Beber(a);
        }
    }
}

void Pensar(void *a){
    int time = 5+rand()%20; 
    printf("\nEl filosofo %i: %li esta pensando por %d seg\n",(int *)a,pthread_self(),time);
    sleep(time); //Tiempo para pensar
    int que_hacer = 0 + rand() %2;
    if(que_hacer==0){
        printf("\nEl filosofo %i: %li le dio hambre\n",(int *)a,pthread_self());
        Comer(a); //Despues de pensar, le da hambre y va a comer
    }
    else{
        printf("\nEl filosofo %i: %li le dio sed\n",(int *)a,pthread_self());
        Beber(a);
    }
}