#include "led_service_module.h"
#include <densityd/bus_client.h>
#include <densityd/async.h>
#include <iostream>
#include <functional>
#include <uv.h>

static led_indicator_state_t ledstate;

int main (int argc, char** argv)
{
	int result = 0;
	bool init;
	
	init = led_service_module_init(); 

	std::unique_ptr<densityd::bus_client> bus = densityd::create_bus_client("ipc:///tmp/broker_publish.ipc",
										"ipc:///tmp/broker_pull.ipc"); 
	bus->register_topic("led_service.control"); 
	/*
        ** After led_service initializes, it will need to check and see what critical messages it has missed.
        ** Healthd/provisiond will publish all messages based on events, but led_service will only update
        ** led light based on specific events.  Therefore, after init and led_service has sent a message
	** notifying which type-message (e.g. subscribed topic) it is interested in, then can call a func
	** that asks if any messages of this type (e.g. topic) has been sent out already and not 'handled' yet.
	** Of these, application will publish another message for each one missed.
        */
//	led_service_check_any_missed_messages("led_service.control");	
	bus->register_callback([](const std::string& topic, const char* data, size_t size){
        	led_define_indicator_status(topic, data, size);
	});  


		densityd::timer timer(uv_default_loop(), [&bus, &argv](){
		//need to publish the msgpack buffer so that when callback is triggered, it contains
		// the encoded message that will need to be unpacked
        	//std::string message("LED_DPU_PROVISIONING_STATE");
			/*
			** For testing, came up with a way to mimic real-time events such as dpu is provisioned, or
			** normal operation mode, or the wifi ble is unplugged.  Attempting to publish all these messages
			** back-to-back, to verify the implementation that handles these messages is correctly setting the
			** the led state and subsequent color.
			*/
			for (auto itr = 0; itr != 4; itr++) {

				msgpack::sbuffer message;
        			serialize(message, itr);
        			bus->publish_message("led_service.control", message.data(), message.size());


        			led_service_set_led_state();
			}// end of for loop

    		});


    	timer.start(1000, 1000);

	uv_run(uv_default_loop(), UV_RUN_DEFAULT); 

	return result;
}
