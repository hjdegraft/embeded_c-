#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "ledcontrol.h"
//#include <czmq.h>
#include <unistd.h>
#include <iostream>
#include "ledhal.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <stdio.h>

static light_state_t st;

static int write_str(char const* path, const char* val)
{
    int fd;
    static int already_warned = 0;

    fd = open(path, O_RDWR);
    if (fd >= 0) {
        ssize_t amt = write(fd, val, (size_t)strlen(val));
        close(fd);
        return amt == -1 ? -errno : 0;
    } else {
        if (already_warned == 0) {
            already_warned = 1;
        }
        return -errno;
    }
}

static int write_int(char const* path, int value)
{
    int fd;
    static int already_warned = 0;

    fd = open(path, O_RDWR);
    if (fd >= 0) {
        char buffer[64];
        int bytes = snprintf(buffer, sizeof(buffer), "%d\n", value);
        ssize_t amt = write(fd, buffer, (size_t)bytes);
        close(fd);
        return amt == -1 ? -errno : 0;
    } else {
        if (already_warned == 0) {
            already_warned = 1;
        }
        return -errno;
    }
}

int set_light_notifications(struct light_state_t const* state)
{
    int red, green, blue;
    int blink;
    int onMS, offMS;
    unsigned int colorRGB;

    switch (state->flashMode) {

        case LIGHT_FLASH_TIMED:
#if 1
            onMS = state->flashOnMS;
            offMS = state->flashOffMS;
#endif
            break;

        case LIGHT_FLASH_NONE:
        default:
            onMS = 0;
            offMS = 0;

            break;
    }
    colorRGB = state->color;

    red = (colorRGB >> 16) & 0xFF;
    green = (colorRGB >> 8) & 0xFF;
    blue = colorRGB & 0xFF;

    if (onMS > 0 && offMS > 0) {
        blink = 1;
    } else {
        blink = 0;
    }

    if (blink) {

        write_str(RED_TRIGGER_FILE, "timer");
        write_str(GREEN_TRIGGER_FILE, "timer");
        write_str(BLUE_TRIGGER_FILE, "timer");

        write_int(RED_DELAY_ON_FILE, onMS);
        write_int(GREEN_DELAY_ON_FILE, onMS);
        write_int(BLUE_DELAY_ON_FILE, onMS);

        write_int(RED_DELAY_OFF_FILE, offMS);
        write_int(GREEN_DELAY_OFF_FILE, offMS);
        write_int(BLUE_DELAY_OFF_FILE, offMS);

        write_int(RED_LED_FILE, red);
        write_int(GREEN_LED_FILE, green);
        write_int(BLUE_LED_FILE, blue);
    } else {
        write_str(RED_TRIGGER_FILE, "none");
        write_str(GREEN_TRIGGER_FILE, "none");
        write_str(BLUE_TRIGGER_FILE, "none");

        write_int(RED_LED_FILE, red);
        write_int(GREEN_LED_FILE, green);
        write_int(BLUE_LED_FILE, blue);
    }

    return 0;
}


