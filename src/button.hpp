#ifndef BUTTON_H
#define BUTTON_H

class Button
{
	bool value = false;

public:

	bool GetValue();
	void Press();
	void Unpress();
};

#endif