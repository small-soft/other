/*
 * -------------------------------------------------------------
 *
 * Module: semaphore.c
 *
 * Purpose:
 *      Semaphores aren't actually part of the PThreads standard.
 *      They are defined by the POSIX Standard:
 *
 *              POSIX 1003.1b-1993      (POSIX.1b)
 *
 * Contents:
 *              Public Methods                    Author
 *              --------------                    ------
 *              sem_init                          John E. Bossom  Mar 1998
 *              sem_destroy                       John E. Bossom  Mar 1998
 *              sem_trywait                       John E. Bossom  Mar 1998
 *              sem_wait                          John E. Bossom  Mar 1998
 *              sem_post                          John E. Bossom  Mar 1998
 *
 *              Private Methods
 *              ---------------
 *
 * -------------------------------------------------------------
 *
 * Pthreads-win32 - POSIX Threads Library for Win32
 * Copyright (C) 1998
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA
 */

#include <windows.h>
//#include <process.h>
//#include <sys/timeb.h>
#include <string.h>

#include "pthread.h"
#include "semaphore.h"

int
sem_init (sem_t * sem, int pshared, unsigned int value)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function initializes an unnamed semaphore. the
      *      initial value of the semaphore is 'value'
      *
      * PARAMETERS
      *      sem
      *              pointer to an instance of sem_t
      *
      *      pshared
      *              if zero, this semaphore may only be shared between
      *              threads in the same process.
      *              if nonzero, the semaphore can be shared between
      *              processes
      *
      *      value
      *              initial value of the semaphore counter
      *
      * DESCRIPTION
      *      This function initializes an unnamed semaphore. The
      *      initial value of the semaphore is set to 'value'.
      *
      * RESULTS
      *              0               successfully created semaphore,
      *              -1              failed, error in errno
      * ERRNO
      *              EINVAL          'sem' is not a valid semaphore,
      *              ENOSPC          a required resource has been exhausted,
      *              ENOSYS          semaphores are not supported,
      *              EPERM           the process lacks appropriate privilege
      *
      * ------------------------------------------------------
      */
{
  int result = 0;


  if (pshared != 0)
    {
      /*
       * Creating a semaphore that can be shared between
       * processes
       */
      result = EPERM;

    }
  else
    {
#ifdef NO_SEM

	  sem->value = value;
	  /* sem->mutex = CreateMutex (NULL,
										FALSE,
										NULL); */
	  pthread_mutex_init(&sem->mutex, NULL);
	  sem->event = CreateEvent (NULL,
										FALSE,	/* manual reset */
										FALSE,	/* initial state */
										NULL);
	  if (value != 0) {
		  SetEvent(sem->event);
	  }
#else
     /*
       * NOTE: Taking advantage of the fact that
       *               sem_t is a simple structure with one entry;
       *               We don't have to allocate it...
       */
      *sem = CreateSemaphore (
			       0,
			       value,
			       0x7FFFFFF,
			       NULL);

      if (*sem == 0)
	{
	  result = ENOSPC;
	}
#endif
    }

  if (result != 0)
    {
      errno = result;
      return -1;
    }

  return 0;

}				/* sem_init */


int
sem_destroy (sem_t * sem)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function destroys an unnamed semaphore.
      *
      * PARAMETERS
      *      sem
      *              pointer to an instance of sem_t
      *
      * DESCRIPTION
      *      This function destroys an unnamed semaphore.
      *
      * RESULTS
      *              0               successfully destroyed semaphore,
      *              -1              failed, error in errno
      * ERRNO
      *              EINVAL          'sem' is not a valid semaphore,
      *              ENOSYS          semaphores are not supported,
      *              EBUSY           threads (or processes) are currently
      *                                      blocked on 'sem'
      *
      * ------------------------------------------------------
      */
{
  int result = 0;

  if (sem == NULL)
    {
      result = EINVAL;
    }
#ifdef NO_SEM
  else {
//		_msg_printf("sem_destroy 0x%08x\n", (unsigned int)sem);
      /* if (!CloseHandle(sem->mutex)) {
		result = EINVAL;
	  } */
	  pthread_mutex_destroy(&sem->mutex);
      if (!CloseHandle(sem->event)) {
		result = EINVAL;
	  }
    }
#else
  else if (! CloseHandle (*sem))
    {
      result = EINVAL;
    }
#endif

  if (result != 0)
    {
      errno = result;
      return -1;
    }

  return 0;

}				/* sem_destroy */


int
sem_trywait (sem_t * sem)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function tries to wait on a semaphore.
      *
      * PARAMETERS
      *      sem
      *              pointer to an instance of sem_t
      *
      * DESCRIPTION
      *      This function tries to wait on a semaphore. If the
      *      semaphore value is greater than zero, it decreases
      *      its value by one. If the semaphore value is zero, then
      *      this function returns immediately with the error EAGAIN
      *
      * RESULTS
      *              0               successfully decreased semaphore,
      *              -1              failed, error in errno
      * ERRNO
      *              EAGAIN          the semaphore was already locked,
      *              EINVAL          'sem' is not a valid semaphore,
      *              ENOSYS          semaphores are not supported,
      *              EINTR           the function was interrupted by a signal,
      *              EDEADLK         a deadlock condition was detected.
      *
      * ------------------------------------------------------
      */
{
  int result = 0;

  if (sem == NULL)
    {
      result = EINVAL;
    }
#ifdef NO_SEM
  /* not yet implemented! */
  result = EINVAL;
  return -1;
#else
  else if (WaitForSingleObject (*sem, 0) == WAIT_TIMEOUT)
    {
      result = EAGAIN;
    }
#endif

  if (result != 0)
    {
      errno = result;
      return -1;
    }

  return 0;

}				/* sem_trywait */

