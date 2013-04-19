#ifndef MONGO_BASE_FORMAT_HPP_INCLUDED
#define MONGO_BASE_FORMAT_HPP_INCLUDED


#include <boost/format.hpp>

namespace mongo {

namespace detail {
    static inline
    std::string
    substitute(boost::format&& message) {
        return message.str();
    }

    template<typename T, typename... Args>
    static inline
    std::string
    substitute(boost::format&& message, const T& argument, const Args&... args) {
        return substitute(std::move(message % argument), args...);
    }
}

template<typename... Args>
static inline
std::string
format(const std::string& format, const Args&... args) {
    try {
        return detail::substitute(boost::format(format), args...);
    } catch(const boost::io::format_error& e) {
        return "<unable to format the message>";
    }
}

} // namespace mongo
#endif // MONGO_BASE_FORMAT_HPP_INCLUDED
