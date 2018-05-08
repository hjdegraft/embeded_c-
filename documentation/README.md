# LED SERVICE

## Design Approach

Chose not to create a class with member functions and parameters.  No application would need to create an instantiation and 
initialize any data.  When the device is turned on, Systemd (the Linus Init process) will boot the led_service.  After the 
software is loaded onto the device and the led service is apart of the programs that run, from the main function, the led 
service will set the led into a known state (e.g. LEDCONTROL_STATE_INIT) and set its color to a solid white.  

The led service gathers messages from the bus (ZMQ) and subsequently changes the led state.  Some states will be captured 
as placeholders for future output to the sysfs and others will guide the setting of the led color.

To receive the messages from the bus, led service will establish a connection via the libdensityd bus_client.  Create
an instantiation of the bus_client with a correct socket path for both publishing and pulling.  There are applications 
that push messages onto the bus and therefore the led service needs to subscribe to these type of messages that it wants
to receive.  After registering a topic for each type of message for which it will respond, then registers its callback
function for each subscription.  

The callback function will check the message, set the appropriate state and lastly color of the led according to the latest
layout in confluence.

### Breakdown of design
**led_service_util** - contains the main function.
  Inside this main function the led_service_module_init() is called, followed by densityd::create_bus_client.  Led Service
  registers its topic bus->register_topic("led_service.control") and its callback function 
    bus->register_callback([](const std::string& topic, const char* data, size_t size){
                led_define_indicator_status(topic, data, size)
    });
    
    Inside of the uv loop, mimicking real-life scenarios, and therefore, first serialize a message that is then published.
    Currently, only subscribing and publishing based off one type of message - led_service.control.  
    
    Lastly, led_service_set_led_state() is called to toggle output to the sysfs file.
    
 **led_service_module** - Main led service function definitions
  o `led_service_module_init`
  
  o led_service_check_any_missed_messages (placeholder) - for future development.  After led service is intialized and 
    if it shuts down.  During this shut down if any of the applications have published a message that is of interest,
    led service will need to request messages perhaps during init.  This request could just ask for all possible messages
    if not a lot of cycle time.  Or could implement a tag in the led service such that when it has already received a 
    message, flag it and therefore will execute this recovery_mode request, only request based upon the flag.
    
    o serialize - Sets the various messages and then packs them along with the result from the application check.  If test
    passed, then led service needs to unpack these messages from the callback().  
    Currently have an iterator to emulate a loop of events that occur to validate that led service implementation correctly
    sets the state and subsequent color.  This is commented out for github commit.  Another suggestion to this function
might be to include the topic in the parms.  This will allow to set the ledState based on the type of message.
    
    o led_define_indicator_status - will verify type of message via the topic and based upon this string, will check
    corresponding messages that get published.  Currently, only checking led_service.control type of messages.  Based on
    the message, set the led to a defined state.
    
    o led_service_set_led_state - According to the latest confluence document, there are basically four states to communicate
    to the end user (e.g. via color change).  Operational (normal), provisioned, wifi_ble unplugged, and non-normal/operational.
    This function groups the led state into these categories and calls ledcontrol_set_color.  For future development work, 
    can add led states in this func.
    
  **ledcontrol** - This was an existing file that I modified.  Updated case for colors, modified the values that are written
  to the sysfs/class/leds delay file.  The delay file determines how long a time lapse between each led blink.
  
    o ledcontrol_set_color - Based on a define, sets the hex color, whether the led should flash (e.g. blink) and the
    flashO[n|ff]MS vars, which are the delay settings.
    
    o set_light_notifications - Based on the color, set the rgb color (only files available in /sys/class/leds are 
    red, green, blue).  If color set to blink, write to the delay file using the o[n|ff]MS var
    
 **led_service_defines** - Contained all the defined led states and colors.
 
 **ledhal** - Previously written file containing the defines for flash or non-flash mode as well as the path locations for
 the sysfs file.
  o brightness - changes the actual color and the range is 0 (min) to 255 (max)
  o delay_o[n|ff] - sets the delay during flash mode of time lapse between blinks
  o trigger - gets set to enable blinking.  However, if the corresponding color->brightness file is set to 0, this trigger
  file is ignored.  To determine what is active in the trigger file, search for the "[xxx]" encapsulation.  If [none], then
  flash mode is disabled.
  
  Also contains the ledstate_callback struct containing the ledState and result.  Can create an object of this type for each
  kind of message (e.g. topic).  For example, could define ledstate_callback healthd_msg, etc.
