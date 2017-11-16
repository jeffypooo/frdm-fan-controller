//
// Created by jeff on 11/15/17.
//

#ifndef FRDM_FAN_CONTROL_USB_FAN_CONTROLLER_H
#define FRDM_FAN_CONTROL_USB_FAN_CONTROLLER_H

#include <platform.h>
#include <features/unsupported/USBDevice/USBHID/USBHID.h>

namespace usb {


    class FanControllerDevice {
    public:
        FanControllerDevice();

        virtual ~FanControllerDevice();

        void Connect();

        void Disconnect();


    private:
        USBHID           *_hid_dev;
        mbed::DigitalOut *_b_led;
        Thread           *_dev_thr;
        void ConfigureDescriptors();
        void DeviceThreadLoop();
    };

}
#endif //FRDM_FAN_CONTROL_USB_FAN_CONTROLLER_H
