//
// Created by jeff on 11/22/17.
//

#ifndef FRDM_FAN_CONTROL_LOGCAT_H
#define FRDM_FAN_CONTROL_LOGCAT_H

#include <string>
#include <vector>
#include <cstdarg>
#include <drivers/Timer.h>

namespace frdm_fc {
    namespace logcat {

        namespace level {
            enum LevelType {
                VERBOSE = 0,
                DEBUG   = 1,
                INFO    = 2,
                WARN    = 3,
                ERROR   = 4,
                WTF     = 5
            };

            std::string GetDesc(level::LevelType level);
        }

        class ISink {
        public:
            virtual level::LevelType GetLevel() = 0;

            virtual void SetLevel(level::LevelType level) = 0;

            virtual void Log(level::LevelType level, const char *tag, const char *fmt, va_list const &args) = 0;
        };

        class ConsoleSink : public ISink {
        public:
            explicit ConsoleSink(level::LevelType level = level::VERBOSE);

            ~ConsoleSink();

            level::LevelType GetLevel() override;

            void SetLevel(level::LevelType level) override;

            void Log(level::LevelType level, const char *tag, const char *fmt, va_list const &args) override;

        private:
            level::LevelType _level;
            mbed::Timer      _timer;
        };

        class Logcat {
        public:
            Logcat();

            virtual ~Logcat();

            void AddSink(ISink *sink);

            void ClearSinks();

            void SetLevelGlobal(level::LevelType level);

            void V(const char *tag, const char *fmt, ...);

            void D(const char *tag, const char *fmt, ...);

            void I(const char *tag, const char *fmt, ...);

            void W(const char *tag, const char *fmt, ...);

            void E(const char *tag, const char *fmt, ...);

            void WTF(const char *tag, const char *fmt, ...);

        private:
            std::vector<ISink *> _sinks;

            void DoLog(level::LevelType level, const char *tag, const char *fmt, va_list const &args);
        };

        Logcat *Shared();
    }
}

#endif //FRDM_FAN_CONTROL_LOGCAT_H
