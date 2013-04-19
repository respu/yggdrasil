#ifndef MONGO_BASE_TIMING_TIMESTAMP_HPP_INCLUDED
#define MONGO_BASE_TIMING_TIMESTAMP_HPP_INCLUDED


#include "base/basic_types.hpp"
#include <boost/operators.hpp>

namespace mongo { namespace timing {

///
/// Time stamp in UTC, in microseconds resolution.
///
/// This class is immutable.
/// It's recommended to pass it by value, since it's passed in register on x64.
///
class timestamp : public boost::less_than_comparable<timestamp>
{
 public:
  ///
  /// Constucts an invalid Timestamp.
  ///
  timestamp()
    : microSecondsSinceEpoch_(0)
  {
  }

  ///
  /// Constucts a Timestamp at specific time
  ///
  /// @param microSecondsSinceEpoch
  explicit timestamp(int64_t microSecondsSinceEpoch);

  void swap(timestamp& that)
  {
    std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
  }

  // default copy/assignment/dtor are Okay

  std::string toString() const;
  std::string toFormattedString() const;

  bool valid() const { return microSecondsSinceEpoch_ > 0; }

  // for internal usage.
  int64_t microSecondsSinceEpoch() const { return microSecondsSinceEpoch_; }
  time_t secondsSinceEpoch() const
  { return static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond); }

  ///
  /// Get time of now.
  ///
  static timestamp now();
  static timestamp invalid();

  static const int kMicroSecondsPerSecond = 1000 * 1000;

 private:
  int64_t microSecondsSinceEpoch_;
};

inline bool operator<(timestamp lhs, timestamp rhs)
{
  return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
}

inline bool operator==(timestamp lhs, timestamp rhs)
{
  return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
}

///
/// Gets time difference of two timestamps, result in seconds.
///
/// @param high, low
/// @return (high-low) in seconds
/// @c double has 52-bit precision, enough for one-microseciond
/// resolution for next 100 years.
inline double timeDifference(timestamp high, timestamp low)
{
  int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
  return static_cast<double>(diff) / timestamp::kMicroSecondsPerSecond;
}

///
/// Add @c seconds to given timestamp.
///
/// @return timestamp+seconds as timestamp
///
inline timestamp addTime(timestamp ts, double seconds)
{
  int64_t delta = static_cast<int64_t>(seconds * timestamp::kMicroSecondsPerSecond);
  return timestamp(ts.microSecondsSinceEpoch() + delta);
}

} // namespace timing
} // namespace mongo

#endif // MONGO_BASE_TIMING_TIMESTAMP_HPP_INCLUDED