bool ledcontrol_set_color(ledcontrol_color_t color)
{
   switch(color)
   {
        default:
        {
           color = LEDCONTROL_YELLOW; 
        }

        case LEDCONTROL_YELLOW:
        {
           break;
        }

        case LEDCONTROL_RED:
        {
#if 1
           st.flashMode  = LIGHT_FLASH_NONE;
           st.flashOnMS  = 0;
           st.flashOffMS = 0;
           st.color      = 0x00FF0000;
#endif
           break;
        }

        case LEDCONTROL_BLUE_BLINK:
        {
#if 1
	   // the flashO[n|ff]MS params are used to set the delay file and the smaller, the less time in between
	   // each blink
	   std::cout << "The color is set to LEDCONTROL_BLUE_BLINK" << std::endl << std::endl;
           st.flashMode  = LIGHT_FLASH_TIMED;
           st.flashOnMS  = 100;
           st.flashOffMS = 100;
           st.color      = 0x000000FF;
#endif
           break;
        }

        case LEDCONTROL_GREEN:
        {
#if 1
           st.flashMode  = LIGHT_FLASH_NONE;
           st.flashOnMS  = 0;
           st.flashOffMS = 0;
           st.color      = 0x0000FF00;
#endif
           break;
        }

        case LEDCONTROL_ORANGE:
        {
	   std::cout << "The color is set to LEDCONTROL_ORANGE" << std::endl << std::endl;
           st.flashMode  = LIGHT_FLASH_NONE;
           st.flashOnMS  = 0;
           st.flashOffMS = 0;
           st.color      = 0x00FFFF00;
           break;
        }

        case LEDCONTROL_PURPLE:
        {
#if 1
           st.flashMode  = LIGHT_FLASH_NONE;
           st.flashOnMS  = 0;
           st.flashOffMS = 0;
           st.color      = 0x00FFFF00;
#endif
           break;
        }

        case LEDCONTROL_WHITE:
        {
#if 1
	   std::cout << "The color is set to LEDCONTROL_WHITE" << std::endl << std::endl;
           st.flashMode  = LIGHT_FLASH_NONE;
           st.flashOnMS  = 0;
           st.flashOffMS = 0;
           //st.color      = 0x0088FFFF;
           st.color      = 0x0044FFFF;
#endif
           break;
        }

        case LEDCONTROL_WHITE_BLINK:
        {
#if 1
	   std::cout << "The color is set to LEDCONTROL_WHITE_BLINK" << std::endl << std::endl;
           st.flashMode  = LIGHT_FLASH_TIMED;
           st.flashOnMS  = 100;
           st.flashOffMS = 100;
           //st.color      = 0x0088FFFF;
           st.color      = 0x0044FFFF;
#endif
           break;
        }

        case LEDCONTROL_CYAN:
        {
#if 1
           st.flashMode  = LIGHT_FLASH_NONE;
           st.flashOnMS  = 0;
           st.flashOffMS = 0;
           st.color      = 0x0000FFFF;
#endif
           break;
        }

        case LEDCONTROL_RED_BLINK1:
        {
#if 1
           st.flashMode  = LIGHT_FLASH_NONE;
           st.flashOnMS  = 0;
           st.flashOffMS = 0;
           st.color      = 0x00FF0000;
#endif
           break;
        }

        case LEDCONTROL_RED_BLINK2:
        {
#if 1
           st.flashMode  = LIGHT_FLASH_NONE;
           st.flashOnMS  = 0;
           st.flashOffMS = 0;
           st.color      = 0x00FF0000;
#endif
           break;
        }

        case LEDCONTROL_RED_BLINK3:
        {
#if 1
           st.flashMode  = LIGHT_FLASH_NONE;
           st.flashOnMS  = 0;
           st.flashOffMS = 0;
           st.color      = 0x00FF0000;
#endif
           break;
        }

        case LEDCONTROL_RED_BLINK4:
        {
#if 1
           st.flashMode  = LIGHT_FLASH_NONE;
           st.flashOnMS  = 0;
           st.flashOffMS = 0;
           st.color      = 0x00FF0000;
#endif
           break;
        }

        case LEDCONTROL_RED_BLINK5:
        {
#if 1
           st.flashMode  = LIGHT_FLASH_NONE;
           st.flashOnMS  = 0;
           st.flashOffMS = 0;
           st.color      = 0x00FF0000;
#endif
           break;
        }

   } // end of switch

         set_light_notifications(&st);
}


/*bool ledcontrol_process_color(const uint32_t current_time)
{
    bool result = false;
    return result;
}
bool ledcontrol_process(const uint32_t current_time)
{
  bool result = true;
  switch(ledcontrol_state)
  {
      case LEDCONTROL_STATE_INIT:
      {
         ledcontrol_state = LEDCONTROL_STATE_HEALTH_CHECK;
//         ledcontrol_set_color(LEDCONTROL_RED); 
         break;
      }
      case LEDCONTROL_STATE_HEALTH_CHECK:
      {
          //TODO: Health Check Daemon needs to be implemented. Skip this test for now
          ledcontrol_state = LEDCONTROL_STATE_HEALTH_CHECK_OK;
          break;
      }
      case LEDCONTROL_STATE_HEALTH_CHECK_OK:
      {
          ledcontrol_set_color(LEDCONTROL_WHITE);
          ledcontrol_state = LEDCONTROL_STATE_IDLE;
          break;
      }
      case LEDCONTROL_STATE_HEALTH_FAILED_NIC:
      {
          
          break;
      }
      case LEDCONTROL_STATE_HEALTH_FAILED_SENSOR:
      { 
          break;
      }
      case LEDCONTROL_STATE_HEALTH_FAILED_NETWORK_LINK:
      {
          break;
      }
      case LEDCONTROL_STATE_HEALTH_FAILED_NETWORK_INTERNET:
      {
          break;
      }
      case LEDCONTROL_STATE_IDLE:
      {
          //if update available then
                // state = LEDCONTROL_STATE_UPDATING;
          //else if unprovisioned then
                // state = LEDCONTROL_STATE_UNPROVISIONED;
          // else if shal we health check again? then
                // state = some health state
          // else go back to OPERATIONAL state if all is good
          usleep(1000);
          break;
      }
      case LEDCONTROL_STATE_UNPROVISIONED:
      {
          break;
      }
      case LEDCONTROL_STATE_OPERATIONAL:
      {
          // some timeout occurs, let's go back to STATE_IDLE and run through the prerequisites and hopefully back to this state
          break;
      }
      case LEDCONTROL_STATE_UPDATING:
      {
          break;
      }
      case LEDCONTROL_STATE_FACTORY_RESET:
      {
          break;
      }
     return result;
  }
} */
