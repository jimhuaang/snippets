
#include "base/ThreadPool.h"

#include "boost/foreach.hpp"
#include "boost/thread/locks.hpp"
#include "boost/thread/mutex.hpp"

#include "base/TaskHandle.h"

namespace QS {

namespace Threading {

using boost::lock_guard;
using boost::mutex;

// --------------------------------------------------------------------------
ThreadPool::ThreadPool(size_t poolSize) : m_poolSize(poolSize) {}

// --------------------------------------------------------------------------
ThreadPool::~ThreadPool() {
  StopProcessing();

  BOOST_FOREACH (TaskHandle *taskHandle, m_taskHandles) { delete taskHandle; }

  while (!m_tasks.empty()) {
    Task *task = m_tasks.front();
    m_tasks.pop_front();
    if (task) {
      delete task;
    }
  }
}

// --------------------------------------------------------------------------
void ThreadPool::SubmitToThread(const Task &task, bool prioritized) {
  {
    lock_guard<mutex> lock(m_queueLock);
    Task *taskCpy = new Task(task);
    if (prioritized) {
      m_tasks.push_front(taskCpy);
    } else {
      m_tasks.push_back(taskCpy);
    }
    taskCpy = NULL;
  }
  lock_guard<mutex> lock(m_syncLock);
  m_syncConditionVar.notify_one();
}

// --------------------------------------------------------------------------
Task *ThreadPool::PopTask() {
  lock_guard<mutex> lock(m_queueLock);
  if (!m_tasks.empty()) {
    Task *task = m_tasks.front();
    if (task) {
      m_tasks.pop_front();
      return task;
    }
  }
  return NULL;
}

// --------------------------------------------------------------------------
bool ThreadPool::HasTasks() {
  lock_guard<mutex> lock(m_queueLock);
  return !m_tasks.empty();
}

// --------------------------------------------------------------------------
void ThreadPool::Initialize() {
  for (size_t i = 0; i < m_poolSize; ++i) {
    m_taskHandles.push_back(new TaskHandle(*this));
  }
}

// --------------------------------------------------------------------------
void ThreadPool::StopProcessing() {
  BOOST_FOREACH(TaskHandle *taskHandle, m_taskHandles) { taskHandle->Stop(); }
  lock_guard<mutex> lock(m_syncLock);
  m_syncConditionVar.notify_all();
}

}  // namespace Threading
}  // namespace QS
