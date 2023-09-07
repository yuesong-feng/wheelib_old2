/*-------------------------------------------------------------------------
 *
 * thread.h
 *	  thread system for wheelib
 *
 * Portions Copyright (c) 2023, yuesong-feng 冯岳松
 *
 *
 * IDENTIFICATION
 *	  src/thrd.h
 *
 *
 * NOTES
 *	  thread system
 *
 *-------------------------------------------------------------------------
 */
#ifndef THREAD_H
#define THREAD_H
#include "type.h"
#include <assert.h>
#include <pthread.h>

typedef struct mutex_struct mutex_t;
struct mutex_struct {
  pthread_mutex_t mutex;
};

static inline void mutex_init(mutex_t* mtx) {
  assert(pthread_mutex_init(&(mtx->mutex), NULL) == 0);
}

static inline void mutex_destroy(mutex_t* mtx) {
  assert(pthread_mutex_destroy(&(mtx->mutex)) == 0);
}

static inline void mutex_lock(mutex_t* mtx) {
  assert(pthread_mutex_lock(&(mtx->mutex)) == 0);
}

static inline void mutex_unlock(mutex_t* mtx) {
  assert(pthread_mutex_unlock(&(mtx->mutex)) == 0);
}

typedef struct event_struct event_t;
struct event_struct {
  bool is_set;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
};

static inline void event_init(event_t* evt) {
  evt->is_set = false;
  assert(pthread_mutex_init(&(evt->mutex), NULL) == 0);
  assert(pthread_cond_init(&(evt->cond), NULL) == 0);
}

static inline void event_destroy(event_t* evt) {
  assert(pthread_cond_destroy(&(evt->cond)) == 0);
  assert(pthread_mutex_destroy(&(evt->mutex)) == 0);
}

static inline void event_wait(event_t* evt) {
  assert(pthread_mutex_lock(&(evt->mutex)) == 0);
  if (evt->is_set == true) {
    assert(pthread_mutex_unlock(&(evt->mutex)) == 0);
    return;
  }
  assert(pthread_cond_wait(&(evt->cond), &(evt->mutex)) == 0);
  assert(pthread_mutex_unlock(&(evt->mutex)) == 0);
}

static inline void event_set(event_t* evt) {
  assert(pthread_mutex_lock(&(evt->mutex)) == 0);
  if (evt->is_set == true) {
    assert(pthread_mutex_unlock(&(evt->mutex)) == 0);
    return;
  }
  evt->is_set = true;
  assert(pthread_cond_broadcast(&(evt->cond)) == 0);
  assert(pthread_mutex_unlock(&(evt->mutex)) == 0);
}

static inline void event_reset(event_t* evt) {
  assert(pthread_mutex_lock(&(evt->mutex)) == 0);
  evt->is_set = false;
  assert(pthread_mutex_unlock(&(evt->mutex)) == 0);
}

typedef struct semaphore_struct semaphore_t;
struct semaphore_struct {
  int v;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
};

static inline void semaphore_init(semaphore_t* sema, int v) {
  sema->v = v;
  assert(pthread_mutex_init(&(sema->mutex), NULL) == 0);
  assert(pthread_cond_init(&(sema->cond), NULL) == 0);
}

static inline void semaphore_destroy(semaphore_t* sema) {
  assert(pthread_cond_destroy(&(sema->cond)) == 0);
  assert(pthread_mutex_destroy(&(sema->mutex)) == 0);
}

static inline void semaphore_p(semaphore_t* sema) {
  assert(pthread_mutex_lock(&(sema->mutex)) == 0);
  while (sema->v <= 0) {
    assert(pthread_cond_wait(&(sema->cond), &(sema->mutex)) == 0);
  }
  (sema->v)--;
  assert(pthread_mutex_unlock(&(sema->mutex)) == 0);
}

static inline void semaphore_v(semaphore_t* sema) {
  assert(pthread_mutex_lock(&(sema->mutex)) == 0);
  (sema->v)++;
  assert(pthread_mutex_unlock(&(sema->mutex)) == 0);
  assert(pthread_cond_signal(&(sema->cond)) == 0);
}

static inline pthread_t thread_create(void* func, void* arg) {
  pthread_t thread;
  assert(pthread_create(&thread, NULL, func, arg) == 0);
  return thread;
}

#endif
