#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <stdio.h>

#define MAX_SLEEP_TIME 3
#define NUM_OF_STUDENTS 4
#define NUM_OF_HELPS 2
#define NUM_OF_SEATS 2


/*mutex declarations*/
pthread_mutex_t mutex_lock;

/*semaphore declarations*/
sem_t students_sem; //ta waits for student to show up, student notifies TA upon arrival
sem_t ta_sem; //student waits for ta to help, ta notifies student he is ready

/*the number of waiting students*/
int waiting_students = 0;
int ta_asleep = 0;
/*seeds for each thread*/
int seeds[5] = {12315, 36462, 63252, 87273, 21573};

pthread_t student_threads[NUM_OF_STUDENTS];
pthread_t ta_thread_ptr;
void *student_thread(void *num);
void *ta_thread(void *staaanddyyyy);

int main(void){
printf("CS149 SleepingTA from Malik Khalil");
pthread_mutex_init(&mutex_lock, NULL);
sem_init(&students_sem, 0, 0);
sem_init(&ta_sem, 0, 1);
int *s_id;
int i;
pthread_create(&ta_thread_ptr, NULL, ta_thread, NULL);
for (i = 0; i < NUM_OF_STUDENTS; i++){
	s_id = i;
	pthread_create(&student_threads[i], NULL, student_thread, s_id);
}
for (i = 0; i < NUM_OF_STUDENTS; i++){
	pthread_join(student_threads[i], NULL);
}
/* clean up resources */
pthread_cancel(ta_thread_ptr);
sem_destroy(&students_sem);
sem_destroy(&ta_sem);

printf("\n");
return 0;

}

void *ta_thread(void *staaanddyyyy){
	int ta_seed = 4;
	int rand_wait = (rand_r(&seeds[ta_seed]) % MAX_SLEEP_TIME) + 1;
		while(1){
	rand_wait = (rand_r(&seeds[ta_seed]) % MAX_SLEEP_TIME) + 1;
	sem_wait(&students_sem);
			while (waiting_students > 0){
		rand_wait = (rand_r(&seeds[ta_seed]) % MAX_SLEEP_TIME) + 1;
		sem_post(&ta_sem);
		pthread_mutex_lock(&mutex_lock);
		waiting_students--;
		pthread_mutex_unlock(&mutex_lock);
		printf("\nHelping a student for %d seconds, # of waiting students = %d", 
			rand_wait, waiting_students);
		sleep(rand_wait);
		}

	}

}

void *student_thread(void *num){

	int helps = 0;
	int student_number = (int *) num;
	int rand_wait = (rand_r(&seeds[student_number]) % MAX_SLEEP_TIME) + 1;
	printf("\n\tStudent %d programming for %d seconds.", student_number, rand_wait);
	sleep(rand_wait);

while (helps < NUM_OF_HELPS){
	pthread_mutex_lock(&mutex_lock);

	if (waiting_students < NUM_OF_SEATS){
		waiting_students++;
		pthread_mutex_unlock(&mutex_lock);
		sem_post(&students_sem);
		printf("\n\t\tStudent %d takes a seat, # of waiting students = %d", student_number, 
			waiting_students);
		sem_wait(&ta_sem);
		printf("\nStudent %d receiving help", student_number);
		rand_wait = (rand_r(&seeds[student_number]) % MAX_SLEEP_TIME) + 1;
		sleep(rand_wait);
		helps++;
	}
	else{
	pthread_mutex_unlock(&mutex_lock);
	rand_wait = (rand_r(&seeds[student_number]) % MAX_SLEEP_TIME) + 1;
	printf("\n\t\t\tStudent %d will try later", student_number);
	printf("\n\tStudent %d programming for %d seconds.", student_number, rand_wait);
	sleep(rand_wait);
	}
}
pthread_exit(NULL);
}