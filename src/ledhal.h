#pragma once
#include <map>
#include <msgpack.hpp>
#include <string>

#define LIGHT_FLASH_NONE            0
#define LIGHT_FLASH_TIMED           1

char const*const RED_LED_FILE
        = "/sys/class/leds/pca963x:red/brightness";
char const*const GREEN_LED_FILE
        = "/sys/class/leds/pca963x:green/brightness";
char const*const BLUE_LED_FILE
        = "/sys/class/leds/pca963x:blue/brightness";

char const*const RED_DELAY_ON_FILE
        = "/sys/class/leds/pca963x:red/delay_on";
char const*const GREEN_DELAY_ON_FILE
        = "/sys/class/leds/pca963x:green/delay_on";
char const*const BLUE_DELAY_ON_FILE
        = "/sys/class/leds/pca963x:blue/delay_on";

char const*const RED_DELAY_OFF_FILE
        = "/sys/class/leds/pca963x:red/delay_off";
char const*const GREEN_DELAY_OFF_FILE
        = "/sys/class/leds/pca963x:green/delay_off";
char const*const BLUE_DELAY_OFF_FILE
        = "/sys/class/leds/pca963x:blue/delay_off";

char const*const RED_TRIGGER_FILE
        = "/sys/class/leds/pca963x:red/trigger";
char const*const GREEN_TRIGGER_FILE
        = "/sys/class/leds/pca963x:green/trigger";
char const*const BLUE_TRIGGER_FILE
        = "/sys/class/leds/pca963x:blue/trigger";

/**
 * The parameters that can be set for a given light.
 *
 * Not all lights must support all parameters.  If you
 * can do something backward-compatible, you should.
 */
struct light_state_t {
    /**
     * The color of the LED in ARGB.
     *
     * Do your best here.
     *   - If your light can only do red or green, if they ask for blue,
     *     you should do green.
     *   - If you can only do a brightness ramp, then use this formula:
     *      unsigned char brightness = ((77*((color>>16)&0x00ff))
     *              + (150*((color>>8)&0x00ff)) + (29*(color&0x00ff))) >> 8;
     *   - If you can only do on or off, 0 is off, anything else is on.
     *
     * The high byte should be ignored.  Callers will set it to 0xff (which
     * would correspond to 255 alpha).
     */
    unsigned int color;
    /**
     * See the LIGHT_FLASH_* constants
     */
    int flashMode;
    int flashOnMS;
    int flashOffMS;
};

struct ledstate_callback {
	std::string ledState;
	std::string result;

	MSGPACK_DEFINE_MAP(ledState, result)
};
