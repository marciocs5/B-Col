/*
 * Timer.cpp
 *
 *  Created on: 26/06/2014
 *      Author: santosma
 */

#include "Timer.h"

//Contructor
Timer::Timer(){}

//Destructor
Timer::~Timer(){}

//Initializes the clock
void Timer::start(){
	seconds = 0.0;
	gettimeofday(&clockinit, &tz);
}

//Pauses the clock
float Timer::pause(){
	gettimeofday(&clockend, &tz);
	seconds += ((float)(clockend.tv_sec - clockinit.tv_sec)) + ((float)(clockend.tv_usec - clockinit.tv_usec))/1000000;
	gettimeofday(&clockinit, &tz);
	return seconds;
}

//Stop the clock
float Timer::stop(){
	gettimeofday(&clockend, &tz);
	seconds += ((float)(clockend.tv_sec - clockinit.tv_sec)) + ((float)(clockend.tv_usec - clockinit.tv_usec))/1000000;
	return seconds;
}
