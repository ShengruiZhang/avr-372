/*
 * Header - Timers
 *
 * Created: 2020-04-01
 * Author: Shengrui Zhang
 */ 

#ifndef TIMER_H_
#define TIMER_H_

#define Timer1_TOP 0x1FFF
#define Timer3_TOP 0x1FFF

typedef unsigned int uint;

enum TimerMode {
	_Timer_Mode_CTC,
	_Timer_Mode_FastPWM
	};

void init_timer_0(enum TimerMode _mode_Timer0);
void init_timer_1(enum TimerMode _mode_timer1);
void init_timer_3(enum TimerMode _mode_timer3);

void Timer_0_delay(uint _Lenght_timer0);

void Timer_1_SetWidth(uint _Width_timer1);
void Timer_3_SetWidth(uint _Width_timer3);

#endif /* TIMER_H_ */