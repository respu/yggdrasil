#include "base/exception.hpp"

#include <execinfo.h>
#include <stdlib.h> // free() TODO: get rid of C lib functions. Please!



namespace mongo {


void exception::fill_stacktrace() {
  void* buffer[backtrace_size];
  int nptrs = ::backtrace(buffer, backtrace_size);
  char** strings = ::backtrace_symbols(buffer, nptrs);
  if (strings)
  {
    for (int i = 0; i < nptrs; ++i)
    {
      // TODO : demangle funcion name with abi::__cxa_demangle
      m_stackTrace.append(strings[i]);
      m_stackTrace.push_back('\n');
    }
    free(strings);
  }
}

} // namespace mongo
