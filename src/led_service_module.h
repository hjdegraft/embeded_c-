#ifndef LED_SERVICE_MODULE_H
#define LED_SERVICE_MODULE_H

#include "led_service_defines.h"
#include <msgpack.hpp>
#include "ledcontrol.h"


	bool led_service_module_init();	// Once systemd turns on the LED Svc, will set a flag
	int led_service_check_any_missed_messages (const std::string& topic);
	void serialize(msgpack::sbuffer& sbuf, int itr);
	void  led_define_indicator_status (const std::string& topic, const char* callback_msg, size_t msg_size); 
					// Check messages and set appropriate indicator flag
	int led_service_set_led_state();

#endif // LED_SERVICE_MODULE_H
