#include <mbed.h>
#include "usb/usb_fan_controller.h"


int main(void) {
    auto *dev = new usb::FanControllerDevice();
    dev->Connect();
    Thread::wait(osWaitForever);
    return 0;
}
