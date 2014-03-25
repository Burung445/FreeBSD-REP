/*-
 * Copyright (c) 2001-2003
 *	Fraunhofer Institute for Open Communication Systems (FhG Fokus).
 * 	All rights reserved.
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
 * Author: Hartmut Brandt <harti@freebsd.org>
 *
 * Fore PCA200E driver for NATM
 *
 * This has been generated with:
 *
 *	awk </dev/null 'BEGIN { period=255; linerate=353053; \
 *	    printf "{ 0x00000000, %u },\n", linerate; \
 *	    for(i=period-1; i>0; i--) printf "{ 0x%08x, %u },\n", \
 *		(i * 65536) + (period - i), i * linerate/period; }'
 *
 * $FreeBSD: head/sys/dev/fatm/if_fatm_rate.h 139749 2005-01-06 01:43:34Z imp $
 */
{ 0x00000000, 353053 },
{ 0x00fe0001, 351668 },
{ 0x00fd0002, 350283 },
{ 0x00fc0003, 348899 },
{ 0x00fb0004, 347514 },
{ 0x00fa0005, 346130 },
{ 0x00f90006, 344745 },
{ 0x00f80007, 343361 },
{ 0x00f70008, 341976 },
{ 0x00f60009, 340592 },
{ 0x00f5000a, 339207 },
{ 0x00f4000b, 337823 },
{ 0x00f3000c, 336438 },
{ 0x00f2000d, 335054 },
{ 0x00f1000e, 333669 },
{ 0x00f0000f, 332285 },
{ 0x00ef0010, 330900 },
{ 0x00ee0011, 329516 },
{ 0x00ed0012, 328131 },
{ 0x00ec0013, 326747 },
{ 0x00eb0014, 325362 },
{ 0x00ea0015, 323978 },
{ 0x00e90016, 322593 },
{ 0x00e80017, 321209 },
{ 0x00e70018, 319824 },
{ 0x00e60019, 318439 },
{ 0x00e5001a, 317055 },
{ 0x00e4001b, 315670 },
{ 0x00e3001c, 314286 },
{ 0x00e2001d, 312901 },
{ 0x00e1001e, 311517 },
{ 0x00e0001f, 310132 },
{ 0x00df0020, 308748 },
{ 0x00de0021, 307363 },
{ 0x00dd0022, 305979 },
{ 0x00dc0023, 304594 },
{ 0x00db0024, 303210 },
{ 0x00da0025, 301825 },
{ 0x00d90026, 300441 },
{ 0x00d80027, 299056 },
{ 0x00d70028, 297672 },
{ 0x00d60029, 296287 },
{ 0x00d5002a, 294903 },
{ 0x00d4002b, 293518 },
{ 0x00d3002c, 292134 },
{ 0x00d2002d, 290749 },
{ 0x00d1002e, 289365 },
{ 0x00d0002f, 287980 },
{ 0x00cf0030, 286595 },
{ 0x00ce0031, 285211 },
{ 0x00cd0032, 283826 },
{ 0x00cc0033, 282442 },
{ 0x00cb0034, 281057 },
{ 0x00ca0035, 279673 },
{ 0x00c90036, 278288 },
{ 0x00c80037, 276904 },
{ 0x00c70038, 275519 },
{ 0x00c60039, 274135 },
{ 0x00c5003a, 272750 },
{ 0x00c4003b, 271366 },
{ 0x00c3003c, 269981 },
{ 0x00c2003d, 268597 },
{ 0x00c1003e, 267212 },
{ 0x00c0003f, 265828 },
{ 0x00bf0040, 264443 },
{ 0x00be0041, 263059 },
{ 0x00bd0042, 261674 },
{ 0x00bc0043, 260290 },
{ 0x00bb0044, 258905 },
{ 0x00ba0045, 257521 },
{ 0x00b90046, 256136 },
{ 0x00b80047, 254751 },
{ 0x00b70048, 253367 },
{ 0x00b60049, 251982 },
{ 0x00b5004a, 250598 },
{ 0x00b4004b, 249213 },
{ 0x00b3004c, 247829 },
{ 0x00b2004d, 246444 },
{ 0x00b1004e, 245060 },
{ 0x00b0004f, 243675 },
{ 0x00af0050, 242291 },
{ 0x00ae0051, 240906 },
{ 0x00ad0052, 239522 },
{ 0x00ac0053, 238137 },
{ 0x00ab0054, 236753 },
{ 0x00aa0055, 235368 },
{ 0x00a90056, 233984 },
{ 0x00a80057, 232599 },
{ 0x00a70058, 231215 },
{ 0x00a60059, 229830 },
{ 0x00a5005a, 228446 },
{ 0x00a4005b, 227061 },
{ 0x00a3005c, 225677 },
{ 0x00a2005d, 224292 },
{ 0x00a1005e, 222907 },
{ 0x00a0005f, 221523 },
{ 0x009f0060, 220138 },
{ 0x009e0061, 218754 },
{ 0x009d0062, 217369 },
{ 0x009c0063, 215985 },
{ 0x009b0064, 214600 },
{ 0x009a0065, 213216 },
{ 0x00990066, 211831 },
{ 0x00980067, 210447 },
{ 0x00970068, 209062 },
{ 0x00960069, 207678 },
{ 0x0095006a, 206293 },
{ 0x0094006b, 204909 },
{ 0x0093006c, 203524 },
{ 0x0092006d, 202140 },
{ 0x0091006e, 200755 },
{ 0x0090006f, 199371 },
{ 0x008f0070, 197986 },
{ 0x008e0071, 196602 },
{ 0x008d0072, 195217 },
{ 0x008c0073, 193833 },
{ 0x008b0074, 192448 },
{ 0x008a0075, 191063 },
{ 0x00890076, 189679 },
{ 0x00880077, 188294 },
{ 0x00870078, 186910 },
{ 0x00860079, 185525 },
{ 0x0085007a, 184141 },
{ 0x0084007b, 182756 },
{ 0x0083007c, 181372 },
{ 0x0082007d, 179987 },
{ 0x0081007e, 178603 },
{ 0x0080007f, 177218 },
{ 0x007f0080, 175834 },
{ 0x007e0081, 174449 },
{ 0x007d0082, 173065 },
{ 0x007c0083, 171680 },
{ 0x007b0084, 170296 },
{ 0x007a0085, 168911 },
{ 0x00790086, 167527 },
{ 0x00780087, 166142 },
{ 0x00770088, 164758 },
{ 0x00760089, 163373 },
{ 0x0075008a, 161989 },
{ 0x0074008b, 160604 },
{ 0x0073008c, 159219 },
{ 0x0072008d, 157835 },
{ 0x0071008e, 156450 },
{ 0x0070008f, 155066 },
{ 0x006f0090, 153681 },
{ 0x006e0091, 152297 },
{ 0x006d0092, 150912 },
{ 0x006c0093, 149528 },
{ 0x006b0094, 148143 },
{ 0x006a0095, 146759 },
{ 0x00690096, 145374 },
{ 0x00680097, 143990 },
{ 0x00670098, 142605 },
{ 0x00660099, 141221 },
{ 0x0065009a, 139836 },
{ 0x0064009b, 138452 },
{ 0x0063009c, 137067 },
{ 0x0062009d, 135683 },
{ 0x0061009e, 134298 },
{ 0x0060009f, 132914 },
{ 0x005f00a0, 131529 },
{ 0x005e00a1, 130145 },
{ 0x005d00a2, 128760 },
{ 0x005c00a3, 127375 },
{ 0x005b00a4, 125991 },
{ 0x005a00a5, 124606 },
{ 0x005900a6, 123222 },
{ 0x005800a7, 121837 },
{ 0x005700a8, 120453 },
{ 0x005600a9, 119068 },
{ 0x005500aa, 117684 },
{ 0x005400ab, 116299 },
{ 0x005300ac, 114915 },
{ 0x005200ad, 113530 },
{ 0x005100ae, 112146 },
{ 0x005000af, 110761 },
{ 0x004f00b0, 109377 },
{ 0x004e00b1, 107992 },
{ 0x004d00b2, 106608 },
{ 0x004c00b3, 105223 },
{ 0x004b00b4, 103839 },
{ 0x004a00b5, 102454 },
{ 0x004900b6, 101070 },
{ 0x004800b7, 99685 },
{ 0x004700b8, 98301 },
{ 0x004600b9, 96916 },
{ 0x004500ba, 95531 },
{ 0x004400bb, 94147 },
{ 0x004300bc, 92762 },
{ 0x004200bd, 91378 },
{ 0x004100be, 89993 },
{ 0x004000bf, 88609 },
{ 0x003f00c0, 87224 },
{ 0x003e00c1, 85840 },
{ 0x003d00c2, 84455 },
{ 0x003c00c3, 83071 },
{ 0x003b00c4, 81686 },
{ 0x003a00c5, 80302 },
{ 0x003900c6, 78917 },
{ 0x003800c7, 77533 },
{ 0x003700c8, 76148 },
{ 0x003600c9, 74764 },
{ 0x003500ca, 73379 },
{ 0x003400cb, 71995 },
{ 0x003300cc, 70610 },
{ 0x003200cd, 69226 },
{ 0x003100ce, 67841 },
{ 0x003000cf, 66457 },
{ 0x002f00d0, 65072 },
{ 0x002e00d1, 63687 },
{ 0x002d00d2, 62303 },
{ 0x002c00d3, 60918 },
{ 0x002b00d4, 59534 },
{ 0x002a00d5, 58149 },
{ 0x002900d6, 56765 },
{ 0x002800d7, 55380 },
{ 0x002700d8, 53996 },
{ 0x002600d9, 52611 },
{ 0x002500da, 51227 },
{ 0x002400db, 49842 },
{ 0x002300dc, 48458 },
{ 0x002200dd, 47073 },
{ 0x002100de, 45689 },
{ 0x002000df, 44304 },
{ 0x001f00e0, 42920 },
{ 0x001e00e1, 41535 },
{ 0x001d00e2, 40151 },
{ 0x001c00e3, 38766 },
{ 0x001b00e4, 37382 },
{ 0x001a00e5, 35997 },
{ 0x001900e6, 34613 },
{ 0x001800e7, 33228 },
{ 0x001700e8, 31843 },
{ 0x001600e9, 30459 },
{ 0x001500ea, 29074 },
{ 0x001400eb, 27690 },
{ 0x001300ec, 26305 },
{ 0x001200ed, 24921 },
{ 0x001100ee, 23536 },
{ 0x001000ef, 22152 },
{ 0x000f00f0, 20767 },
{ 0x000e00f1, 19383 },
{ 0x000d00f2, 17998 },
{ 0x000c00f3, 16614 },
{ 0x000b00f4, 15229 },
{ 0x000a00f5, 13845 },
{ 0x000900f6, 12460 },
{ 0x000800f7, 11076 },
{ 0x000700f8, 9691 },
{ 0x000600f9, 8307 },
{ 0x000500fa, 6922 },
{ 0x000400fb, 5538 },
{ 0x000300fc, 4153 },
{ 0x000200fd, 2769 },
{ 0x000100fe, 1384 },
