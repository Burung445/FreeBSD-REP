/*-
 * Copyright (c) 2011 Semihalf.
 * All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: head/sys/arm/mv/armadaxp/armadaxp_mp.c 262409 2014-02-23 22:35:18Z ian $
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/bus.h>
#include <sys/lock.h>
#include <sys/mutex.h>
#include <sys/smp.h>

#include <vm/vm.h>
#include <vm/vm_kern.h>
#include <vm/vm_extern.h>

#include <machine/smp.h>
#include <machine/fdt.h>
#include <machine/armreg.h>

#include <arm/mv/mvwin.h>

#define MV_AXP_CPU_DIVCLK_BASE		(MV_BASE + 0x18700)
#define CPU_DIVCLK_CTRL0		0x00
#define CPU_DIVCLK_CTRL2_RATIO_FULL0	0x08
#define CPU_DIVCLK_CTRL2_RATIO_FULL1	0x0c
#define CPU_DIVCLK_MASK(x)		(~(0xff << (8 * (x))))

#define CPU_PMU(x)			(MV_BASE + 0x22100 + (0x100 * (x)))
#define CPU_PMU_BOOT			0x24

#define MP				(MV_BASE + 0x20800)
#define MP_SW_RESET(x)			((x) * 8)

#define CPU_RESUME_CONTROL		(0x20988)

void armadaxp_init_coher_fabric(void);
int platform_get_ncpus(void);

/* Coherency Fabric registers */
static uint32_t
read_cpu_clkdiv(uint32_t reg)
{

	return (bus_space_read_4(fdtbus_bs_tag, MV_AXP_CPU_DIVCLK_BASE, reg));
}

static void
write_cpu_clkdiv(uint32_t reg, uint32_t val)
{

	bus_space_write_4(fdtbus_bs_tag, MV_AXP_CPU_DIVCLK_BASE, reg, val);
}

void
platform_mp_setmaxid(void)
{

	mp_maxid = 3;
}

int
platform_mp_probe(void)
{

	mp_ncpus = platform_get_ncpus();

	return (mp_ncpus > 1);
}

void
platform_mp_init_secondary(void)
{
}

void mptramp(void);



void
platform_mp_start_ap(void)
{
	uint32_t reg, *src, *dst, cpu_num, div_val, cputype;
	vm_offset_t smp_boot;
	/*
	 * Initialization procedure depends on core revision,
	 * in this step CHIP ID is checked to choose proper procedure
	 */
	cputype = cpufunc_id();
	cputype &= CPU_ID_CPU_MASK;

	smp_boot = kva_alloc(PAGE_SIZE);
	pmap_kenter_nocache(smp_boot, 0xffff0000);
	dst = (uint32_t *) smp_boot;

	for (src = (uint32_t *)mptramp; src < (uint32_t *)mpentry;
	    src++, dst++) {
		*dst = *src;
	}
	kva_free(smp_boot, PAGE_SIZE);

	if (cputype == CPU_ID_MV88SV584X_V7) {
		/* Core rev A0 */
		div_val = read_cpu_clkdiv(CPU_DIVCLK_CTRL2_RATIO_FULL1);
		div_val &= 0x3f;

		for (cpu_num = 1; cpu_num < mp_ncpus; cpu_num++ ) {
			reg = read_cpu_clkdiv(CPU_DIVCLK_CTRL2_RATIO_FULL1);
			reg &= CPU_DIVCLK_MASK(cpu_num);
			reg |= div_val << (cpu_num * 8);
			write_cpu_clkdiv(CPU_DIVCLK_CTRL2_RATIO_FULL1, reg);
		}
	} else {
		/* Core rev Z1 */
		div_val = 0x01;

		if (mp_ncpus > 1) {
			reg = read_cpu_clkdiv(CPU_DIVCLK_CTRL2_RATIO_FULL0);
			reg &= CPU_DIVCLK_MASK(3);
			reg |= div_val << 24;
			write_cpu_clkdiv(CPU_DIVCLK_CTRL2_RATIO_FULL0, reg);
		}

		for (cpu_num = 2; cpu_num < mp_ncpus; cpu_num++ ) {
			reg = read_cpu_clkdiv(CPU_DIVCLK_CTRL2_RATIO_FULL1);
			reg &= CPU_DIVCLK_MASK(cpu_num);
			reg |= div_val << (cpu_num * 8);
			write_cpu_clkdiv(CPU_DIVCLK_CTRL2_RATIO_FULL1, reg);
		}
	}

	reg = read_cpu_clkdiv(CPU_DIVCLK_CTRL0);
	reg |= ((0x1 << (mp_ncpus - 1)) - 1) << 21;
	write_cpu_clkdiv(CPU_DIVCLK_CTRL0, reg);
	reg = read_cpu_clkdiv(CPU_DIVCLK_CTRL0);
	reg |= 0x01000000;
	write_cpu_clkdiv(CPU_DIVCLK_CTRL0, reg);

	DELAY(100);
	reg &= ~(0xf << 21);
	write_cpu_clkdiv(CPU_DIVCLK_CTRL0, reg);
	DELAY(100);

	bus_space_write_4(fdtbus_bs_tag, MV_BASE, CPU_RESUME_CONTROL, 0);

	for (cpu_num = 1; cpu_num < mp_ncpus; cpu_num++ )
		bus_space_write_4(fdtbus_bs_tag, CPU_PMU(cpu_num), CPU_PMU_BOOT,
		    pmap_kextract((vm_offset_t)mpentry));

	cpu_idcache_wbinv_all();

	for (cpu_num = 1; cpu_num < mp_ncpus; cpu_num++ )
		bus_space_write_4(fdtbus_bs_tag, MP, MP_SW_RESET(cpu_num), 0);

	/* XXX: Temporary workaround for hangup after releasing AP's */
	wmb();
	DELAY(10);

	armadaxp_init_coher_fabric();
}

void
platform_ipi_send(cpuset_t cpus, u_int ipi)
{

	pic_ipi_send(cpus, ipi);
}
