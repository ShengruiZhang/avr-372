/*
 * Header - Global Macro
 *
 * Macros for timers
 *
 * Created: 2020-05-07 18:11:16
 *
 * Author: Shengrui Zhang
			Zepeng Cai
 */ 
#ifndef _GLOBAL_MACRO_H
#define _GLOBAL_MACRO_H

#define Timer1_TOP 0x1FFF
#define Timer3_TOP 0x1FFF

typedef unsigned int uint;
typedef unsigned char uchar;

enum TimerMode {
	_Timer_Mode_CTC,
	_Timer_Mode_FastPWM
	};

#endif