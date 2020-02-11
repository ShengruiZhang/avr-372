#ifndef GLOBAL_MACRO_H_
#define GLOBAL_MACRO_H_

typedef unsigned int uint;
typedef unsigned char uchar;

enum LED_State {_State_LED_slow, _State_LED_fast};
enum Button_State {_State_Button_released, _State_Button_to_pressed,
	_State_Button_pressed, _State_Button_to_released};

#endif