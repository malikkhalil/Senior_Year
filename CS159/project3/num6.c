#include <stdio.h>
#include <omp.h>
int main(){
		int i;
		int sum = 0;
		int NTHREADS = 8;
		int COUNT = 10;
	omp_set_num_threads(NTHREADS);
			#pragma omp parallel for private(sum) 
			for (i = 0; i < COUNT; i++)
			{
				sum = sum + i;
			printf(" Hello from thread number: %d  Iteration: %d Local Sum: %d \n", omp_get_thread_num(), i, sum);
			}

		printf("\n\n GoodBye - Team Destroyed - Exiting Program \n\n");
}