#pragma once
#include <Arduino.h>
class Light
{
public:
	int pin;
	
	bool ToggleLight(int pin);
	Light();
	~Light();

private:
	bool CheckLightState(int pin);
	void TurnOn(int pin);
	void TurnOff(int pin);
};

