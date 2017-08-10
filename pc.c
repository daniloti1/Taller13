#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t miMutex;

typedef struct _apy {
	int * cola;
	int tiempoCons;
	int tiempoProd;
	int indice;
}apy;


void * funcionProd(void * est) {
	apy * estructura = (apy *) est;
	usleep(estructura->tiempoProd);	
	pthread_mutex_lock(&miMutex);
	estructura->cola++;
	pthread_mutex_unlock(&miMutex);
	printf("Productor %d ha producido 1 item tamaño de la cola = %d",estructura->indice, );
	
	return NULL;
}

void * funcionCons(void * est) {
	apy * estructura = (apy *) est;
	usleep(estructura->tiempoCons);	
	pthread_mutex_lock(&miMutex);
	estructura->cola--;
	pthread_mutex_unlock(&miMutex);
	printf("Consumidor %d ha consumido 1 item tamaño de la cola = %d",estructura->indice, );

	return NULL;
}


int main(int argc, char ** argv){
	
	if (argc < 6) {

		printf("./pc <num_hilos> <tiempo_prod> <num_hilos_cons> <tiempo_cons> <tam_cola>
<total_items> \n");

		exit(1);
	}

	int productores = argv[1];
	int consumidores = argv[3];
	int tamCola = argv[5];
	double tiempoConsumo = argv[4];
	double tiempoProduccion = argv[2];
	int items = argv[6];

	pthread_t * listaConsumidores = (pthread_t *) malloc(sizeof(pthread_t)*productores);
	pthread_t * listaProductores = (pthread_t *) malloc(sizeof(pthread_t)*consumidores);

	printf("Numero de productores: %d\n", productores);
	printf("Numero de consumidores: %d\n", consumidores);
	printf("Tamaño de cola: %d\n", tamCola);
	printf("Tiempo de consumo: %d\n", tiempoConsumo);
	printf("Tiempo de produccion: %d\n", tiempoProduccion);
	printf("Total de items a producir: %d\n", items);	

	int * cola = (int*)malloc(sizeof(int));
	

	for (int j = 0; j < productores; j ++) {

		apy * estructura = (apy*)malloc(sizeof(apy));	
		estructuctura->cola = cola;
		estructuctura->tiempoCons = tiempoConsumo;
		estructuctura->tiempoProd = tiempoProduccion;
		estructuctura->indice = j+1;

		int statusHilo = pthread_create(&listaConsumidores[j], NULL, funcionProd, (void*) estructura);


		if (statusHilo < 0) {

			fprintf(stderr, "Error al crear el hilo\n");

			exit(-1);	

		}


	}
	
}
