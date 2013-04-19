#include "base/runtime/pid_file.hpp"
#include "base/exception.hpp"
#include <csignal>

#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>

#include <sys/types.h>

using namespace mongo;

namespace fs = boost::filesystem;

pid_file::pid_file(const fs::path& filepath):
    m_filepath(filepath)
{
    // If the pidfile exists, check if the process is still active.
    if(fs::exists(m_filepath)) {
        pid_t pid;
        fs::ifstream stream(m_filepath);

        if(!stream) {
            throw mongo::exception("unable to read '%s'", m_filepath.string());
        }

        stream >> pid;

        if(::kill(pid, 0) < 0 && errno == ESRCH) {
            // Unlink the stale pid file.
            remove();
        } else {
            throw mongo::exception("another process is active");
        }
    }

    fs::ofstream stream(m_filepath);

    if(!stream) {
        throw mongo::exception("unable to write '%s'", m_filepath.string());
    }

    stream << ::getpid();
    stream.close();
}

pid_file::~pid_file() {
    try {
        remove();
    } catch(...) {
        // Do nothing.
    }
}

void
pid_file::remove() {
    try {
        fs::remove(m_filepath);
    } catch(const fs::filesystem_error& e) {
        throw mongo::exception("unable to remove '%s'", m_filepath.string());
    }
}
