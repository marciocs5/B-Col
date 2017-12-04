/*
 * Timer.h
 *
 *  Created on: 26/06/2014
 *      Author: santosma
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <sys/time.h>
#include <unistd.h>

//represents a clock for the problems
class Timer {
private:
	//The initial time
	struct timeval  clockinit;

	//the final time
	struct timeval  clockend;

	//the time zone
	struct timezone tz;

	//
	float seconds;
public:
	/*
	 * The basic constructor
	 * */
	Timer();

	/*
	 * The basic destructor
	 * */
	virtual ~Timer();

	/*
	 * Initializes the clock
	 * */
	void start();

	/*
	 * Pause the clock and return the elapsed time so far.
	 *
	 * @return the elapsed time so far.
	 * */
	float pause();

	/*
	 * Stop the clock and return the elapsed time so far.
	 *
	 * @return the elapsed time so far.
	 * */
	float stop();
};

#endif /* TIMER_H_ */
