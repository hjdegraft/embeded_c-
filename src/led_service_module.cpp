#include "led_service_module.h"
#include "ledhal.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <map>
#include <msgpack.hpp>


static led_indicator_state_t ledstate;
static ledstate_callback msg;

bool led_service_module_init () 
{
 	bool isOn = true;
   	ledstate =  LEDCONTROL_STATE_INIT;

       	return isOn;
}
 
int led_service_check_any_missed_messages (const std::string& topic)
{
	int result = 1;

	/*
	** Upon initialization, get state of the applications gather any missed messages
	** 
	*/
		
	return result;
}

// Encoding/packing the message to publish onto the bus
void serialize(msgpack::sbuffer& sbuf, int itr)
{
	std::cout << "What message are we on : " << itr << std::endl << std::endl;
	if (itr == 0)
	{
		msg.ledState = "WIFI_BLE_DONGLE_UNPLUGGED_STATE";
		msg.result = "pass";
	} else if (itr == 1) 
	{
		msg.ledState = "LED_DPU_PROVISIONING_STATE";
		msg.result = "pass";
	} else if (itr == 2)
	{
		msg.ledState = "LED_DPU_OPERATIONAL_STATE";
		msg.result = "pass";
	} else if (itr == 3)
	{
		msg.ledState = "LED_NETWORK_IS_DOWN_STATE";
		msg.result = "pass";
	}
	/*{"name": "LED_DPU_PROVISIONING_STATE", "result": pass}*/
	msgpack::packer<msgpack::sbuffer> pk(&sbuf);
	pk.pack_map(2);
	{
		pk.pack(std::string("ledState"));
		pk.pack(msg.ledState);

		std::cout << "Value of led state is : " << msg.ledState << std::endl << std::endl;

		pk.pack(std::string("result"));
		pk.pack(msg.result);

		std::cout << "Value of result is : " << msg.result << std::endl << std::endl;

	}
}

void led_define_indicator_status (const std::string& topic, const char* callback_msg, size_t msg_size) 
{
	/*
	** Will have a plethora here of topics, therefore based on the type of message, then can check for
	** type of message and then check the result 
	**
	*/

	if (topic == "led_service.control") {
		// unpack the callback message
		msgpack::object_handle oh = msgpack::unpack(callback_msg, msg_size);
		const msgpack::object& callbackmsg_obj = oh.get();
		callbackmsg_obj.convert(msg);
		// Need to figure out what it is unpacking and the end result
		std::cout << "Checking callback func message : " << msg.ledState << std::endl << std::endl;
		if ((msg.ledState == "LED_STATE_IDLE") &&
			(msg.result == "pass")) 
		{
			ledstate = LED_DPU_OPERATIONAL;
		} 
		if ((msg.ledState == "LED_DPU_OPERATIONAL_STATE") &&
			(msg.result == "pass")) 
		{
			ledstate = LED_DPU_OPERATIONAL;
		}
		if ((msg.ledState ==  "LED_HEALTH_CHECK_STATE") && 
			(msg.result == "pass"))
		{
			ledstate = LED_HEALTH_CHECK_OK;
		}	
		if ((msg.ledState == "LED_DPU_PROVISIONING_STATE") && 
			(msg.result == "pass"))
		{
		 	ledstate = LED_DPU_PROVISIONED;
		}
		if ((msg.ledState == "WIFI_BLE_DONGLE_UNPLUGGED_STATE") && 
			(msg.result == "pass"))
		{
			ledstate = WIFI_BLE_DONGLE_UNPLUGGED;
		}	
		if ((msg.ledState == "LED_NETWORK_IS_DOWN_STATE") && 
			(msg.result == "pass"))
		{
			ledstate = LED_NETWORK_DOWN;
		}
		if ((msg.ledState == "LED_SENSOR_IN_FAIL_STATE") &&
			(msg.result == "pass"))
		{
			ledstate = LED_SENSOR_FAILED;
		}
		if ((msg.ledState == "LED_NO_NETWORK_LINK_STATE") && 
			(msg.result == "pass"))
		{
			ledstate = LED_NO_NETWORK_LINK;
		}
		if ((msg.ledState == "LED_INTERNET_NOT_AVAIL_STATE") &&
			(msg.result == "pass"))
		{
			ledstate = LED_INTERNET_NOT_AVAILABLE;
		}

	}// end if (topic)

} // end led_define_indicator_status


int led_service_set_led_state()
{
	int result = 0;

	std::cout << "The ledstate is as follows :" << ledstate << std::endl << std::endl; 
	switch (ledstate) {
		/*
		** For non-failure state/operational mode
		*/
		case	LEDCONTROL_STATE_INIT:	
		case	LED_DPU_OPERATIONAL:
		case	LED_HEALTH_CHECK_OK:
		{
			ledcontrol_set_color(LEDCONTROL_WHITE); 
			break;
		}

		case	LED_DPU_PROVISIONED:
		{
			ledcontrol_set_color(LEDCONTROL_BLUE_BLINK);
			break;
		}

		case	WIFI_BLE_DONGLE_UNPLUGGED:	
		{
			ledcontrol_set_color(LEDCONTROL_ORANGE); 
			break;
		}

		/*
		** For non-operational mode
		*/
		case	LED_NETWORK_DOWN:
		case	LED_SENSOR_FAILED:
		case	LED_NO_NETWORK_LINK:
		case	LED_INTERNET_NOT_AVAILABLE:
		{
			ledcontrol_set_color(LEDCONTROL_WHITE_BLINK);
			break;
		}

		
	} // end of switch

	return result;
} // end of led_service_set_led_status
