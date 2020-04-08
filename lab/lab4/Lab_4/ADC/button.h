/*
 * Header - Button handling
 *
 * Created: 2020-04-08 03:55:24
 * Author: Shengrui Zhang
 */ 

#ifndef	BUTTON_H_
#define BUTTON_H_

enum Button_State {
	_State_Button_released,
	_State_Button_to_pressed,
	_State_Button_pressed,
	_State_Button_to_released
	};

void init_button();

#endif /* BUTTON_H_ */