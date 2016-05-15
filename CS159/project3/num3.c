#include <stdio.h>
#include <omp.h>
int main(){
	omp_set_num_threads(7);
		#pragma omp parallel
		{
			printf(" Hello from thread = %d ", omp_get_thread_num());
		}
		printf("\n\n GoodBye - Team Destroyed - Exiting Program \n\n");
}