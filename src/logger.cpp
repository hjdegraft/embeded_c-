#include <cstdio>
#include <cstdarg>
#include "logger.h"
#include <syslog.h>

#define OUTPUT_CONSOLE(prefix, fmt, args, stream) \
    do { \
        fprintf(stream, prefix); \
        vfprintf(stream, fmt, args); \
        fprintf(stream, "\n"); \
    } while(0)

using namespace densityd;

namespace
{
    class logger
    {
    public:
        virtual void trace(const char* fmt, va_list ap) = 0;
        virtual void debug(const char* fmt, va_list ap) = 0;
        virtual void info(const char* fmt, va_list ap) = 0;
        virtual void warn(const char* fmt, va_list ap) = 0;
        virtual void error(const char* fmt, va_list ap) = 0;

        virtual ~logger()
        {}
    };
    class console_logger : public logger
    {
        log_level m_log_level;

    public:

        console_logger(log_level level)
            : logger(),
              m_log_level(level)
        {}

        void trace(const char* fmt, va_list ap) override
        {
            if(m_log_level <= log_level::trace)
                OUTPUT_CONSOLE("TRACE: ", fmt, ap, stderr);
        }

        void debug(const char* fmt, va_list ap) override
        {
            if(m_log_level <= log_level::debug)
                OUTPUT_CONSOLE("DEBUG: ", fmt, ap, stderr);
        }

        void info(const char* fmt, va_list ap) override
        {
            if(m_log_level <= log_level::info)
                OUTPUT_CONSOLE("INFO: ", fmt, ap, stdout);
                }
 59 
 60         void warn(const char* fmt, va_list ap) override
 61         {
 62             if(m_log_level <= log_level::warn)
 63                 OUTPUT_CONSOLE("WARNING: ", fmt, ap, stderr);
 64         }
 65 
 66         void error(const char* fmt, va_list ap) override
 67         {
 68             if(m_log_level <= log_level::error)
 69                 OUTPUT_CONSOLE("ERROR: ", fmt, ap, stderr);
 70         }
 71 
 72         ~console_logger()
 73         {}
 74     };
 75 
 76     class syslog_logger : public logger
 77     {
 78     public:
 79 
 80         syslog_logger()
 81         {
 82             ::openlog("configd", LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_LOCAL0);
 83         }
 void trace(const char* fmt, va_list ap) override
 86         {
 87             vsyslog(LOG_DEBUG, fmt, ap);
 88         }
 89 
 90         void debug(const char* fmt, va_list ap) override
 91         {
 92             vsyslog(LOG_DEBUG, fmt, ap);
 93         }
 94 
 95         void info(const char* fmt, va_list ap) override
 96         {
 97             vsyslog(LOG_INFO, fmt, ap);
 98         }
 99 
100         void warn(const char* fmt, va_list ap) override
101         {
102             vsyslog(LOG_WARNING, fmt, ap);
103         }
104 
105         void error(const char* fmt, va_list ap) override
106         {
107             vsyslog(LOG_ERR, fmt, ap);
108         }
109 
110         ~syslog_logger()
111         {}
};
113 
114     std::unique_ptr<logger> _logger(new console_logger(log_level::trace));
115 }
116 
117 log_level densityd::parse_log_level(const std::string& ll_str)
118 {
119     if(ll_str == "trace")
120     {
121         return log_level::trace;
122     }
123     else if(ll_str == "debug")
124     {
125         return log_level::debug;
126     }
127     else if(ll_str == "info")
128     {
129         return log_level::info;
130     }
131     else if(ll_str == "warn")
132     {
133         return log_level::warn;
134     }
135     else if(ll_str == "error")
136     {
137         return log_level::error;
138     }
else
140     {
141         throw std::runtime_error("Unknown log level string: " + ll_str);
142     }
143 }
144 
145 void densityd::trace(const std::string& fmt, ...)
146 {
147     va_list ap;
148     va_start(ap, fmt);
149     _logger->trace(fmt.c_str(), ap);
150     va_end(ap);
151 }
152 
153 void densityd::debug(const std::string& fmt, ...)
154 {
155     va_list ap;
156     va_start(ap, fmt);
157     _logger->debug(fmt.c_str(), ap);
158     va_end(ap);
159 }
160 
161 void densityd::info(const std::string& fmt, ...)
162 {
163     va_list ap;
164     va_start(ap, fmt);
165     _logger->info(fmt.c_str(), ap);
166     va_end(ap);
 }
168 
169 void densityd::warn(const std::string& fmt, ...)
170 {
171     va_list ap;
172     va_start(ap, fmt);
173     _logger->warn(fmt.c_str(), ap);
174     va_end(ap);
175 }
176 
177 void densityd::error(const std::string& fmt, ...)
178 {
179     va_list ap;
180     va_start(ap, fmt);
181     _logger->error(fmt.c_str(), ap);
182     va_end(ap);
183 }
184 
185 void densityd::use_syslog_logging()
186 {
187     _logger = std::make_unique<syslog_logger>();
188 }
189 
190 void densityd::use_console_logging(log_level level)
191 {
192     _logger = std::make_unique<console_logger>(level);
193 }
