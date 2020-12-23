#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>

/* O codigo a seguir foi escrito por Nicolas Bueno. Grupo: SISTEMATICOS 
 * (Nicolas Bueno, RA 222904)
 * (Leonardo Vincius RA 239287)
 * Este codigo foi desenvolvido como tarefa de programacao para o trabalho final da disciplina 
 * Sistemas Operacionais na Faculdade de Tecnologia da Unicamp durante o segundo semestre de 2020, 
 * e tem como objetivo exercitar os conceitos de programacao multithread e semaforos visto em aula. 
 * Para compilar: gcc -pthread HSO.c -o arquivo_executavel
 * O programa deve imprimir a molecula H2 S 04 (HHSOOOO) um numero x de vezes, de acordo com input
 * do usuario.
 */

/* declara semaforo mutex (mutual exclusion)
* declara threads a serem executadas, responsaveis por imprimir os atomos da molecula (H,S,O)
*/ 
sem_t mutex;  
pthread_t thdH, thdS, thdO;

//A funcao abaixo imprime o atomo H com sua thread propria, inclui sinais para controlar semaforo.
void *thr_H() { 
	int h = 0;
	for(;;) {
		sem_wait(&mutex);            
		printf("H");
		sem_post(&mutex);
		h++;
		sleep(2); 
		if (h == 2) {
			break;
			}
		}
	pthread_exit(NULL);
	}

//A funcao abaixo imprime o atomo S com sua thread propria, inclui sinais para controlar semaforo.	
void *thr_S() { 
	int s = 0;
	for(;;) {		
		sem_wait(&mutex);
		printf("S");
		sem_post(&mutex);
		s++;		
		sleep(2); 
		if (s == 1) {
			break;
			}
		}
	pthread_exit(NULL);
	}

//A funcao abaixo imprime o atomo O com sua thread propria, inclui sinais para controlar semaforo.	
void *thr_O() { 
	int o = 0;
	for(;;) {		
		sem_wait(&mutex);
		printf("O");
		sem_post(&mutex);
		o++;		
		sleep(2);
		if(o == 4) {
			break;
			}
		 }
	pthread_exit(NULL);
	}


/* A funcao abaixo e responsavel por criar as threads chamando as funcoes que imprimem cada atomo respectivamente. 
 * @sem_init inicia o semaforo mutex.
 * @pthread_create cria uma thread.
 * @pthread_join bloqueia o fluxo ate que determinada thread tenha sido executada.
 * @sem_destroy termina o semaforo.
 */		
void *Imprime_molecula() {
	sem_init(&mutex, 0,1);
	pthread_create (&thdH,NULL, (void*) thr_H, NULL);
	pthread_join(thdH,NULL);
	pthread_create (&thdS,NULL, (void*) thr_S, NULL);
	pthread_join(thdS,NULL);
	pthread_create (&thdO,NULL, (void*) thr_O, NULL);
	pthread_join(thdO,NULL);
	printf("\n");
	sem_destroy (&mutex);
	return(0);
	}

/*  A funcao principal e responsavel por pegar o input do usuario e chamar a funcao 
 *  Imprime_molecula k (input) vezes.
 */


int main (int argc, char* argv[]) { 
	int k = 0;
	int j;
	printf("insira o  numero de repeticoes \n");
	scanf("%d", &k);
	for (j=0;j<k;j++) {
		Imprime_molecula();
		}
	return(0);
	}
