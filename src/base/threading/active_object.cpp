#include "base/threading/active_object.hpp"


using namespace mongo::threading;


active_object::active_object(): m_done(false)
{
}

active_object::~active_object() {
  callback quit_token = std::bind(&active_object::do_done, this);
  send(quit_token); // tell thread to exit
  m_thread.join();
}

// Add asynchronously a work-message to queue
void active_object::send(callback msg_){
  m_queue.push(msg_);
}


// Will wait for msgs if queue is empty
// A great explanation of how this is done (using Qt's library):
// http://doc.qt.nokia.com/stable/qwaitcondition.html
void active_object::run() {
  while (!m_done) {
    // wait till job is available, then retrieve it and
    // executes the retrieved job in this thread (background)
    callback func;
    m_queue.wait_and_pop(func);
    func();
  }
}

// Factory: safe construction of object before thread start
std::unique_ptr<active_object> active_object::create_active(){
  std::unique_ptr<active_object> ptr(new active_object());

  ptr->m_thread = std::thread(&active_object::run, ptr.get());
  return ptr;
}
