#pragma once
class IRcode
{
public:
	
	struct config_t
	{
		unsigned long code; //this is start-light IR code saved in EEPROM by EEPROM_writeanything
		
	} cfg;

	IRcode();
	~IRcode();
};

