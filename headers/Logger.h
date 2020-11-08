#ifndef MIDIFACE_LOGGER_H
#define MIDIFACE_LOGGER_H

#include <cstdio>
#include <string>
#include <memory>

namespace MIDI
{
    enum class LogLevel {
        MF_DEBUG = 0b00000001,
        MF_INFO = 0b00000011,
        MF_ERROR = 0b00000111,
    };

    class BaseLogger
    {
    public:
        virtual ~BaseLogger() = 0;

        void debug(std::string message, ...);
        void info(std::string message, ...);
        void error(std::string message, ...);
    
    protected:
        virtual void send(const enum LogLevel, std::string message, ...) = 0;
        std::unique_ptr<std::ostream> output;
    };

    class LoggerAggregator : public BaseLogger
    {
    public:
        void enqueue_logger(const std::unique_ptr<BaseLogger>);

    protected:
        void send(const enum LogLevel, std::string message, ...);
    };
}
#endif //MIDIFACE_LOGGER_H
