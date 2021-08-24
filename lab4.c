#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 4

//varáveis globais
int controle = 0;//é a variável que determina o wait
pthread_mutex_t mutex;
pthread_cond_t cond_a; //necessário para "Seja bem vindo!" ser impresso primeiro
pthread_cond_t cond_b; //necessário para "Volte sempre!" ser impresso por último

//função "Seja bem vindo!"
void * a(void * arg){
  pthread_mutex_lock(&mutex);
  puts("Seja bem vindo!");
  controle++;
  pthread_cond_broadcast(&cond_a);
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
}

//função “Fique a vontade.”
void * b(void * arg){
  pthread_mutex_lock(&mutex);
  if(controle==0) pthread_cond_wait(&cond_a,&mutex); //nesse caso, não é necessário o while
  puts("Fique a vontade.");
  controle++;
  pthread_cond_signal(&cond_b);
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
}

//função “Sente-se por favor.”
void * c(void * arg){
  pthread_mutex_lock(&mutex);
  if(controle==0) pthread_cond_wait(&cond_a,&mutex);
  puts("Sente-se por favor.");
  controle++;
  pthread_cond_signal(&cond_b);
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
}

//função “Volte sempre!”
void * d  (void * arg){
  pthread_mutex_lock(&mutex);
  while(controle!=3) pthread_cond_wait(&cond_b,&mutex);
  puts("Volte sempre!");
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
}

//fluxo principal
int main(void){

  pthread_t threads[NTHREADS];

  //criação das threads
  pthread_create(&threads[0],NULL,a,NULL);
  pthread_create(&threads[1],NULL,b,NULL);
  pthread_create(&threads[2],NULL,c,NULL);
  pthread_create(&threads[3],NULL,d,NULL);

  //espera as threads acabarem
  for (int i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  //desaloca Threads
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond_a);
  pthread_cond_destroy(&cond_b);

return 0;
}
