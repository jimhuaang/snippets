#ifndef QSFS_BASE_SINGLETON_HPP_
#define QSFS_BASE_SINGLETON_HPP_

#include "boost/noncopyable.hpp"
#include "boost/scoped_ptr.hpp"
#include "boost/thread/once.hpp"

//
// Use:
// class YourClass : public Singleton<YourClass> {
// public:
//   void YourMethod() { }
// private:
//   YourClass() { /* init */ }
//   friend class Singleton<YourClass>;
// };
//
// Using Your Singleton:
// YourClass::Instance().YourMethod();
//
//
template <typename T>
class Singleton : private boost::noncopyable {
 public:
  static T& Instance() {
    boost::call_once(m_flag, Init);
    return *m_instance;
  }

 protected:
  static void Init() { m_instance.reset(new T); }

 protected:
  Singleton() {}
  virtual ~Singleton() {}

 private:
  static boost::scoped_ptr<T> m_instance;
  static boost::once_flag m_flag;
};

template <typename T>
boost::scoped_ptr<T> Singleton<T>::m_instance(0);

template <typename T>
boost::once_flag Singleton<T>::m_flag = BOOST_ONCE_INIT;


#endif  // QSFS_BASE_SINGLETON_HPP_
