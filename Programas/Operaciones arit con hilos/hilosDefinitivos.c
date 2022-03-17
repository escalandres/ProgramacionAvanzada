//Autor: Andres Rafael Escala Acosta
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
//gcc hilos.c -l pthread -o hilo
int variable_compartida=0; //variable global
int suma=0,resta=0,multi=0,divi=0; //Variables del contador de cada operacion
int cont_suma[3],cont_resta[3],cont_multi[3],cont_div[3]; //Contadores para los casos del random (cumplir con las 5 operaciones)
int r=0,s=0,m=0,d=0,x=0,y=0,z=0,w=0; //x,y,z,w: Variables auxiliares para llevar la cuenta en el for; r,s,m,d: los contadores de los arreglos de arriba

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//Estructura para las operaciones. Se puede usar cualquier numero (siempre que sea entero); y cualquier operacion basica (+,-,*,/)
struct Operacion
{
    int operando;
    char operador;
};

void funcion_hilo(struct Operacion *argumento);

int main(){
    pthread_t id_hilo,id_hilo2,id_hilo3,id_hilo4,id_hilo5,id_hilo6,id_hilo7,id_hilo8,id_hilo9,id_hilo10,id_hilo11,id_hilo12;
    struct Operacion op1,op2,op3,op4,op5,op6,op7,op8,op9,op10,op11,op12;
    void* valor1_retorno;
    void* valor2_retorno;
    void* valor3_retorno;
    void* valor4_retorno;
    void* valor5_retorno;
    void* valor6_retorno;
    void* valor7_retorno;
    void* valor8_retorno;
    void* valor9_retorno;
    void* valor10_retorno;
    void* valor11_retorno;
    void* valor12_retorno;

    //Creacion de cada hilo. Para pruebas, se pueden cambiar los valores de operador y operando
    op1.operador='+';
    op1.operando=9;
    if(pthread_create(&id_hilo,NULL,(void*)funcion_hilo,(void *)&op1)){
        printf("Problema en la creacion del hilo 1\n");
        exit(EXIT_FAILURE);
    }
    op2.operador='-';
    op2.operando=7;
    if(pthread_create(&id_hilo2,NULL,(void*)funcion_hilo,(void *)&op2)){
        printf("Problema en la creacion del hilo 2\n");
        exit(EXIT_FAILURE);
    }
    op3.operador='*';
    op3.operando=4;
    if(pthread_create(&id_hilo3,NULL,(void*)funcion_hilo,(void *)&op3)){
        printf("Problema en la creacion del hilo 3\n");
        exit(EXIT_FAILURE);
    }
    op4.operador='/';
    op4.operando=2;
    if(pthread_create(&id_hilo4,NULL,(void*)funcion_hilo,(void *)&op4)){
        printf("Problema en la creacion del hilo 4\n");
        exit(EXIT_FAILURE);
    }
    op5.operador='+';
    op5.operando=12;
    if(pthread_create(&id_hilo5,NULL,(void*)funcion_hilo,(void *)&op5)){
        printf("Problema en la creacion del hilo 5\n");
        exit(EXIT_FAILURE);
    }
    op6.operador='*';
    op6.operando=20;
    if(pthread_create(&id_hilo6,NULL,(void*)funcion_hilo,(void *)&op6)){
        printf("Problema en la creacion del hilo 6\n");
        exit(EXIT_FAILURE);
    }
    op7.operador='/';
    op7.operando=5;
    if(pthread_create(&id_hilo7,NULL,(void*)funcion_hilo,(void *)&op7)){
        printf("Problema en la creacion del hilo 4\n");
        exit(EXIT_FAILURE);
    }
    op8.operador='-';
    op8.operando=8;
    if(pthread_create(&id_hilo8,NULL,(void*)funcion_hilo,(void *)&op8)){
        printf("Problema en la creacion del hilo 8\n");
        exit(EXIT_FAILURE);
    }
    op9.operador='-';
    op9.operando=3;
    if(pthread_create(&id_hilo9,NULL,(void*)funcion_hilo,(void *)&op9)){
        printf("Problema en la creacion del hilo 9\n");
        exit(EXIT_FAILURE);
    }
    op10.operador='/';
    op10.operando=4;
    if(pthread_create(&id_hilo10,NULL,(void*)funcion_hilo,(void *)&op10)){
        printf("Problema en la creacion del hilo 10\n");
        exit(EXIT_FAILURE);
    }
    op11.operador='+';
    op11.operando=23;
    if(pthread_create(&id_hilo11,NULL,(void*)funcion_hilo,(void *)&op11)){
        printf("Problema en la creacion del hilo 11\n");
        exit(EXIT_FAILURE);
    }
    op12.operador='*';
    op12.operando=9;
    if(pthread_create(&id_hilo12,NULL,(void*)funcion_hilo,(void *)&op12)){
        printf("Problema en la creacion del hilo 12\n");
        exit(EXIT_FAILURE);
    }
    printf("Esperando a que termine el hilo hijo...\n");
    printf("Proceso papa: %li \n",pthread_self());
    if(pthread_join(id_hilo,&valor1_retorno)){
        printf("Problema al crear el enlace con otro hilo\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(id_hilo2,&valor2_retorno)){
        printf("Problema al crear el enlace con otro hilo\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(id_hilo3,&valor3_retorno)){
        printf("Problema al crear el enlace con otro hilo\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(id_hilo4,&valor4_retorno)){
        printf("Problema al crear el enlace con otro hilo\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(id_hilo5,&valor5_retorno)){
        printf("Problema al crear el enlace con otro hilo\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(id_hilo6,&valor6_retorno)){
        printf("Problema al crear el enlace con otro hilo\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(id_hilo7,&valor7_retorno)){
        printf("Problema al crear el enlace con otro hilo\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(id_hilo8,&valor8_retorno)){
        printf("Problema al crear el enlace con otro hilo\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(id_hilo9,&valor9_retorno)){
        printf("Problema al crear el enlace con otro hilo\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(id_hilo10,&valor10_retorno)){
        printf("Problema al crear el enlace con otro hilo\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(id_hilo11,&valor11_retorno)){
        printf("Problema al crear el enlace con otro hilo\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(id_hilo12,&valor12_retorno)){
        printf("Problema al crear el enlace con otro hilo\n");
        exit(EXIT_FAILURE);
    }
    //printf("El hilo que espera papa, regreso!!!\t %s\n",(char *)valor_retorno);
    exit(EXIT_SUCCESS);
}
//Funcion para realizar las operaciones aritmeticas
void funcion_hilo(struct Operacion *argumento){
    printf("\nEl codigo esta en ejecucion!\n\n");
    printf("La variable es: %i, el argumento es: %i y el operador es: %c\n",variable_compartida,argumento->operando,argumento->operador);
    printf("\nproceso hijo: %li\n", pthread_self());
    sleep(3);
    pthread_mutex_lock(&mutex); //Se bloquea el mutex para evitar que otro proceso haga una operacion antes que el primero termine
    //Se verifica cual operacion se quiere realizar, y se separa en casos
    switch(argumento->operador){
        case '+':
            printf("\n\t--Suma %d--\n",s);
            int i; //Variable auxiliar del for
            int random_suma = 1 + rand() %2; //Se genera un numero random entre 1-2, para las operaciones
            //Nota: Para este programa se decidio solamente que el maximo de operaciones que puede hacer
            //un hilo sea 2, y el minimo es 1
            cont_suma[s]=random_suma;
            printf("\nProceso: %li\n", pthread_self()); //Identificador del hilo en ejecucion
            s++; //Variable auxiliar para el indice de los arreglos
            //Condicionales para el caso de la tercera operacion, se asegura que se hagan las 5 operaciones solicitadas
            if(cont_suma[0]==1&&cont_suma[1]==1&&cont_suma[2]==1){
                random_suma=3;
            }
            else if(cont_suma[0]==1&&cont_suma[1]==2&&cont_suma[2]==1){
                random_suma=2;
            }
            else if(cont_suma[0]==2&&cont_suma[1]==1&&cont_suma[2]==1){
                random_suma=2;
            }
            else if(cont_suma[0]==2&&cont_suma[1]==2&&cont_suma[2]==2){
                random_suma=1;
            }
            else{
                printf(".");
            }
            printf("Variable: %d, Operador: %c, Operando: %d\n",variable_compartida,argumento->operador,argumento->operando);
            suma+=random_suma;
            for(i=x;i<suma;i++){
                variable_compartida+=argumento->operando;
                printf("---(%d)---\n",variable_compartida);
            }
            x=suma; //Se usa para llevar una cuenta de las operaciones realizada, para el for
            break;
        //Las mismas explicaciones dabas anteriormente se aplican a los siguientes casos
        case '-':
            printf("\n\t--Resta %d--\n",r);
            int j;
            int random_resta = 1 + rand() %2;
            cont_resta[r]=random_resta;
            printf("\nProceso: %li\n", pthread_self());
            r++;
            if(cont_resta[0]==1&&cont_resta[1]==1&&cont_resta[2]==1){
                random_resta=3;
            }
            else if(cont_resta[0]==1&&cont_resta[1]==2&&cont_resta[2]==1){
                random_resta=2;
            }
            else if(cont_resta[0]==2&&cont_resta[1]==1&&cont_resta[2]==1){
                random_resta=2;
            }
            else if(cont_resta[0]==2&&cont_resta[1]==2&&cont_resta[2]==2){
                random_resta=1;
            }
            else{
                printf(".");
            }
            printf("Variable: %d, Operador: %c, Operando: %d\n",variable_compartida,argumento->operador,argumento->operando);
            resta+=random_resta;
            for(j=y;j<resta;j++){
                variable_compartida-=argumento->operando;
                printf("---(%d)---\n",variable_compartida);
            }
            y=resta;
            break;
        case '*':
            printf("\n\t--Multi %d--\n",m);
            int k;
            int random_multi = 1 + rand() %2;
            cont_multi[m]=random_multi;
            printf("\nProceso: %li\n", pthread_self());
            m++;
            if(cont_multi[0]==1&&cont_multi[1]==1&&cont_multi[2]==1){
                random_multi=3;
            }
            else if(cont_multi[0]==1&&cont_multi[1]==2&&cont_multi[2]==1){
                random_multi=2;
            }
            else if(cont_multi[0]==2&&cont_multi[1]==1&&cont_multi[2]==1){
                random_multi=2;
            }
            else if(cont_multi[0]==2&&cont_multi[1]==2&&cont_multi[2]==2){
                random_multi=1;
            }
            else{
                printf(".");
            }
            printf("Variable: %d, Operador: %c, Operando: %d\n",variable_compartida,argumento->operador,argumento->operando);
            multi+=random_multi;
            for(k=z;k<multi;k++){
                variable_compartida*=argumento->operando;
                printf("---(%d)---\n",variable_compartida);
            }
            z=multi;
            break;
        case '/':
            printf("\n\t--Div %d--\n",d);
            int l;
            int random_div = 1 + rand() %2;
            cont_div[d]=random_div;
            printf("\nProceso: %li\n", pthread_self());
            d++;
            if(cont_div[0]==1&&cont_div[1]==1&&cont_div[2]==1){
                random_div=3;
            }
            else if(cont_div[0]==1&&cont_div[1]==2&&cont_div[2]==1){
                random_div=2;
            }
            else if(cont_div[0]==2&&cont_div[1]==1&&cont_div[2]==1){
                random_div=2;
            }
            else if(cont_div[0]==2&&cont_div[1]==2&&cont_div[2]==2){
                random_div=1;
            }
            else{
                printf(".");
            }
            printf("Variable: %d, Operador: %c, Operando: %d\n",variable_compartida,argumento->operador,argumento->operando);
            divi+=random_div;
            for(l=w;l<divi;l++){
                variable_compartida/=argumento->operando;
                printf("---(%d)---\n",variable_compartida);
            }
            w=divi;
            break;
    
    }
    printf("La variable ha sido modificada!\nNuevo valor de la variable: %i\n",variable_compartida);
    pthread_mutex_unlock(&mutex); //Una vez terminado la operacion, se desbloquea el mutex para que otro proceso realice su operacion correspondiente
    pthread_exit("\nhijo retorna gracias. \n");
}