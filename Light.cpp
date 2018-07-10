#include "Light.h"

Light::Light()
{
	pin = 10; //light control on pin 10
	pinMode(pin, OUTPUT);
}


Light::~Light()
{
}

void Light::TurnOn(int pin)
{
	digitalWrite(pin, HIGH);
	delay(50);
}

void Light::TurnOff(int pin)
{
	digitalWrite(pin, LOW);
	delay(50);
}

bool Light::CheckLightState(int pin)
{	
	bool result = digitalRead(pin);	
	return result;
}

//toggle light depending state
bool Light::ToggleLight(int pin)
{
	bool result;
	if (CheckLightState(pin)==true)
	{
		TurnOff(pin);
		result = false;		
	}
	else
	{
		TurnOn(pin);
		result = true;	
	}
	return result;
}
