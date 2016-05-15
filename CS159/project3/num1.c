#include <stdio.h>
#include <omp.h>
int main(){
		#pragma omp parallel
		{
			printf(" Hello ");
		}
		printf("\n\n GoodBye - Team Destroyed - Exiting Program \n\n");
}