#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define GRID_SIZE 9

int grid[GRID_SIZE][GRID_SIZE] = {
		{6, 5, 3, 1, 2, 8, 7, 9, 4},
		{1, 7, 4, 3, 5, 9, 6, 8, 2},
		{9, 2, 8, 4, 6, 7, 5, 3, 1},
		{2, 8, 6, 5, 1, 4, 3, 7, 9},
		{3, 9, 1, 7, 8, 2, 4, 5, 6},
		{5, 4, 7, 6, 9, 3, 2, 1, 8},
		{8, 6, 5, 2, 3, 1, 9, 4, 7},
		{4, 1, 2, 9, 7, 5, 8, 6, 3},
		{7, 3, 9, 8, 4, 6, 1, 2, 5}};
int valid_sudoku = 1; //default value = True or 1

int main(){

	printf("CS149 Sudoku from Malik Khalil\n");
	int i, j;
	for (i = 0; i < GRID_SIZE; i++){
		for (j = 0; j < GRID_SIZE; j++){
			printf("%d",grid[i][j]);
			if (j != 8){printf(", ");}
		}
		printf("\n");
	}
	printf("Spawning 9 worker column threads...\n9 worker row threads...\n9 submatrix threads...\n");
	sleep(2.5);
	/* structure for passing data to threads*/
	typedef struct 
	{
		int row;
		int column;
		//int (*matrix)[GRID_SIZE];
	} parameters;

	/* tests the column that is passed in. Returns 1 if satisfies Sudoku, 0 if it doesn't*/
	void *test_column(void *ds){
		parameters *data = (parameters *)ds;
		int column = data->column;
		int i;
		int array[GRID_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
		//int (*grid)[GRID_SIZE] = data->matrix;
		int *result = malloc(sizeof(int));
		*result = 1;
		for (i = 0; i < GRID_SIZE; i++){
			int current = grid[i][column];
			array[current-1] = 1;
		}
		for (i = 0; i < GRID_SIZE; i++){
			if (array[i] == 0){
				*result = 0;
			}
		}
		pthread_exit((void*)*result);
	}

	/* tests the row that is passed in. Returns 1 if satisfies Sudoku, 0 if it doesn't*/
	void *test_row(void *ds){
		parameters *data = (parameters *)ds;
		int row = data->row;
		int j;
		int array[GRID_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
		//int (*grid)[GRID_SIZE] = data->matrix;
		int *result = malloc(sizeof(int));
		*result = 1;
		for (j = 0; j < GRID_SIZE; j++){
			int current = grid[row][j];
			array[current-1] = 1;
		}
		for (j = 0; j < GRID_SIZE; j++){
			if (array[j] == 0){
				*result = 0;
			}
		}
		pthread_exit((void*)*result);
	}

	/* tests a 3x3 sub matrix. Returns 1 if satisfies Sudoku, 0 if it doesn't*/
	void *test_sub_matrix(void *ds){
		parameters *data = (parameters *)ds;
		int row = data->row;
		int col = data->column;
		int i;
		int j;
		int array[GRID_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
		//int (*grid)[GRID_SIZE] = data->matrix;
		int *result = malloc(sizeof(int));
		*result = 1;
		for (i = row; i < row+3; i++){
			for (j = col; j < col+3; j++){
				int current =  grid[i][j];
				array[current-1] = 1;
			}
		}
		for (j = 0; j < GRID_SIZE; j++){
			if (array[j] == 0){
				*result = 0;
			}
		}
		pthread_exit((void*)*result);
	}
	/*erase this later
	int row_result = -1;
	int col_result = -1;
	pthread_t row_thread;
	pthread_t col_thread;
	pthread_create(&row_thread, NULL, test_row, data);
	pthread_join(row_thread, (void**)&row_result);
	printf("result for row 1: %d", row_result);
	*/

	/*Array for rows and cols, see if the Sudoku is valid*
	Worker threads populate these*/
	pthread_t row_checkers[GRID_SIZE];
	pthread_t col_checkers[GRID_SIZE];
	pthread_t sub_matrix_checkers[GRID_SIZE]; 

	
	int valid_rows[GRID_SIZE] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	int valid_cols[GRID_SIZE] = {1, 1, 1, 1, 1, 1, 1, 1, 1}; 
	int valid_sub_matrices[GRID_SIZE] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	

	int row, col, sub_matrix_i, sub_matrix_j;
	/* Spawn workers to check each row*/
	parameters* structs[GRID_SIZE*3];
	int current_index= 0;
	for (row = 0; row < GRID_SIZE; row++) 
	{
		parameters *data = malloc(sizeof(parameters));
		data->row = row;
		data->column = 0;
		structs[current_index] = data;
		current_index++;
		pthread_create(&row_checkers[row], NULL, test_row, data);
	}
	/* Spawn workers to check each column*/
	for (col = 0; col < GRID_SIZE; col++){ 
		parameters *data = malloc(sizeof(parameters));
		data->row = 0;
		data->column = col;
		structs[current_index] = data;
		current_index++;
		pthread_create(&col_checkers[col], NULL, test_column, data);
	}
	/* Spawn workers to check each sub matrix*/
	int index = 0;
	for (sub_matrix_i = 0; sub_matrix_i < 3; sub_matrix_i++){
		for (sub_matrix_j = 0; sub_matrix_j < 3; sub_matrix_j++){
			parameters *data = malloc(sizeof(parameters));
			data->row = sub_matrix_i*3;
			data->column = sub_matrix_j*3;
			structs[current_index] = data;
			current_index++;
			pthread_create(&sub_matrix_checkers[index], NULL, test_sub_matrix, data);
			index++;
		}
	}

	/*Join row workers with main thread*/
	for (row = 0; row < GRID_SIZE; row++){ 
		int row_result = 1;
		pthread_join(row_checkers[row], (void**) &row_result);
		if (row_result == 0){valid_sudoku = 0;}
		valid_rows[row] = row_result;
	}
	/*Join column workers with main thread*/
	for (col = 0; col < GRID_SIZE; col++){ 
		int col_result = 1;
		pthread_join(col_checkers[col], (void**) &col_result);
		valid_cols[col] = col_result;
	}
	/*Join sub matrix workers with main thread*/
	for (sub_matrix_i = 0; sub_matrix_i < GRID_SIZE; sub_matrix_i++){
		int sub_matrix_result = 1;
		pthread_join(sub_matrix_checkers[sub_matrix_i], (void**) &sub_matrix_result);
		valid_sub_matrices[sub_matrix_i] = sub_matrix_result;
	}
	int idx;
	for (idx = 0; idx < GRID_SIZE*3; idx++){
		parameters* current_data = structs[idx];
		free(current_data);
	}
	//IGNORE... JUST PRINTING...
	int k;
	printf("\n");
	for(k = 0; k < GRID_SIZE; k++){
		printf("Row %d, result: %d\n",k, valid_rows[k]);
		printf("Column %d, result: %d\n",k, valid_cols[k]);
		printf("SubMatrix %d, result: %d\n",k, valid_sub_matrices[k]);
		if (valid_rows[k] == 0 || valid_cols[k] == 0 || valid_sub_matrices[k] == 0){
			valid_sudoku = 0;
		}
	}
	if (valid_sudoku == 0) {printf("\nValid Sudoku: %d, FALSE, the grid is not a good solution.\n", valid_sudoku);}
	else if (valid_sudoku == 1) {printf("\nValid Sudoku: %d, TRUE, the grid is a good solution.\n", valid_sudoku);}
}