#ifdef NO_SEM
void 
_decrease_semaphore(sem_t * sem)
{
	/*WaitForSingleObject(sem->mutex, INFINITE);*/
	pthread_mutex_lock(&sem->mutex);
	if (sem->value != 0) {
//		_msg_printf("_decrease_semaphore 0x%08x: %u -> %u\n", (unsigned int)sem, sem->value, sem->value - 1);
		sem->value--;
		if (sem->value != 0) {
//			_msg_printf("_decrease_semaphore signals event\n");
			SetEvent(sem->event);
		}
	} else {
//		_msg_printf("_decrease_semaphore aborting\n");
//		abort();
		/* this case should not happen! */
	}
	/*ReleaseMutex(sem->mutex);*/
	pthread_mutex_unlock(&sem->mutex);
}

BOOL 
_increase_semaphore(sem_t * sem, unsigned int n)
{
	BOOL result;

//	_msg_printf("_increase_semaphore 0x%08x: %u -> %u\n", (unsigned int)sem, sem->value, sem->value + n);
	/*WaitForSingleObject(sem->mutex, INFINITE);*/
	pthread_mutex_lock(&sem->mutex);
	if (sem->value + n > sem->value) {
		sem->value += n;
//		_msg_printf("_increase_semaphore signals event\n");
		SetEvent(sem->event);
		result = TRUE;
	} else {
//		_msg_printf("_increase_semaphore fails\n");
		result = FALSE;
	}
	/*ReleaseMutex(sem->mutex);*/
	pthread_mutex_unlock(&sem->mutex);
	return result;
}

#endif

int
sem_wait (sem_t * sem)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function  waits on a semaphore.
      *
      * PARAMETERS
      *      sem
      *              pointer to an instance of sem_t
      *
      * DESCRIPTION
      *      This function waits on a semaphore. If the
      *      semaphore value is greater than zero, it decreases
      *      its value by one. If the semaphore value is zero, then
      *      the calling thread (or process) is blocked until it can
      *      successfully decrease the value or until interrupted by
      *      a signal.
      *
      * RESULTS
      *              0               successfully decreased semaphore,
      *              -1              failed, error in errno
      * ERRNO
      *              EINVAL          'sem' is not a valid semaphore,
      *              ENOSYS          semaphores are not supported,
      *              EINTR           the function was interrupted by a signal,
      *              EDEADLK         a deadlock condition was detected.
      *
      * ------------------------------------------------------
      */
{
  int result = 0;

  if (sem == NULL)
    {
      result = EINVAL;
    }
  else
    {
#ifdef NO_SEM
	result = pthreadCancelableWait (sem->event);
#else
	result = pthreadCancelableWait (*sem);
#endif
    }

  if (result != 0)
    {
      errno = result;
      return -1;
    }
#ifdef NO_SEM
  _decrease_semaphore(sem);
#endif

  return 0;

}				/* sem_wait */


int
sem_post (sem_t * sem)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function posts a wakeup to a semaphore.
      *
      * PARAMETERS
      *      sem
      *              pointer to an instance of sem_t
      *
      * DESCRIPTION
      *      This function posts a wakeup to a semaphore. If there
      *      are waiting threads (or processes), one is awakened;
      *      otherwise, the semaphore value is incremented by one.
      *
      * RESULTS
      *              0               successfully posted semaphore,
      *              -1              failed, error in errno
      * ERRNO
      *              EINVAL          'sem' is not a valid semaphore,
      *              ENOSYS          semaphores are not supported,
      *
      * ------------------------------------------------------
      */
{
  int result = 0;

  if (sem == NULL)
    {
	result = EINVAL;
    }
#ifdef NO_SEM
  else if (! _increase_semaphore (sem, 1))

#else

  else if (! ReleaseSemaphore (*sem, 1, 0))
#endif
    {
	result = EINVAL;
    }

  if (result != 0)
    {
      errno = result;
      return -1;
    }

  return 0;

}				/* sem_post */


int
sem_open (const char * name, int oflag, mode_t mode, unsigned int value)
{
  errno = ENOSYS;
  return -1;
}				/* sem_open */


int
sem_close (sem_t * sem)
{
  errno = ENOSYS;
  return -1;
}				/* sem_close */


int
sem_unlink (const char * name)
{
  errno = ENOSYS;
  return -1;
}				/* sem_unlink */


int
sem_getvalue (sem_t * sem, int * sval)
{
  errno = ENOSYS;
  return -1;
}				/* sem_getvalue */

