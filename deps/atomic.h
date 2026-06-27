#ifndef ATOMIC_H
#define ATOMIC_H

/* * Minimal atomic operations wrapper 
 * Replaces the complex QEMU atomic.h for your standalone build
 */

#define qatomic_read(ptr) \
    __atomic_load_n(ptr, __ATOMIC_RELAXED)

#define qatomic_set(ptr, val) \
    __atomic_store_n(ptr, val, __ATOMIC_RELAXED)

#define qatomic_or(ptr, val) \
    __atomic_fetch_or(ptr, val, __ATOMIC_RELAXED)

#define qatomic_and(ptr, val) \
    __atomic_fetch_and(ptr, val, __ATOMIC_RELAXED)

#define qatomic_xchg(ptr, val) \
    __atomic_exchange_n(ptr, val, __ATOMIC_SEQ_CST)

#define qatomic_cmpxchg(ptr, old, new) \
    __atomic_compare_exchange_n(ptr, &old, new, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

#endif
