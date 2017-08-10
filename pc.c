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
