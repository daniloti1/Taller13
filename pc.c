#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t miMutex;
pthread_cond_t cv_c = PTHREAD_COND_INITIALIZER;
pthread_cond_t cv_p = PTHREAD_COND_INITIALIZER;

typedef struct _apy {
	int * cola;
	int tiempoCons;
	int tiempoProd;
	int indice;
	int tamCola;
	int * total;
}apy;


void * funcionProd(void * est) {
	apy * estructura = (apy *) est;	
	while ((*(estructura->total) > 0)) {
	
		pthread_mutex_lock(&miMutex);
		while(!(*(estructura->cola) < estructura->tamCola)) {
			pthread_cond_wait(&cv_p, &miMutex);
		}	

		usleep(estructura->tiempoProd);
		*(estructura->cola) = *(estructura->cola) + 1; 
		//printf("entra al hilo %d\n",*(estructura->cola));
		*(estructura->total) = *(estructura->total) -1;
		pthread_cond_broadcast(&cv_c);
		if (*(estructura->total) <= 0) {
			pthread_cond_broadcast(&cv_c);
		}
		pthread_mutex_unlock(&miMutex);

		printf("Productor %d ha producido 1 item, tamaño de la cola = %d\n",estructura->indice, *(estructura->cola));
	}
	return NULL;
}

void * funcionCons(void * est) {
	apy * estructura = (apy *) est;
	pthread_mutex_lock(&miMutex);
	while(!(*(estructura->cola) > 0)) {
		pthread_cond_wait(&cv_c, &miMutex);
	}
	pthread_mutex_unlock(&miMutex);
	while ((*(estructura->cola) > 0)) {
		
		pthread_mutex_lock(&miMutex);
		while(!(*(estructura->cola) > 0)) {
			pthread_cond_wait(&cv_c, &miMutex);
		}
		usleep(estructura->tiempoCons);	
		*(estructura->cola) = *(estructura->cola) - 1;
		pthread_cond_broadcast(&cv_p);
		pthread_mutex_unlock(&miMutex);

		printf("Consumidor %d ha consumido 1 item, tamaño de la cola = %d\n",estructura->indice, *(estructura->cola));
	}

	return NULL;
}


int main(int argc, char ** argv){
	
	if (argc < 6) {

		printf("./pc <num_hilos> <tiempo_prod> <num_hilos_cons> <tiempo_cons> <tam_cola> <total_items> \n");

		exit(1);
	}

	int productores = atoi(argv[1]);
	int consumidores = atoi(argv[3]);
	int tamCola = atoi(argv[5]);
	double tiempoConsumo = atoi(argv[4]);
	double tiempoProduccion = atoi(argv[2]);
	int items = atoi(argv[6]);

	pthread_t * listaConsumidores = (pthread_t *) malloc(sizeof(pthread_t)*productores);
	pthread_t * listaProductores = (pthread_t *) malloc(sizeof(pthread_t)*consumidores);

	printf("Numero de productores: %d\n", productores);
	printf("Numero de consumidores: %d\n", consumidores);
	printf("Tamaño de cola: %d\n", tamCola);
	printf("Tiempo de consumo: %f\n", tiempoConsumo);
	printf("Tiempo de produccion: %f\n", tiempoProduccion);
	printf("Total de items a producir: %d\n", items);	

	int * cola = (int*)malloc(sizeof(int));
	

	for (int j = 0; j < productores; j ++) {

		apy * estructura = (apy*)malloc(sizeof(apy));	
		estructura->cola = cola;
		estructura->tiempoCons = tiempoConsumo;
		estructura->tiempoProd = tiempoProduccion;
		estructura->indice = j+1;
		estructura->tamCola = tamCola;
		estructura->total = &items;

		int statusHilo = pthread_create(&listaProductores[j], NULL, funcionProd, (void*) estructura);


		if (statusHilo < 0) {

			fprintf(stderr, "Error al crear el hilo\n");

			exit(-1);	

		}
	}

	for (int i = 0; i < consumidores; i ++) {

		apy * estructura = (apy*)malloc(sizeof(apy));	
		estructura->cola = cola;
		estructura->tiempoCons = tiempoConsumo;
		estructura->tiempoProd = tiempoProduccion;
		estructura->indice = i+1;
		estructura->tamCola = tamCola;
		estructura->total = &items;

		int statusHilo = pthread_create(&listaConsumidores[i], NULL, funcionCons, (void*) estructura);


		if (statusHilo < 0) {

			fprintf(stderr, "Error al crear el hilo\n");

			exit(-1);	

		}
	}

	
	for (int k = 0; k < consumidores; k++) {

		int status = pthread_join(listaConsumidores[k], NULL);
	
		if (status < 0) {

			fprintf(stderr, "Error al crear el hilo\n");

			exit(-1);	

		}

	}

	for (int k = 0; k < productores; k++) {


		int status = pthread_join(listaProductores[k], NULL);
	
		if (status < 0) {

			fprintf(stderr, "Error al crear el hilo\n");

			exit(-1);	

		}

	}


	
}
