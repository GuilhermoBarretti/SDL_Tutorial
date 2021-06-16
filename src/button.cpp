#include "button.hpp"


bool Button::GetValue()
{
	return value;
}

void Button::Press()
{
	value = true;
}

void Button::Unpress()
{
	value = false;
}