#include "jetslog.h"
#include <cstdlib>
#include <ctime>

namespace jets
{

std::ofstream JetsLogger::_error_log_file;
std::ofstream JetsLogger::_warn_log_file;
std::ofstream JetsLogger::_info_log_file;


void jetsLogInit(const std::string& info_log_filename,
                 const std::string& warn_log_filename,
                 const std::string& error_log_filename)
{
    JetsLogger::_info_log_file.open(info_log_filename.c_str());
    JetsLogger::_warn_log_file.open(warn_log_filename.c_str());
    JetsLogger::_error_log_file.open(error_log_filename.c_str());

}

std::ostream& JetsLogger::get_stream(LogLevel level)
{
    return (INFO == level) ?
        (_info_log_file.is_open() ? _info_log_file : std::cout) :
        (WARN == level ?
            (_warn_log_file.is_open() ? _warn_log_file : std::cerr) :
            (_error_log_file.is_open() ? _error_log_file : std::cerr));
}


std::ostream& JetsLogger::start(LogLevel level,
                            const int32_t line,
                            const std::string& function)
{
    time_t tm;
    time(&tm);
    char time_string[128];
    ctime_r(&tm, time_string);
    return get_stream(level) << time_string
        << "function (" << function << ")"
        << "line " << line << ": "
        << std::flush;
}

JetsLogger::~JetsLogger()
{
    get_stream(_level) << std::endl << std::flush;

    if (FATAL == _level)
    {
        _info_log_file.close();
        _info_log_file.close();
        _info_log_file.close();
        abort();
    }
}
} // namespace jets