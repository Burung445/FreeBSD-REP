/*-
 * Copyright (c) 2006 M. Warner Losh.  All rights reserved.
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
 *
 * This software is derived from software provide by Kwikbyte who specifically
 * disclaimed copyright on the code.
 *
 * $FreeBSD: head/sys/boot/arm/at91/libat91/emac_init.c 238463 2012-07-15 05:35:14Z imp $
 */

/******************************************************************************
 *
 * Filename: emac.c
 *
 * Instantiation of routines for MAC/ethernet functions supporting tftp.
 *
 * Revision information:
 *
 * 28AUG2004	kb_admin	initial creation
 * 08JAN2005	kb_admin	added tftp download
 *					also adapted from external sources
 *
 * BEGIN_KBDD_BLOCK
 * No warranty, expressed or implied, is included with this software.  It is
 * provided "AS IS" and no warranty of any kind including statutory or aspects
 * relating to merchantability or fitness for any purpose is provided.  All
 * intellectual property rights of others is maintained with the respective
 * owners.  This software is not copyrighted and is intended for reference
 * only.
 * END_BLOCK
 ******************************************************************************/

#include "at91rm9200.h"
#include "at91rm9200_lowlevel.h"
#include "emac.h"
#include "lib.h"

/* ****************************** GLOBALS *************************************/

unsigned localMACSet;
unsigned char localMACAddr[6];
unsigned localMAClow, localMAChigh;

/* ********************** PRIVATE FUNCTIONS/DATA ******************************/

/*
 * .KB_C_FN_DEFINITION_START
 * void EMAC_SetMACAddress(unsigned low_address, unsigned high_address)
 *  This global function sets the MAC address.  low_address is the first
 * four bytes while high_address is the last 2 bytes of the 48-bit value.
 * .KB_C_FN_DEFINITION_END
 */
void
EMAC_SetMACAddress(unsigned char mac[6])
{
	AT91PS_PMC	pPMC = AT91C_BASE_PMC;
	AT91PS_EMAC	pEmac = AT91C_BASE_EMAC;

	/* enable the peripheral clock before using EMAC */
	pPMC->PMC_PCER = ((unsigned) 1 << AT91C_ID_EMAC);

	memcpy(localMACAddr, mac, 6);
	localMAClow = (mac[3] << 24) | (mac[2] << 16) | (mac[1] << 8) | mac[0];
	localMAChigh = (mac[5] << 8) | mac[4];
	localMACSet = 1;

	AT91C_BASE_PMC->PMC_PCER = 1u << AT91C_ID_EMAC;
	AT91C_BASE_PIOA->PIO_ASR = 
	  AT91C_PIO_PA14 | AT91C_PIO_PA12 | AT91C_PIO_PA13 |
	  AT91C_PIO_PA8 | AT91C_PIO_PA16 | AT91C_PIO_PA9 |
	  AT91C_PIO_PA10 | AT91C_PIO_PA11 | AT91C_PIO_PA15 |
	  AT91C_PIO_PA7;
	AT91C_BASE_PIOA->PIO_PDR = 
	  AT91C_PIO_PA14 | AT91C_PIO_PA12 | AT91C_PIO_PA13 |
	  AT91C_PIO_PA8 | AT91C_PIO_PA16 | AT91C_PIO_PA9 |
	  AT91C_PIO_PA10 | AT91C_PIO_PA11 | AT91C_PIO_PA15 |
	  AT91C_PIO_PA7;
#if defined(BOOT_KB920X) | defined(BOOT_BWCT)	/* Really !RMII */
	AT91C_BASE_PIOB->PIO_BSR =
	  AT91C_PIO_PB12 | AT91C_PIO_PB13 | AT91C_PIO_PB14 |
	  AT91C_PIO_PB15 | AT91C_PIO_PB16 | AT91C_PIO_PB17 |
	  AT91C_PIO_PB18 | AT91C_PIO_PB19;
	AT91C_BASE_PIOB->PIO_PDR =
	  AT91C_PIO_PB12 | AT91C_PIO_PB13 | AT91C_PIO_PB14 |
	  AT91C_PIO_PB15 | AT91C_PIO_PB16 | AT91C_PIO_PB17 |
	  AT91C_PIO_PB18 | AT91C_PIO_PB19;
#endif
	pEmac->EMAC_CTL  = 0;

	pEmac->EMAC_CFG  = (pEmac->EMAC_CFG & ~(AT91C_EMAC_CLK)) |
#ifdef BOOT_TSC
	    AT91C_EMAC_RMII |
#endif
	    AT91C_EMAC_CLK_HCLK_32 | AT91C_EMAC_CAF;
	// the sequence write EMAC_SA1L and write EMAC_SA1H must be respected
	pEmac->EMAC_SA1L = localMAClow;
	pEmac->EMAC_SA1H = localMAChigh;
}
