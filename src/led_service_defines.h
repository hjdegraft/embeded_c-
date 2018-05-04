#pragma once

enum LED_INDICATOR_STATES {LEDCONTROL_STATE_INIT,			LED_STATE_IDLE,
				  WIFI_BLE_DONGLE_UNPLUGGED_STATE,	WIFI_BLE_DONGLE_UNPLUGGED,
				  LED_HEALTH_CHECK_STATE,		LED_HEALTH_CHECK_OK,
                                  LED_DPU_UNPROVISIONED_STATE,		LED_DPU_NOT_PROVISIONED,
                                  LED_DPU_UPDATING_STATE,		LED_DPU_UPDATED,
                                  LED_DPU_PROVISIONING_STATE,		LED_DPU_PROVISIONED,
                                  LED_DPU_OPERATIONAL_STATE,		LED_DPU_OPERATIONAL,
                                  LED_DPU_FACTORY_RESET_STATE,		LED_DPU_IN_FACTORY_RESET,
                                  LED_NETWORK_IS_DOWN_STATE,		LED_NETWORK_DOWN,
                                  LED_SENSOR_IN_FAIL_STATE,		LED_SENSOR_FAILED,
                                  LED_NO_NETWORK_LINK_STATE,		LED_NO_NETWORK_LINK,
                                  LED_INTERNET_NOT_AVAIL_STATE,		LED_INTERNET_NOT_AVAILABLE } typedef led_indicator_state_t;

enum LEDCONTROL_COLORS {LEDCONTROL_YELLOW,      LEDCONTROL_ORANGE,
                        LEDCONTROL_RED,         LEDCONTROL_PURPLE,
                        LEDCONTROL_BLUE_BLINK,  LEDCONTROL_WHITE,
			LEDCONTROL_WHITE_BLINK, LEDCONTROL_GREEN,       
			LEDCONTROL_CYAN, 	LEDCONTROL_RED_BLINK1,  
			LEDCONTROL_RED_BLINK2, 	LEDCONTROL_RED_BLINK3,  
                        LEDCONTROL_RED_BLINK4,  LEDCONTROL_RED_BLINK5 } typedef ledcontrol_color_t;

/**
** Have the names of the files in sysfs that LED Service will write to
** for handling of the led module
**
**/
