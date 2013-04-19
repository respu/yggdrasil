#ifndef MONGO_BASE_EXCEPTION_HPP_INCLUDED
#define MONGO_BASE_EXCEPTION_HPP_INCLUDED


#include "base/format.hpp"

#include <exception>


namespace mongo {

struct exception :
    public std::exception
{
    static constexpr std::size_t backtrace_size = 20;

    template<typename... Args>
    exception(const std::string& format, const Args&... args):
        m_message(mongo::format(format, args...))
    {
        fill_stacktrace();
    }

    virtual
   ~exception() throw() {
        // Empty.
    }

    virtual
    const char*
    what() const throw() {
        return m_message.c_str();
    }

    const char*
    stackTrace() const throw() {
        return m_stackTrace.c_str();
    }

private:
    void fill_stacktrace();
    const std::string m_message;
    std::string m_stackTrace;
};

} // namespace mongo

#endif // MONGO_BASE_EXCEPTION_HPP_INCLUDED
