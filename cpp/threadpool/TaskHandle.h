
#ifndef QSFS_BASE_TASKHANDLE_H_
#define QSFS_BASE_TASKHANDLE_H_

#include "boost/noncopyable.hpp"
#include "boost/thread/shared_mutex.hpp"
#include "boost/thread/thread.hpp"

namespace QS {

namespace Threading {

class ThreadPool;

class TaskHandle : private boost::noncopyable {
 public:
  explicit TaskHandle(ThreadPool &threadPool);  // NOLINT
  ~TaskHandle();

 private:
  void Stop();
  void operator()();

  bool ShouldContinue() const;
  bool Predicate() const;

 private:
  bool m_continue;
  mutable boost::shared_mutex m_continueLock;
  ThreadPool &m_threadPool;
  boost::thread m_thread;

  friend class ThreadPool;
};

}  // namespace Threading
}  // namespace QS


#endif  // QSFS_BASE_TASKHANDLE_H_
