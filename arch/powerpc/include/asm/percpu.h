#ifndef _ASM_POWERPC_PERCPU_H_
#define _ASM_POWERPC_PERCPU_H_
#ifdef __powerpc64__

/*
 * Same as asm-generic/percpu.h, except that we store the per cpu offset
 * in the paca. Based on the x86-64 implementation.
 */

#ifdef CONFIG_SMP

<<<<<<< HEAD
=======
#include <asm/paca.h>

>>>>>>> FETCH_HEAD
#define __my_cpu_offset local_paca->data_offset

#endif /* CONFIG_SMP */
#endif /* __powerpc64__ */

#include <asm-generic/percpu.h>

<<<<<<< HEAD
#include <asm/paca.h>

=======
>>>>>>> FETCH_HEAD
#endif /* _ASM_POWERPC_PERCPU_H_ */
