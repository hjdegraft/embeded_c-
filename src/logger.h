#ifndef LIBDENSITYD_LOGGER_H
#define LIBDENSITYD_LOGGER_H

#include <memory>

namespace densityd {

    enum class log_level : int
    {
        trace,
        debug,
        info,
        warn,
        error
    };

    log_level parse_log_level(const std::string& ll_str);

    void trace(const std::string& fmt, ...);
    void debug(const std::string& fmt, ...);
    void info(const std::string& fmt, ...);
    void warn(const std::string& fmt, ...);
    void error(const std::string& fmt, ...);

    void use_syslog_logging();
    void use_console_logging(log_level level);

}
