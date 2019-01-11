#ifndef QSFS_BASE_THREADPOOLINITIALIZER_H_
#define QSFS_BASE_THREADPOOLINITIALIZER_H_

#include <set>

#include "base/Singleton.hpp"
#include "configure/IncludeFuse.h"

namespace QS {

namespace FileSystem {
void* qsfs_init(struct fuse_conn_info* conn);
}  // namespace FileSystem

namespace Threading {

class ThreadPool;

class ThreadPoolInitializer : public Singleton<ThreadPoolInitializer> {
 public:
  ~ThreadPoolInitializer() {}

 public:
  void Register(ThreadPool* threadPool);
  void UnRegister(ThreadPool* threadPool);

 private:
  void DoInitialize();
  friend void* QS::FileSystem::qsfs_init(struct fuse_conn_info* conn);

 private:
  ThreadPoolInitializer() {}

  std::set<ThreadPool*> m_threadPools;

  friend class Singleton<ThreadPoolInitializer>;
};

}  // namespace Threading
}  // namespace QS

#endif  // QSFS_BASE_THREADPOOLINITIALIZER_H_
