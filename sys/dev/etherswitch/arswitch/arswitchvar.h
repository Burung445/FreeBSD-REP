/*-
 * Copyright (c) 2011-2012 Stefan Bethke.
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
 * $FreeBSD: head/sys/dev/etherswitch/arswitch/arswitchvar.h 262681 2014-03-02 05:48:56Z adrian $
 */
#ifndef	__ARSWITCHVAR_H__
#define	__ARSWITCHVAR_H__

typedef enum {
	AR8X16_SWITCH_NONE,
	AR8X16_SWITCH_AR7240,
	AR8X16_SWITCH_AR8216,
	AR8X16_SWITCH_AR8226,
	AR8X16_SWITCH_AR8316,
	AR8X16_SWITCH_AR9340,
	AR8X16_SWITCH_AR8327,
	AR8X16_SWITCH_AR8337,
} ar8x16_switch_type;

/*
 * XXX TODO: start using this where required
 */
#define	AR8X16_IS_SWITCH(_sc, _type) \
	    (!!((_sc)->sc_switchtype == AR8X16_SWITCH_ ## _type))

#define ARSWITCH_NUM_PORTS	MAX(AR8327_NUM_PORTS, AR8X16_NUM_PORTS)
#define ARSWITCH_NUM_PHYS	MAX(AR8327_NUM_PHYS, AR8X16_NUM_PHYS)

struct arswitch_softc {
	struct mtx	sc_mtx;		/* serialize access to softc */
	device_t	sc_dev;
	int		phy4cpu;	/* PHY4 is connected to the CPU */
	int		numphys;	/* PHYs we manage */
	int		is_rgmii;	/* PHY mode is RGMII (XXX which PHY?) */
	int		is_gmii;	/* PHY mode is GMII (XXX which PHY?) */
	int		is_mii;		/* PHY mode is MII (XXX which PHY?) */
	int		page;
	int		is_internal_switch;
	int		chip_ver;
	int		chip_rev;
	int		mii_lo_first;
	ar8x16_switch_type	sc_switchtype;
	/* should be the max of both pre-AR8327 and AR8327 ports */
	char		*ifname[ARSWITCH_NUM_PHYS];
	device_t	miibus[ARSWITCH_NUM_PHYS];
	struct ifnet	*ifp[ARSWITCH_NUM_PHYS];
	struct callout	callout_tick;
	etherswitch_info_t info;

	/* VLANs support */
	int		vid[AR8X16_MAX_VLANS];
	uint32_t	vlan_mode;

	struct {
		/* Global setup */
		int (* arswitch_hw_setup) (struct arswitch_softc *);
		int (* arswitch_hw_global_setup) (struct arswitch_softc *);

		/* Port functions */
		void (* arswitch_port_init) (struct arswitch_softc *, int);

		/* ATU functions */
		int (* arswitch_atu_flush) (struct arswitch_softc *);

		/* VLAN functions */
		int (* arswitch_port_vlan_setup) (struct arswitch_softc *,
		    etherswitch_port_t *);
		int (* arswitch_port_vlan_get) (struct arswitch_softc *,
		    etherswitch_port_t *);
		void (* arswitch_vlan_init_hw) (struct arswitch_softc *);
		int (* arswitch_vlan_getvgroup) (struct arswitch_softc *,
		    etherswitch_vlangroup_t *);
		int (* arswitch_vlan_setvgroup) (struct arswitch_softc *,
		    etherswitch_vlangroup_t *);
		int (* arswitch_vlan_get_pvid) (struct arswitch_softc *, int,
		    int *);
		int (* arswitch_vlan_set_pvid) (struct arswitch_softc *, int,
		    int);
	} hal;

	struct {
		uint32_t port0_status;
		uint32_t port5_status;
		uint32_t port6_status;
	} ar8327;
};

#define	ARSWITCH_LOCK(_sc)			\
	    mtx_lock(&(_sc)->sc_mtx)
#define	ARSWITCH_UNLOCK(_sc)			\
	    mtx_unlock(&(_sc)->sc_mtx)
#define	ARSWITCH_LOCK_ASSERT(_sc, _what)	\
	    mtx_assert(&(_sc)->sc_mtx, (_what))
#define	ARSWITCH_TRYLOCK(_sc)			\
	    mtx_trylock(&(_sc)->sc_mtx)

#if defined(DEBUG)
#define DPRINTF(dev, args...) device_printf(dev, args)
#define DEVERR(dev, err, fmt, args...) do { \
		if (err != 0) device_printf(dev, fmt, err, args); \
	} while (0)
#define DEBUG_INCRVAR(var)	do { \
		var++; \
	} while (0)
#else
#define DPRINTF(dev, args...)
#define DEVERR(dev, err, fmt, args...)
#define DEBUG_INCRVAR(var)
#endif

#endif	/* __ARSWITCHVAR_H__ */

