//
// Created by jeff on 11/22/17.
//

#include "logcat.h"
#include "frdm_fc_io.h"

namespace frdm_fc {
    namespace logcat {

        std::string level::GetDesc(level::LevelType level) {
            switch (level) {
                case level::VERBOSE:
                    return "V";
                case level::DEBUG:
                    return "D";
                case level::INFO:
                    return "I";
                case level::WARN:
                    return "W";
                case level::ERROR:
                    return "E";
                case level::WTF:
                    return "WTF";
                default:
                    return "?";
            }
        }

        ConsoleSink::ConsoleSink(level::LevelType level) : ISink(), _level(level), _timer() { _timer.start(); }

        ConsoleSink::~ConsoleSink() = default;

        level::LevelType ConsoleSink::GetLevel() {
            return _level;
        }

        void ConsoleSink::SetLevel(level::LevelType level) {
            _level = level;
        }

        void ConsoleSink::Log(level::LevelType level, const char *tag, const char *fmt, va_list const &args) {
            if (level < _level) return;
            auto cons       = io::GetConsoleUART();
            auto level_desc = level::GetDesc(level);
            auto ms = _timer.read_ms();
            auto ms_r = ms % 1000;
            auto sec_r = (ms / 1000) % 60;
            auto min_r = ((ms / 1000) / 60);
            cons->printf("[%02d:%02d.%03d] - %s/%s: ", min_r, sec_r, ms_r, level_desc.c_str(), tag);
            cons->vprintf(fmt, args);
            cons->printf("\n");
        }

        static Logcat *shared_lc = nullptr;

        Logcat *Shared() {
            ;
            if (shared_lc == nullptr) {
                shared_lc = new Logcat;
            }
            return shared_lc;
        }

        Logcat::Logcat() : _sinks() {}

        Logcat::~Logcat() = default;

        void Logcat::AddSink(ISink *sink) {
            _sinks.push_back(sink);
        }

        void Logcat::ClearSinks() {
            _sinks.clear();
        }

        void Logcat::SetLevelGlobal(level::LevelType level) {
            for (auto s : _sinks) {
                s->SetLevel(level);
            }
        }

        void Logcat::V(const char *tag, const char *fmt, ...) {
            std::va_list args;
            va_start(args, fmt);
            DoLog(level::VERBOSE, tag, fmt, args);
            va_end(args);
        }

        void Logcat::D(const char *tag, const char *fmt, ...) {
            std::va_list args;
            va_start(args, fmt);
            DoLog(level::DEBUG, tag, fmt, args);
            va_end(args);
        }

        void Logcat::I(const char *tag, const char *fmt, ...) {
            std::va_list args;
            va_start(args, fmt);
            DoLog(level::INFO, tag, fmt, args);
            va_end(args);
        }

        void Logcat::W(const char *tag, const char *fmt, ...) {
            std::va_list args;
            va_start(args, fmt);
            DoLog(level::WARN, tag, fmt, args);
            va_end(args);
        }

        void Logcat::E(const char *tag, const char *fmt, ...) {
            std::va_list args;
            va_start(args, fmt);
            DoLog(level::ERROR, tag, fmt, args);
            va_end(args);
        }

        void Logcat::WTF(const char *tag, const char *fmt, ...) {
            std::va_list args;
            va_start(args, fmt);
            DoLog(level::WTF, tag, fmt, args);
            va_end(args);
        }

        /* Private */

        void Logcat::DoLog(level::LevelType level, const char *tag, const char *fmt, va_list const &args) {
            for (auto s : _sinks) {
                s->Log(level, tag, fmt, args);
            }
            if (level == level::WTF) {
                exit(-1);
            }
        }
    }
}