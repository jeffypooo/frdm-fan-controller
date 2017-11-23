//
// Created by jeff on 11/17/17.
//
#include <sstream>
#include <deque>
#include "tinysine.h"


namespace frdm_fc {
    namespace bluetooth {

        static const char *kTag = "TinySine";


        TinySine::TinySine(mbed::Serial *uart) : _uart(uart), _log(logcat::Shared()) {
            _uart_timer = new mbed::Timer;
            _uart_buf   = new mbed::CircularBuffer<char, 255>;
            _uart->attach(Callback<void()>(this, &TinySine::UART_ISR));
        }

        TinySine::~TinySine() {
            delete _uart_timer;
            delete _uart_buf;
        };

        bool TinySine::ModuleReady() {
            return AT_Check();
        }

        bool TinySine::Reset() {
            UART_Write("AT+RESET");
            return UART_WaitForResponse("OK+RESET", 500);
        }

        bool TinySine::DetectBaudrate() {
            std::deque<int> bauds{230400, 115200, 57600, 38400, 19200, 9600, 4800};
            while (!bauds.empty()) {
                auto b = bauds[0];
                bauds.pop_front();
                _uart->baud(b);
                if (AT_Check()) {
                    _log->D(kTag, "DetectBaudrate(): success (%d)", b);
                    return true;
                }
            }
            _log->W(kTag, "DetectBaudrate(): module not responding");
            return false;
        }

        bool TinySine::SetBaudrate(Baudrate baud) {
            return AT_SetInt("BAUD", baud);
        }

        bool TinySine::SetScanMode(TinySine::ScanMode interval) {
            return AT_SetInt("SCAN", interval);
        }

        std::string TinySine::GetVersion() {
            auto vers = AT_Get("VERS");
            if (vers.length() > 0) {
                _log->V(kTag, "version: %s", vers.c_str());
                return vers;
            }
            auto verr = AT_Get("VERR");
            if (verr.length() > 0) {
                _log->V(kTag, "version: %s", verr.c_str());
                return verr;
            }
            _log->E(kTag, "failed to read version");
            return "";
        }

        bool TinySine::AT_SetInt(std::string param_name, int value) {
            _log->D(kTag, "setting parameter '%s' = %d", param_name.c_str(), value);
            std::ostringstream cmd_stream;
            cmd_stream << "AT+" << param_name << value;
            UART_Write(cmd_stream.str());
            std::ostringstream res_stream;
            res_stream << "OK+Set:" << value;
            auto success = UART_WaitForResponse(res_stream.str(), 500);
            UART_FlushBuffer();
            if (!success) {
                _log->W(kTag, "timed out setting parameter '%s'", param_name.c_str());
                return false;
            }
            return true;
        }

        std::string TinySine::AT_Get(const std::string &param_name) {
            _log->D(kTag, "getting parameter '%s'", param_name.c_str());
            std::ostringstream cmd_stream;
            cmd_stream << "AT+" << param_name << "?";
            UART_Write(cmd_stream.str());
            auto responded = UART_WaitForResponse("OK+Get:", 500);
            if (!responded) {
                _log->W(kTag, "timed out getting parameter '%s'", param_name.c_str());
                return "";
            }
            auto value_str = UART_Read(500);
            UART_FlushBuffer();
            return value_str;
        }

        bool TinySine::AT_Check() {
            UART_Write("AT");
            auto success = UART_WaitForResponse("OK", 500);
            if (!success) {
                _log->W(kTag, "AT_Check(): no response");
                return false;
            } else {
                _log->D(kTag, "AT_Check(): success");
                return true;
            }
        }

        bool TinySine::UART_WaitForResponse(std::string expected, int timeout_ms) {
            std::string resp;
            char        tmp;
            int         cur_time_ms = 0;
            _uart_timer->stop();
            _uart_timer->reset();
            _uart_timer->start();
            while (cur_time_ms < timeout_ms) {
                cur_time_ms = _uart_timer->read_ms();
                if (!_uart_buf->pop(tmp)) continue;
                resp += tmp;
                if (resp.length() == expected.length()) break;
            }
            _log->V(kTag, "UART_WaitForResponse(%s, %d): got '%s'", expected.c_str(), timeout_ms, resp.c_str());
            return resp == expected;
        }

        std::string TinySine::UART_Read(int timeout_ms) {
            std::string str;
            char        tmp;
            _uart_timer->stop();
            _uart_timer->reset();
            _uart_timer->start();
            while (_uart_timer->read_ms() < timeout_ms) {
                if (!_uart_buf->pop(tmp)) continue;
                str += tmp;
            }
            _log->V(kTag, "UART_Read(%d): read %d bytes", timeout_ms, str.length());
            return str;
        }

        void TinySine::UART_Write(std::string out) {
            _uart->printf(out.c_str());
        }

        void TinySine::UART_FlushBuffer() {
            char tmp;
            int  i = 0;
            while (_uart_buf->pop(tmp)) {
                i++;
            }
            _log->V(kTag, "UART_Flush(): dumped %d bytes", i);
        }

        void TinySine::UART_ISR() {
            while (_uart->readable()) {
                auto rd = static_cast<char>(_uart->getc());
                _uart_buf->push(rd);
            }
        }
    }
}