# WebServer

首先我们对锁的控制封装为一个类`Mutex`，实现RALL机制

```
RAII

RAII全称是“Resource Acquisition is Initialization”，直译过来是“资源获取即初始化”.

在构造函数中申请分配资源，在析构函数中释放资源。因为C++的语言机制保证了，当一个对象创建的时候，自动调用构造函数，当对象超出作用域的时候会自动调用析构函数。所以，在RAII的指导下，我们应该使用类来管理资源，将资源和对象的生命周期绑定

RAII的核心思想是将资源或者状态与对象的生命周期绑定，通过C++的语言机制，实现资源和状态的安全管理,智能指针是RAII最好的例子
```

我们可以在`Mutex`中存放当前调用锁的线程，由于`pthread_t`指向的是一块动态分配的内存，导致它的值容易重复，所以需要使用`gettid(2)`系统调用返回值作为线程id。
