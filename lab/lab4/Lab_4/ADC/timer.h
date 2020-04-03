/*
 * Header - Timers
 *
 * Created: 2020-04-01
 * Author: Shengrui Zhang
 */ 

#ifndef TIMER_H_
#define TIMER_H_

typedef unsigned int uint;

enum TimerMode {
	_Timer_Mode_CTC,
	_Timer_Mode_FastPWM
	};

void init_timer_16(enum TimerMode _mode);

#endif /* TIMER_H_ */