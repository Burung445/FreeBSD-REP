/*-
 * Copyright (c) 2013 Thomas Skibo.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD:  265099 2014-04-29 17:48:57Z ian $");
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/bus.h>
#include <sys/lock.h>
#include <sys/mutex.h>
#include <sys/smp.h>

#include <machine/smp.h>
#include <machine/fdt.h>
#include <machine/intr.h>

#include <arm/xilinx/zy7_reg.h>

#define	ZYNQ7_CPU1_ENTRY	0xfffffff0

void
platform_mp_init_secondary(void)
{

	gic_init_secondary();
}

void
platform_mp_setmaxid(void)
{

	mp_maxid = 1;
}

int
platform_mp_probe(void)
{

	mp_ncpus = 2;
	return (1);
}

void    
platform_mp_start_ap(void)
{
	bus_space_handle_t ocm_handle;

	/* Map in magic location to give entry address to CPU1. */
	if (bus_space_map(fdtbus_bs_tag, ZYNQ7_CPU1_ENTRY, 4,
	    0, &ocm_handle) != 0)
		panic("platform_mp_start_ap: Couldn't map OCM\n");

	/* Write start address for CPU1. */
	bus_space_write_4(fdtbus_bs_tag, ocm_handle, 0,
	    pmap_kextract((vm_offset_t)mpentry));

	/*
	 * The SCU is enabled by the BOOTROM but I think the second CPU doesn't
	 * turn on filtering until after the wake-up below. I think that's why
	 * things don't work if I don't put these cache ops here.  Also, the
	 * magic location, 0xfffffff0, isn't in the SCU's filtering range so it
	 * needs a write-back too.
	 */
	cpu_idcache_wbinv_all();
	cpu_l2cache_wbinv_all();

	/* Wake up CPU1. */
	armv7_sev();

	bus_space_unmap(fdtbus_bs_tag, ocm_handle, 4);
}

void
platform_ipi_send(cpuset_t cpus, u_int ipi)
{

	pic_ipi_send(cpus, ipi);
}
