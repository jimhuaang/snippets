
#include "base/ThreadPoolInitializer.h"

#include "boost/foreach.hpp"

#include "base/ThreadPool.h"


namespace QS {

namespace Threading {

// --------------------------------------------------------------------------
void ThreadPoolInitializer::DoInitialize() {
  BOOST_FOREACH(ThreadPool *threadpool, m_threadPools) {
    if (threadpool != NULL) {
      threadpool->Initialize();
    }
  }
}

// --------------------------------------------------------------------------
void ThreadPoolInitializer::Register(ThreadPool *threadpool) {
  m_threadPools.insert(threadpool);
}

// --------------------------------------------------------------------------
void ThreadPoolInitializer::UnRegister(ThreadPool *threadpool) {
  m_threadPools.erase(threadpool);
}

}  // namespace Threading
}  // namespace QS
