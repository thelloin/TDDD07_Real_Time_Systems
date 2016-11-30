/**
 * @file	scheduler.c
 * @author  Eriks Zaharans and Massimiiliano Raciti
 * @date    1 Jul 2013
 *
 * @section DESCRIPTION
 *
 * Cyclic executive scheduler library.
 */

/* -- Includes -- */
/* system libraries */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
/* project libraries */
#include "scheduler.h"
#include "task.h"
#include "timelib.h"
#include <time.h>
#include <math.h>
/* -- Defines -- */

/* -- Functions -- */

/**
 * Initialize cyclic executive scheduler
 * @param minor Minor cycle in miliseconds (ms)
 * @return Pointer to scheduler structure
 */
scheduler_t *scheduler_init(void)
{
	// Allocate memory for Scheduler structure
	scheduler_t *ces = (scheduler_t *) malloc(sizeof(scheduler_t));

	return ces;
}

/**
 * Deinitialize cyclic executive scheduler
 * @param ces Pointer to scheduler structure
 * @return Void
 */
void scheduler_destroy(scheduler_t *ces)
{
	// Free memory
	free(ces);
}

/**
 * Start scheduler
 * @param ces Pointer to scheduler structure
 * @return Void
 */
void scheduler_start(scheduler_t *ces)
{
	// Set timers
	timelib_timer_set(&ces->tv_started);
	timelib_timer_set(&ces->tv_cycle);
}

/**
 * Wait (sleep) till end of minor cycle
 * @param ces Pointer to scheduler structure
 * @return Void
 */
void scheduler_wait_for_timer(scheduler_t *ces)
{
	int sleep_time; // Sleep time in microseconds

	// Calculate time till end of the minor cycle
	sleep_time = (ces->minor * 1000) - (int)(timelib_timer_get(ces->tv_cycle) * 1000);
//	printf(timelib_timer_get);
	//printf("sleep time %d \n", sleep_time);
	/*printf("ces minor %d \n", ces->minor);
	printf("ces minor*1000 %d \n", ces->minor * 1000);
	printf("tv_cycle %d \n", (int)timelib_timer_get(ces->tv_cycle));
	printf("tv_cycle*1000 %d \n", (int)timelib_timer_get(ces->tv_cycle) *1000);*/

	// Add minor cycle period to timer
	timelib_timer_add_ms(&ces->tv_cycle, ces->minor);
	//printf("tv_cycle after timelib %d \n", (int)timelib_timer_get(ces->tv_cycle));
	// Check for overrun and execute sleep only if there is no
	if(sleep_time > 0)
	{
		// Go to sleep (multipy with 1000 to get miliseconds)
		usleep(sleep_time);
	}
}

/**
 * Execute task
 * @param ces Pointer to scheduler structure
 * @param task_id Task ID
 * @return Void
 */
void scheduler_exec_task(scheduler_t *ces, int task_id)
{
	switch(task_id)
	{
	// Mission
	case s_TASK_MISSION_ID :
		task_mission();
		break;
	// Navigate
	case s_TASK_NAVIGATE_ID :
		task_navigate();
		break;
	// Control
	case s_TASK_CONTROL_ID :
		task_control();
		break;
	// Refine
	case s_TASK_REFINE_ID :
		task_refine();
		break;
	// Report
	case s_TASK_REPORT_ID :
		task_report();
		break;
	// Communicate
	case s_TASK_COMMUNICATE_ID :
		task_communicate();
		break;
	// Collision detection
	case s_TASK_AVOID_ID :
		task_avoid();
		break;
	// Other
	default :
		// Do nothing
		break;
	}
}




void minor_cycle_1(scheduler_t *ces) {
  scheduler_exec_task(ces, 6);
  scheduler_exec_task(ces, 7);

  
}

void minor_cycle_2(scheduler_t *ces) {
  scheduler_exec_task(ces, 1);
  scheduler_exec_task(ces, 2);
  scheduler_exec_task(ces, 3);
  scheduler_exec_task(ces, 7);
  scheduler_exec_task(ces, 4);
  scheduler_exec_task(ces, 5);  
}

void minor_cycle_34567(scheduler_t *ces) {
  scheduler_exec_task(ces, 7);
  scheduler_exec_task(ces, 4);
  scheduler_exec_task(ces, 5);
}

void minor_cycle_8(scheduler_t *ces) {
  scheduler_exec_task(ces, 2);
  scheduler_exec_task(ces, 3);
  scheduler_exec_task(ces, 7);
  scheduler_exec_task(ces, 4);
  scheduler_exec_task(ces, 5);

}




/**
 * Run scheduler
 * @param ces Pointer to scheduler structure
 * @return Void
 */
void scheduler_run(scheduler_t *ces)
{

  

  /* here, do your time-consuming job */



  //timeval timer;
  //  timelib_timer_set(&timer);

 
  //struct timeval timer;
  //int groupNumber = 3;

  
  
  //timelib_timer_set(&timer);
  ces->minor = 125;
  scheduler_wait_for_timeslot(groupNumber);
 
  scheduler_start(ces);

  while(1) {

    
    minor_cycle_1(ces);
    scheduler_wait_for_timer(ces);
    
    minor_cycle_2(ces);
    scheduler_wait_for_timer(ces);
    
    minor_cycle_34567(ces);
    scheduler_wait_for_timer(ces);
    
    minor_cycle_34567(ces);
    scheduler_wait_for_timer(ces);
    
    minor_cycle_34567(ces);
    scheduler_wait_for_timer(ces);
    
    minor_cycle_34567(ces);
    scheduler_wait_for_timer(ces);
    
    minor_cycle_34567(ces);
    scheduler_wait_for_timer(ces);
    
    minor_cycle_8(ces);
    scheduler_wait_for_timer(ces);


  }




}


