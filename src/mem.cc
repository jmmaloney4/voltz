//
//  mem.cc
//  mach
//
//  Created by Jack Maloney on 12/5/14.
//
//

#include "mach.h"
#include <pthread.h>

pthread_mutex_t mem_mutex0;
pthread_mutex_t mem_mutex1;
pthread_mutex_t mem_mutex2;
pthread_mutex_t mem_mutex3;
pthread_mutex_t mem_mutex4;

void InitializeMutexes() {
    pthread_mutex_init(&mem_mutex0, (pthread_mutexattr_t*) NULL);
    pthread_mutex_init(&mem_mutex1, (pthread_mutexattr_t*) NULL);
    pthread_mutex_init(&mem_mutex2, (pthread_mutexattr_t*) NULL);
    pthread_mutex_init(&mem_mutex3, (pthread_mutexattr_t*) NULL);
    pthread_mutex_init(&mem_mutex4, (pthread_mutexattr_t*) NULL);
}

pthread_mutex_t* GetMutex(id x) {
    switch (((long) x) % 4) {
        case 0:
            return &mem_mutex0;
            break;
        case 1:
            return &mem_mutex1;
            break;
        case 2:
            return &mem_mutex2;
            break;
        case 3:
            return &mem_mutex3;
            break;
        case 4:
            return &mem_mutex4;
            break;
        default:
            return (pthread_mutex_t*) NULL;
            break;
    }
}


