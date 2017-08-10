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

	pthread_t * listaConsumidores = (pthread_t *) malloc(sizeof(pthread_t)*hilos);
	pthread_t * listaProductores = (pthread_t *) malloc(sizeof(pthread_t)*hilos);

	int productores = argv[1];
	int consumidores = argv[3];
	int tamCola = argv[5];
	double tiempoConsumo = argv[4];
	double tiempoProduccion = argv[2];
	int items = argv[6];

	printf("Numero de productores: %d\n", productores);
	printf("Numero de consumidores: %d\n", consumidores);
	printf("Tamaño de cola: %d\n", tamCola);
	printf("Tiempo de consumo: %d\n", tiempoConsumo);
	printf("Tiempo de produccion: %d\n", tiempoProduccion);
	printf("Total de items a producir: %d\n", items);	

	int cola = 0;
	

	for (int j = 0; j < productores; j ++) {		

		int statusHilo = pthread_create(&listaConsumidores[j], NULL, funcion, (void *)estructura);


		if (statusHilo < 0) {

			fprintf(stderr, "Error al crear el hilo\n");

			exit(-1);	

		}


		contador++;

	}
	
}
