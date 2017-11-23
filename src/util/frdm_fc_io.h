//
// Created by jeff on 11/17/17.
//

#ifndef FRDM_FAN_CONTROL_IO_H
#define FRDM_FAN_CONTROL_IO_H

#include <mbed.h>

namespace frdm_fc {
    namespace io {
        mbed::Serial *GetConsoleUART();
        mbed::Serial *GetBluetoothUART();
    }
}

#endif //FRDM_FAN_CONTROL_IO_H
