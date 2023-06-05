#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <sys/syscall.h>

class Mutex
{
public:
    Mutex()
        : holder_(0)
    {
        pthread_mutex_init(&mutex_, NULL);
    }

    ~Mutex()
    {
        assert(holder_ == 0);
        pthread_mutex_destroy(&mutex_);
    }

    void lock()
    {
        pthread_mutex_lock(&mutex_);
        holder_ = static_cast<pid_t>(::syscall(SYS_gettid));
    }

    void unlock()
    {
        holder_ = 0;
        pthread_mutex_unlock(&mutex_);
    }

private:
    pthread_mutex_t mutex_;
    pid_t holder_;
};