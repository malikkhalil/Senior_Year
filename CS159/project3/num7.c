#include <stdio.h>
#include <omp.h>
int main(){
		int i;
		int sum = 0;
	omp_set_num_threads(8);
			#pragma omp parallel for reduction(+: sum) private(i)
			for (i = 0; i < 10; i++)
			{
				sum = sum + i;
			printf(" Hello from thread number: %d  Iteration: %d Local Sum: %d \n", omp_get_thread_num(), i, sum);
			}
		printf("\n\n GoodBye - Team Destroyed - Exiting Program \n\n");
}