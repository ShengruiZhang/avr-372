/*
 * Header - Timers
 *
 * Created: 2020-04-01
 * Author: Shengrui Zhang
 */ 

#ifndef TIMER_H_
#define TIMER_H_

void init_timer_0(enum TimerMode _mode_Timer0);
void init_timer_1(enum TimerMode _mode_timer1);

void Timer_0_delay_ms(uint _Lenght_timer0);
void Timer_1_delay_ms(uint16_t _Lenght_timer1);

void Timer_1_SetWidth(float _Width_timer1);

#endif /* TIMER_H_ */