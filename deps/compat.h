#ifndef COMPAT_H
#define COMPAT_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Map QEMU internals to standard C equivalents */
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#define barrier() __asm__ __volatile__("" ::: "memory")
#define smp_mb() __sync_synchronize()
#define smp_rmb() __sync_synchronize()
#define smp_wmb() __sync_synchronize()

#endif
