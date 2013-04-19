#ifndef MONGO_BASE_TIMING_TIME_UTIL_HPP_INCLUDED
#define MONGO_BASE_TIMING_TIME_UTIL_HPP_INCLUDED

#include <ctime>
#include <string>
#include <chrono>

// NOTE :
// namespace mongo::internal ONLY in g2time.cpp
//          std::string put_time(const struct tm* tmb, const char* c_time_format)

namespace mongo { namespace timing {

  typedef std::chrono::steady_clock::time_point steady_time_point;
  typedef std::chrono::time_point<std::chrono::system_clock>  system_time_point;
  typedef std::chrono::milliseconds milliseconds;
  typedef std::chrono::microseconds microseconds;

  //  wrap for std::chrono::system_clock::now()
  std::time_t systemtime_now();

  /** return time representing POD struct (ref ctime + wchar) that is normally
  * retrieved with std::localtime. g2::localtime is threadsafe which std::localtime is not.
  * g2::localtime is probably used together with @ref g2::systemtime_now */
  tm localtime(const std::time_t& time);

  /** format string must conform to std::put_time's demands.
  * WARNING: At time of writing there is only so-so compiler support for
  * std::put_time. A possible fix if your c++11 library is not updated is to
  * modify this to use std::strftime instead */
  std::string localtime_formatted(const std::time_t& time_snapshot, const std::string& time_format) ;
} // namespace timing
} // namespace mongo

#endif // MONGO_BASE_TIMING_TIME_UTIL_HPP_INCLUDED
