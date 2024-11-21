#include "jetscomm.h"
// #include "libmesh/libmesh.h"
// #include "libmesh/libmesh_common.h"
// #include "libmesh/print_trace.h"

namespace jets
{

sync::spin_mutex spin_mtx;

namespace MacroFunctions
{
void here(const char * file, int line, const char * date, const char * time, std::ostream & os)
{
  os << "[" << static_cast<std::size_t>(jets::global_processor_id()) << "] "
     << file
     << ", line " << line
     << ", compiled " << date
     << " at " << time
     << std::endl;
}

void stop(const char * file, int line, const char * date, const char * time)
{
//   if (jets::global_n_processors() == 1)
//     {
//       jets::MacroFunctions::here(file, line, date, time);
// #if defined(LIBMESH_HAVE_CSIGNAL) && defined(SIGSTOP)
//       libMesh::out << "Stopping process " << getpid() << "..." << std::endl;
//       std::raise(SIGSTOP);
//       libMesh::out << "Continuing process " << getpid() << "..." << std::endl;
// #else
//       jets::out << "WARNING:  libmesh_stop() does not work; no operating system support." << std::endl;
// #endif
//     }
}

void report_error(const char * file, int line, const char * date, const char * time, std::ostream & os)
{
  // It is possible to have an error *inside* report_error; e.g. from
  // print_trace.  We don't want to infinitely recurse.
  static bool reporting_error = false;
  if (reporting_error)
    {
      // I heard you like error reporting, so we put an error report
      // in report_error() so you can report errors from the report.
      os << "jets encountered an error while attempting to report_error." << std::endl;
      return;
    }
  reporting_error = true;

  // if (jets::global_n_processors() == 1 ||
  //     jets::on_command_line("--print-trace"))
  //   jets::print_trace(os);
  // else
  //   jets::write_traceout();
  jets::MacroFunctions::here(file, line, date, time, os);

  reporting_error = false;
}
} // namespace MacroFunctions

void sync::lock_singleton_spin_mutex() { spin_mtx.lock(); }
void sync::unlock_singleton_spin_mutex() { spin_mtx.unlock(); }
} // namespace jets