//
// Created by jeff on 11/15/17.
//

#include <features/unsupported/USBDevice/USBHID/USBHID_Types.h>
#include <string>
#include <vector>
#include "usb_fan_controller.h"

namespace usb {

    struct StringDescriptor {
        uint8_t *data;
        size_t len;
        StringDescriptor(uint8_t *data, size_t len) {
            this->data = new uint8_t[len];
            this->len = len;
            memcpy(this->data, data, len);
        }
        virtual ~StringDescriptor() {
            delete[] this->data;
        }
    };

    static StringDescriptor *MakeStringDesc(const char *str) {
        std::vector<uint8_t> vec;
        vec.push_back(0);
        vec.push_back(STRING_DESCRIPTOR);
        for (int i = 0; i < strlen(str); ++i) {
            vec.push_back(str[i]);
            vec.push_back(0);
        }
        vec[0] = static_cast<uint8_t >(vec.size());
        return new StringDescriptor(vec.data(), vec.size());
    }

    FanControllerDevice::FanControllerDevice() {
        _hid_dev = new USBHID(64, 64, 0xFDFC, 0x0001, 0x0001, false);
        _b_led   = new mbed::DigitalOut(LED_BLUE);
        _b_led->write(1);
        _dev_thr = new Thread;
        ConfigureDescriptors();
    }

    FanControllerDevice::~FanControllerDevice() {
        Disconnect();
        delete _hid_dev;
    }

    void FanControllerDevice::Connect() {
        _hid_dev->connect(true);
        _b_led->write(0);
        _dev_thr->start(Callback<void()>(this, &FanControllerDevice::DeviceThreadLoop));
    }

    void FanControllerDevice::Disconnect() {
        _dev_thr->terminate();
        _hid_dev->disconnect();
        _b_led->write(1);

    }

    void FanControllerDevice::ConfigureDescriptors() {
        auto mfg_name = MakeStringDesc("JMJ Software");
        auto prod_name = MakeStringDesc("FRDM-K64F Fan Controller");
        memcpy(_hid_dev->stringImanufacturerDesc(), mfg_name->data, mfg_name->len);
        memcpy(_hid_dev->stringIproductDesc(), prod_name->data, prod_name->len);
    }

    void FanControllerDevice::DeviceThreadLoop() {
        auto *recv = new HID_REPORT;
        while (true) {
            _hid_dev->read(recv);
            _b_led->write(recv->data[0]);
        }
    }

}