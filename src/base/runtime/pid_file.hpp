#ifndef MONGO_BASE_RUNTIME_PID_FILE_HPP_INCLUDED
#define MONGO_BASE_RUNTIME_PID_FILE_HPP_INCLUDED



#include "base/macros.hpp"

#include <boost/filesystem/path.hpp>

namespace mongo {

class pid_file {
    MONGO_DECLARE_NONCOPYABLE(pid_file)

    public:
        pid_file(const boost::filesystem::path& filepath);
       ~pid_file();

    private:
        void
        remove();

    private:
        const boost::filesystem::path m_filepath;
};

} // namespace mongo

#endif // MONGO_BASE_RUNTIME_PID_FILE_HPP_INCLUDED
