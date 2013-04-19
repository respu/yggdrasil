#ifndef MONGO_BASE_THREADING_ACTIVE_OBJECT_HPP_INCLUDED
#define MONGO_BASE_THREADING_ACTIVE_OBJECT_HPP_INCLUDED


#include <thread>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <memory>

#include "base/threading/shared_queue.hpp"

namespace mongo { namespace threading {

class active_object {

public:
    typedef std::function<void()> callback;
    /// destructor
    virtual ~active_object();
    /// send callback to execute
    void send(callback msg_);
    /// static factory function
  static std::unique_ptr<active_object> create_active(); // Factory: safe construction & thread start

private:
    active_object(const active_object&) = delete;
    active_object& operator=(const active_object&) = delete;
    active_object(); // Construction is done ONLY through factory create_active();

    void do_done() { m_done = true; }

    void run();

    shared_queue<callback> m_queue;
    std::thread m_thread;
    bool m_done;  // finished flag to be set through msg queue by ~active_object


};

} // namespace threading
} // namespace mongo

#endif // MONGO_BASE_THREADING_ACTIVE_OBJECT_HPP_INCLUDED
