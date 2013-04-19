#include "base/timing/time_util.hpp"

#include <sstream>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>
#include <iomanip>


namespace mongo { namespace timing { namespace internal {
  // This mimics the original "std::put_time(const std::tm* tmb, const charT* fmt)"
  // This is needed since latest version (at time of writing) of gcc4.7 does not implement this library function yet.
  // return value is SIMPLIFIED to only return a std::string
  std::string put_time(const struct tm* tmb, const char* c_time_format)
  {
    const size_t size = 1024;
    char buffer[size]; // OBS: kolla om inte std::put_time finns. This is way more buffer space then we need
    auto success = std::strftime(buffer, size, c_time_format, tmb); // Ta över denna funktion till BitBucket/code/g2log sen då denna är utvecklingsbranchen
    if (0 == success)
      return c_time_format; // error return result indeterminate due to buffer overflow - should throw instead?
    return buffer; // implicit conversion to std::string
  }
} // namespace internal

std::time_t systemtime_now()
{
  system_time_point system_now = std::chrono::system_clock::now();
  return std::chrono::system_clock::to_time_t(system_now);
}

tm localtime(const std::time_t& time)
{
  struct tm tm_snapshot;
  localtime_r(&time, &tm_snapshot);
  return tm_snapshot;
}

/// returns a std::string with content of time_t as localtime formatted by input format string
/// * format string must conform to std::put_time
/// This is similar to std::put_time(std::localtime(std::time_t*), time_format.c_str());
std::string localtime_formatted(const std::time_t& time_snapshot, const std::string& time_format)
{
  const std::tm t = localtime(time_snapshot);
  std::stringstream buffer;
  buffer << internal::put_time(&t, time_format.c_str());  // format example: //"%Y/%m/%d %H:%M:%S");
  return buffer.str();
}
} // namespace timing
} // namespace mongo
