//
// Created by jeff on 11/17/17.
//
#include "frdm_fc_io.h"
#include "frdm_fc_pinout.h"


namespace frdm_fc {
    namespace io {

        const int kDefaultConsoleBaud   = 230400;
        const int kDefaultBluetoothBaud = 230400;

        mbed::Serial *GetConsoleUART() {
            static mbed::Serial console_uart(USBTX, USBRX, kDefaultConsoleBaud);
            return &console_uart;
        }

        mbed::Serial *GetBluetoothUART() {
            static mbed::Serial bt_uart(PTC4, PTC3, kDefaultBluetoothBaud);
            return &bt_uart;
        }
    }
}