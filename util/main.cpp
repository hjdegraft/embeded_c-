#include <stdint.h>
//#include "docopt/docopt.h"
#include "ledhal.h"
#include "led_service_module.h"
#include <iostream>

int main(int argc, char **argv)
{
     int result = 0;
#if 0
     static const char USAGE[] =
             R"(ledcontrold.
 
             Usage:
             ledcontrold
             ledcontrold (-h | --help)
             ledcontrold --version
 
             Options:
             -h --help           Show this screen.
             --version           Show version.
             )";

    std::map<std::string, docopt::value> args
            = docopt::docopt(USAGE,
                             { argv + 1, argv + argc },
                             true,                // show help if requested
                             "ledcontrold 0.1.3");  // version string
#endif

     if (!led_service_module_init())
     {
          result = 1;
     }



     while(true)
     {
        led_service_set_led_state();
        // ledcontrol_process(1);
     }

  return result;
}
