
#include "led_service_defines.h"

/* #pragma once
enum LEDCONTROL_STATES {LEDCONTROL_STATE_INIT,
                        LEDCONTROL_STATE_HEALTH_CHECK,               LEDCONTROL_STATE_HEALTH_CHECK_OK,
                        LEDCONTROL_STATE_HEALTH_FAILED_NIC,          LEDCONTROL_STATE_HEALTH_FAILED_SENSOR,
                        LEDCONTROL_STATE_HEALTH_FAILED_NETWORK_LINK, LEDCONTROL_STATE_HEALTH_FAILED_NETWORK_INTERNET,
                        LEDCONTROL_STATE_IDLE,                       LEDCONTROL_STATE_UNPROVISIONED,
                        LEDCONTROL_STATE_UPDATING,                   LEDCONTROL_STATE_OPERATIONAL,
                        LEDCONTROL_STATE_FACTORY_RESET,              LEDCONTROL_STATE_UNKNOWN } typedef ledcontrol_state_t;
enum LEDCONTROL_COLORS {LEDCONTROL_YELLOW,      LEDCONTROL_ORANGE,
                        LEDCONTROL_RED,         LEDCONTROL_PURPLE,
                        LEDCONTROL_BLUE,        LEDCONTROL_WHITE,
                        LEDCONTROL_GREEN,       LEDCONTROL_CYAN,
                        LEDCONTROL_RED_BLINK1,  LEDCONTROL_RED_BLINK2,
                        LEDCONTROL_RED_BLINK3,  LEDCONTROL_RED_BLINK4,
                        LEDCONTROL_RED_BLINK5,  LEDCONTROL_RED_BLINK6 } typedef ledcontrol_color_t;
*/
/*ledcontrol_state_t get_ledcontrol_state();
bool ledcontrol_init();
bool ledcontrol_process(const uint32_t current_time);
bool ledcontrol_process_color(const uint32_t current_time); */
bool ledcontrol_set_color(ledcontrol_color_t color);
int set_light_notifications(struct light_state_t const* state);
