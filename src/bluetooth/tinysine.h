//
// Created by jeff on 11/17/17.
//

#ifndef FRDM_FAN_CONTROL_TINYSINE_H
#define FRDM_FAN_CONTROL_TINYSINE_H

#include <vector>
#include <string>
#include <cstdint>
#include <mbed.h>
#include <drivers/Serial.h>
#include "../util/logcat.h"

namespace frdm_fc {
    namespace bluetooth {
        class TinySine {
        public:
            enum ScanMode {
                CONNECTABLE_DISCOVERABLE = 0, CONNECTABLE = 1
            };

            enum Baudrate {
                _4800 = 1,
                _9600,
                _19200,
                _38400,
                _57600,
                _115200,
                _230400
            };

            explicit TinySine(mbed::Serial *uart);

            virtual ~TinySine();


            bool ModuleReady();

            bool Reset();

            bool DetectBaudrate();

            bool SetBaudrate(Baudrate baudrate);

            bool SetScanMode(ScanMode interval);

            std::string GetVersion();

        private:
            logcat::Logcat                  *_log;
            mbed::Serial                    *_uart;
            mbed::CircularBuffer<char, 255> *_uart_buf;
            mbed::Timer                     *_uart_timer;

            bool AT_SetInt(std::string param_name, int value);

            std::string AT_Get(const std::string &param_name);

            bool AT_Check();

            bool UART_WaitForResponse(std::string expected, int timeout_ms);

            std::string UART_Read(int timeout_ms);

            void UART_Write(std::string out);

            void UART_FlushBuffer();

            void UART_ISR();
        };
    }
}

#endif //FRDM_FAN_CONTROL_TINYSINE_H
