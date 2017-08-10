#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>

int main(int argc, char ** argv){
	
	if (argc < 6) {

		printf("./pc <num_hilos> <tiempo_prod> <num_hilos_cons> <tiempo_cons> <tam_cola>
<total_items> \n");

		exit(1);
	}

	int productores = argv[1];
	int consumidores = argv[3];
	int tamCola = argv[5];
	int tiempoConsumo = argv[4];
	int tiempoProduccion = argv[2];

	printf("");
	pthread_t * listaConsumidores = (pthread_t *) malloc(sizeof(pthread_t)*hilos);
	pthread_t * listaProductores = (pthread_t *) malloc(sizeof(pthread_t)*hilos);

	for (int j = 0; j < productores; j ++) {		

		int statusHilo = pthread_create(&listaConsumidores[j], NULL, funcion, (void *)estructura);


		if (statusHilo < 0) {

			fprintf(stderr, "Error al crear el hilo\n");

			exit(-1);	

		}


		contador++;

	}
	
}
