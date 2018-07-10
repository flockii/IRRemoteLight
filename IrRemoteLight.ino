/*
 Name:		IrRemoteLight.ino
 Created:	5/24/2018 1:10:16 PM
 Author:	flocki
*/

#include <irremote\IRremote.h>
#include "EEPROMWriteAnything.h"
#include "IRcode.h"
#include "Light.h"
#include <EEPROM\EEPROM.h>

int RECV_pin = 9; //IR receiver port
int pin=10; //light control on port 10 giving signal to uln2003
IRrecv irrecv(RECV_pin);
decode_results results;
IRcode *ircode;
Light *light;
int timeToChangeCode = 500;// setup time after start the board, for change remote IR code
//after this timeToChangeCode time, selected code will be considered as a new code that turns on the light
unsigned long time;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	irrecv.enableIRIn(); // Start the receiver
	light = new Light();
	ircode = new IRcode();
	//ircode->cfg.code = 333;
  // EEPROM_writeAnything(81, ircode->cfg);	
   EEPROM_readAnything(81,ircode->cfg); //read configuration from EEPROM
   Serial.println(ircode->cfg.code);
}
void SaveCode(unsigned long code)
{
	EEPROM_writeAnything(81, code);
}

// the loop function runs over and over again until power down or reset
void loop() {
	time = millis();
	
		if (irrecv.decode(&results)) 
		{
			if (time > timeToChangeCode) //enter to setup time(timeToChangeCode) is up - normal work- switch the light
			{
				Serial.println(results.value, HEX);
				Serial.println(results.value);
				if (results.value == ircode->cfg.code) //whencode is compatible switch the light
				{		
					if (light->ToggleLight(pin))
					{
						Serial.println("jasno");
					}
					else
					{
						Serial.println("ciemno");
					}
				}
			}
			else { //config time has not passed - changing new code is possible by Remote IR

				ircode->cfg.code = results.value;
				SaveCode(ircode->cfg.code);
				Serial.println(time);
			}
			irrecv.resume(); // Receive the next value
		}
	
}
