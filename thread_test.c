#include <stdlib.h>
#include <string.h>
#include "thrd.h"
#include "log.h"
#include "debug.h"

semaphore_t sem;
event_t evt1;
event_t evt2;

void th1() {
    semaphore_p(&sem);
    LOG_INFO("申请到了");
    semaphore_p(&sem);
    LOG_INFO("申请到了");
    event_set(&evt1);
}

void th2() {
    LOG_INFO("释放一个");
    semaphore_v(&sem);
    LOG_INFO("在释放一个");
    semaphore_v(&sem);
    event_set(&evt2);
}

int main(int argc, char const *argv[])
{
    event_init(&evt1);
    event_init(&evt2);
    char *a = malloc(1000);
    memset(a, 'a', 1000);
    
    semaphore_init(&sem, 0);

    thread_create(th1, NULL);
    thread_create(th2, NULL);
    event_wait(&evt1);
    event_wait(&evt2);
    print_mem(th1, 64);
    free(a);
    return 0;
}
