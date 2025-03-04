#ifndef __JETS_LOG_H__
#define __JETS_LOG_H__

// C++ includes
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>

#include <stdint.h>

namespace jets
{

typedef enum _p_log_level
{
    INFO,
    WARN,
    ERROR,
    FATAL
} LogLevel;

void jetsLogInit(const std::string& info_log_filename,
                 const std::string& warn_log_filename,
                 const std::string& error_log_filename);

class JetsLogger
{

    friend void jetsLogInit(const std::string& info_log_filename,
                            const std::string& warn_log_filename,
                            const std::string& error_log_filename);

public:
    JetsLogger(LogLevel level): _level(level) {}

    ~JetsLogger();

    static std::ostream& start(LogLevel level,
                               const int32_t line,
                               const std::string& function);
private:
    LogLevel _level;

    static std::ostream& get_stream(LogLevel level);

    static std::ofstream _info_log_file;
    static std::ofstream _warn_log_file;
    static std::ofstream _error_log_file;
};

// Using ostream to log messages with different log levels.
#define JETS_LOG(log_rank)   \
jets::JetsLogger(log_rank).start(log_rank, __LINE__, __FUNCTION__)


// Some micros for checking.
#define JETS_CHECK(a)                                            \
   if(!(a)) {                                              \
       JETS_LOG(ERROR) << " CHECK failed " << endl              \
                   << #a << "= " << (a) << endl;          \
       abort();                                            \
   }                                                      \

#define JETS_CHECK_NOTNULL(a)                                    \
   if( NULL == (a)) {                                      \
       JETS_LOG(ERROR) << " CHECK_NOTNULL failed "              \
                   << #a << "== NULL " << endl;           \
       abort();                                            \
    }

#define JETS_CHECK_NULL(a)                                       \
   if( NULL != (a)) {                                      \
       JETS_LOG(ERROR) << " CHECK_NULL failed " << endl         \
                   << #a << "!= NULL " << endl;           \
       abort();                                            \
    }


#define JETS_CHECK_EQ(a, b)                                      \
   if(!((a) == (b))) {                                     \
       JETS_LOG(ERROR) << " CHECK_EQ failed "  << endl          \
                   << #a << "= " << (a) << endl           \
                   << #b << "= " << (b) << endl;          \
       abort();                                            \
    }

#define JETS_CHECK_NE(a, b)                                      \
   if(!((a) != (b))) {                                     \
       JETS_LOG(ERROR) << " CHECK_NE failed " << endl           \
                   << #a << "= " << (a) << endl           \
                   << #b << "= " << (b) << endl;          \
       abort();                                            \
    }

#define JETS_CHECK_LT(a, b)                                      \
   if(!((a) < (b))) {                                      \
       JETS_LOG(ERROR) << " CHECK_LT failed "                   \
                   << #a << "= " << (a) << endl           \
                   << #b << "= " << (b) << endl;          \
       abort();                                            \
    }

#define JETS_CHECK_GT(a, b)                                      \
   if(!((a) > (b))) {                                      \
       JETS_LOG(ERROR) << " CHECK_GT failed "  << endl          \
                  << #a <<" = " << (a) << endl            \
                   << #b << "= " << (b) << endl;          \
       abort();                                            \
    }

#define JETS_CHECK_LE(a, b)                                      \
   if(!((a) <= (b))) {                                     \
       JETS_LOG(ERROR) << " CHECK_LE failed "  << endl          \
                   << #a << "= " << (a) << endl           \
                   << #b << "= " << (b) << endl;          \
       abort();                                            \
    }

#define JETS_CHECK_GE(a, b)                                      \
   if(!((a) >= (b))) {                                     \
       JETS_LOG(ERROR) << " CHECK_GE failed "  << endl          \
                   << #a << " = "<< (a) << endl            \
                   << #b << "= " << (b) << endl;          \
       abort();                                            \
    }

#define JETS_CHECK_DOUBLE_EQ(a, b)                               \
   do {                                                    \
       JETS_CHECK_LE((a), (b)+0.000000000000001L);              \
       JETS_CHECK_GE((a), (b)-0.000000000000001L);              \
    }while (0)
} // namespace jets

#endif // __JETS_LOG_H__