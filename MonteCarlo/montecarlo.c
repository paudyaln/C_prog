/******************************************************
*FILENAME: montecarlo.c
*DES:
*	Generating value of Pi
*	Monte Carlo Technique, uses randomization
*	Multithreading version of algorithm
*
*	Creates seperate thread to generate random (x,y) cordinates
*		-and count the cordinates that fall inside the radius of circle
*
*Author: Nischal Paudyal
*2019
**********************************************************/

#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

double x,y;
int count;
double pi;
void *runner(void *param); /* threads call this function */

int main(int argc, char *argv[])
{
	int npoints;	/*number of points to be generated*/
	pthread_t thread_pi;	 /* the thread identifier */
	pthread_attr_t attr; /* set of thread attributes */

	if (argc != 2) {
    fprintf(stderr,"usage: a.out <integer value> \n");
    return -1;
	}

	if (atoi(argv[1]) < 0) {
    fprintf(stderr,"%d must be >= 0 \n",atoi(argv[1]));
    return -1;
  	}

	/*convert character string to interger*/
	npoints = atoi(argv[1]);

  	/* get the default attributes */
 	pthread_attr_init(&attr);

  	/* create the thread */
  	if(pthread_create(&thread_pi,&attr,runner, npoints)){
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

  	/* wait for the thread to exit */
  	if(pthread_join(thread_pi,NULL)){
		fprintf(stderr,"Error joining thread\n");
		return 2;
	}

	/*calculate pi in the parent thread*/
	pi = (double)(4 * count)/npoints;
	printf("pi = %f", pi);
}

/* The thread will begin control in this function
* counts the number of coordinate that falls inside the cirle of radius 1.
*/
void *runner(void *param)
{
	count = 0;
	double radius = 0;
	srand(time(NULL));	/*set SEED*/

  	for (int i = 1; i <= param; i++){
		x = (double)rand()/(double)((unsigned)RAND_MAX+1);
		y = (double)rand()/(double)((unsigned)RAND_MAX+1);
		radius = x*x + y*y;
		//printf("radius = %f\n", radius);
		if(radius<=1){
			count++;
			//printf("\t\tx: %f\t      , y: %f\t     , count: %d\n", x, y, count);
		}
	}
	/*exit thread_pi*/
  	pthread_exit(0);
}
