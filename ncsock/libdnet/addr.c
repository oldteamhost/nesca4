/*
 * addr.c
 *
 * Network address operations.
 *
 * Copyright (c) 2000 Dug Song <dugsong@monkey.org>
 *
 * $Id$
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include "include/addr.h"
#include "include/ip.h"

#ifndef MAXHOSTNAMELEN
# define MAXHOSTNAMELEN 256
#endif

union sockunion {
	struct sockaddr		sa;
	struct sockaddr_in	sin;
	struct sockaddr_in6	sin6;
};

int
addr_cmp(const struct addr *a, const struct addr *b)
{
	int i, j, k;

	/* XXX */
	if ((i = a->addr_type - b->addr_type) != 0)
		return (i);
	
	/* XXX - 10.0.0.1 is "smaller" than 10.0.0.0/8? */
	if ((i = a->addr_bits - b->addr_bits) != 0)
		return (i);
	
	j = b->addr_bits / 8;

	for (i = 0; i < j; i++) {
		if ((k = a->addr_data8[i] - b->addr_data8[i]) != 0)
			return (k);
	}
	if ((k = b->addr_bits % 8) == 0)
		return (0);

	k = ~0 << (8 - k);
	i = b->addr_data8[j] & k;
	j = a->addr_data8[j] & k;
	
	return (j - i);
}

int
addr_net(const struct addr *a, struct addr *b)
{
	uint32_t mask;
	int i, j;

	if (a->addr_type == ADDR_TYPE_IP) {
		addr_btom(a->addr_bits, &mask, _IP_ADDR_LEN);
		b->addr_type = ADDR_TYPE_IP;
		b->addr_bits = IP_ADDR_BITS;
		b->addr_ip = a->addr_ip & mask;
	} else if (a->addr_type == ADDR_TYPE_ETH) {
		memcpy(b, a, sizeof(*b));
		if (a->addr_data8[0] & 0x1)
			memset(b->addr_data8 + 3, 0, 3);
		b->addr_bits = ETH_ADDR_BITS;
	} else if (a->addr_type == ADDR_TYPE_IP6) {
		b->addr_type = ADDR_TYPE_IP6;
		b->addr_bits = IP6_ADDR_BITS;
		memset(&b->addr_ip6, 0, IP6_ADDR_LEN);
		
		switch ((i = a->addr_bits / 32)) {
		case 4: b->addr_data32[3] = a->addr_data32[3];
		case 3: b->addr_data32[2] = a->addr_data32[2];
		case 2: b->addr_data32[1] = a->addr_data32[1];
		case 1: b->addr_data32[0] = a->addr_data32[0];
		}
		if ((j = a->addr_bits % 32) > 0) {
			addr_btom(j, &mask, sizeof(mask));
			b->addr_data32[i] = a->addr_data32[i] & mask;
		}
	} else
		return (-1);
	
	return (0);
}

int
addr_bcast(const struct addr *a, struct addr *b)
{
	struct addr mask;
	
	if (a->addr_type == ADDR_TYPE_IP) {
		addr_btom(a->addr_bits, &mask.addr_ip, _IP_ADDR_LEN);
		b->addr_type = ADDR_TYPE_IP;
		b->addr_bits = IP_ADDR_BITS;
		b->addr_ip = (a->addr_ip & mask.addr_ip) |
		    (~0L & ~mask.addr_ip);
	} else if (a->addr_type == ADDR_TYPE_ETH) {
		b->addr_type = ADDR_TYPE_ETH;
		b->addr_bits = ETH_ADDR_BITS;
		memcpy(&b->addr_eth, ETH_ADDR_BROADCAST, ETH_ADDR_LEN);
	} else {
		/* XXX - no broadcast addresses in IPv6 */
		errno = EINVAL;
		return (-1);
	}
	return (0);
}

char *
addr_ntop(const struct addr *src, char *dst, size_t size)
{
	if (src->addr_type == ADDR_TYPE_IP && size >= 20) {
		if (ip_ntop(&src->addr_ip, dst, size) != NULL) {
			if (src->addr_bits != IP_ADDR_BITS)
				sprintf(dst + strlen(dst), "/%d",
				    src->addr_bits);
			return (dst);
		}
	} else if (src->addr_type == ADDR_TYPE_IP6 && size >= 42) {
		if (ip6_ntop(&src->addr_ip6, dst, size) != NULL) {
			if (src->addr_bits != IP6_ADDR_BITS)
				sprintf(dst + strlen(dst), "/%d",
				    src->addr_bits);
			return (dst);
		}
	} else if (src->addr_type == ADDR_TYPE_ETH && size >= 18) {
		if (src->addr_bits == ETH_ADDR_BITS)
			return (eth_ntop(&src->addr_eth, dst, size));
	}
	errno = EINVAL;
	return (NULL);
}

int
addr_pton(const char *src, struct addr *dst)
{
	char *ep, tmp[300];
	long bits = -1;
	int i;
	
	for (i = 0; i < (int)sizeof(tmp) - 1; i++) {
		if (src[i] == '/') {
			tmp[i] = '\0';
			if (strchr(&src[i + 1], '.')) {
				uint32_t m;
				uint16_t b;
				/* XXX - mask is specified like /255.0.0.0 */
				if (ip_pton(&src[i + 1], &m) != 0) {
					errno = EINVAL;
					return (-1);
				}
				addr_mtob(&m, sizeof(m), &b);
				bits = b;
			} else {
				bits = strtol(&src[i + 1], &ep, 10);
				if (ep == src || *ep != '\0' || bits < 0) {
					errno = EINVAL;
					return (-1);
				}
			}
			break;
		} else if ((tmp[i] = src[i]) == '\0')
			break;
	}
	if (ip_pton(tmp, &dst->addr_ip) == 0) {
		dst->addr_type = ADDR_TYPE_IP;
		dst->addr_bits = IP_ADDR_BITS;
	} else if (eth_pton(tmp, &dst->addr_eth) == 0) {
		dst->addr_type = ADDR_TYPE_ETH;
		dst->addr_bits = ETH_ADDR_BITS;
	} else if (ip6_pton(tmp, &dst->addr_ip6) == 0) {
		dst->addr_type = ADDR_TYPE_IP6;
		dst->addr_bits = IP6_ADDR_BITS;
	} else {
		errno = EINVAL;
		return (-1);
	}
	if (bits >= 0) {
		if (bits > dst->addr_bits) {
			errno = EINVAL;
			return (-1);
		}
		dst->addr_bits = (uint16_t)bits;
	}
	return (0);
}

char *
addr_ntoa(const struct addr *a)
{
	static char *p, buf[BUFSIZ];
	char *q = NULL;
	
	if (p == NULL || p > buf + sizeof(buf) - 64 /* XXX */)
		p = buf;
	
	if (addr_ntop(a, p, (buf + sizeof(buf)) - p) != NULL) {
		q = p;
		p += strlen(p) + 1;
	}
	return (q);
}

int
addr_ntos(const struct addr *a, struct sockaddr *sa)
{
	union sockunion *so = (union sockunion *)sa;
	
	switch (a->addr_type) {
	case ADDR_TYPE_ETH:
#ifdef HAVE_NET_IF_DL_H
		memset(&so->sdl, 0, sizeof(so->sdl));
# ifdef HAVE_SOCKADDR_SA_LEN
		so->sdl.sdl_len = sizeof(so->sdl);
# endif
# ifdef AF_LINK 
		so->sdl.sdl_family = AF_LINK;
# else
		so->sdl.sdl_family = AF_UNSPEC;
#endif
		so->sdl.sdl_alen = ETH_ADDR_LEN;
		memcpy(LLADDR(&so->sdl), &a->addr_eth, ETH_ADDR_LEN);
#else
		memset(sa, 0, sizeof(*sa));
# ifdef AF_LINK
		sa->sa_family = AF_LINK;
# else
		sa->sa_family = AF_UNSPEC;
# endif
		memcpy(sa->sa_data, &a->addr_eth, ETH_ADDR_LEN);
#endif
		break;
#ifdef HAVE_SOCKADDR_IN6
	case ADDR_TYPE_IP6:
		memset(&so->sin6, 0, sizeof(so->sin6));
#ifdef HAVE_SOCKADDR_SA_LEN
		so->sin6.sin6_len = sizeof(so->sin6);
#endif
		so->sin6.sin6_family = AF_INET6;
		memcpy(&so->sin6.sin6_addr, &a->addr_ip6, IP6_ADDR_LEN);
		break;
#endif
	case ADDR_TYPE_IP:
		memset(&so->sin, 0, sizeof(so->sin));
#ifdef HAVE_SOCKADDR_SA_LEN
		so->sin.sin_len = sizeof(so->sin);
#endif
		so->sin.sin_family = AF_INET;
		so->sin.sin_addr.s_addr = a->addr_ip;
		break;
	default:
		errno = EINVAL;
		return (-1);
	}
	return (0);
}

int
addr_ston(const struct sockaddr *sa, struct addr *a)
{
	union sockunion *so = (union sockunion *)sa;
	
	memset(a, 0, sizeof(*a));
	
	switch (sa->sa_family) {
#ifdef HAVE_NET_IF_DL_H
# ifdef AF_LINK
	case AF_LINK:
		if (so->sdl.sdl_alen != ETH_ADDR_LEN) {
			errno = EINVAL;
			return (-1);
		}
		a->addr_type = ADDR_TYPE_ETH;
		a->addr_bits = ETH_ADDR_BITS;
		memcpy(&a->addr_eth, LLADDR(&so->sdl), ETH_ADDR_LEN);
		break;
# endif
#endif
	case AF_UNSPEC:
	case 0x0001:	/* XXX- Linux arp(7) */
		a->addr_type = ADDR_TYPE_ETH;
		a->addr_bits = ETH_ADDR_BITS;
		memcpy(&a->addr_eth, sa->sa_data, ETH_ADDR_LEN);
		break;
		
#ifdef AF_RAW
	case AF_RAW:		/* XXX - IRIX raw(7f) */
		a->addr_type = ADDR_TYPE_ETH;
		a->addr_bits = ETH_ADDR_BITS;
		memcpy(&a->addr_eth, so->sr.sr_addr, ETH_ADDR_LEN);
		break;
#endif
#ifdef HAVE_SOCKADDR_IN6
	case AF_INET6:
		a->addr_type = ADDR_TYPE_IP6;
		a->addr_bits = IP6_ADDR_BITS;
		memcpy(&a->addr_ip6, &so->sin6.sin6_addr, IP6_ADDR_LEN);
		break;
#endif
	case AF_INET:
		a->addr_type = ADDR_TYPE_IP;
		a->addr_bits = IP_ADDR_BITS;
		a->addr_ip = so->sin.sin_addr.s_addr;
		break;
	default:
		errno = EINVAL;
		return (-1);
	}
	return (0);
}

int
addr_btos(uint16_t bits, struct sockaddr *sa)
{
	union sockunion *so = (union sockunion *)sa;

#ifdef HAVE_SOCKADDR_IN6
	if (bits > IP_ADDR_BITS && bits <= IP6_ADDR_BITS) {
		memset(&so->sin6, 0, sizeof(so->sin6));
#ifdef HAVE_SOCKADDR_SA_LEN
		so->sin6.sin6_len = IP6_ADDR_LEN + (bits / 8) + (bits % 8);
#endif
		so->sin6.sin6_family = AF_INET6;
		return (addr_btom(bits, &so->sin6.sin6_addr, IP6_ADDR_LEN));
	} else
#endif
	if (bits <= IP_ADDR_BITS) {
		memset(&so->sin, 0, sizeof(so->sin));
#ifdef HAVE_SOCKADDR_SA_LEN
		so->sin.sin_len = IP_ADDR_LEN + (bits / 8) + (bits % 8);
#endif
		so->sin.sin_family = AF_INET;
		return (addr_btom(bits, &so->sin.sin_addr, _IP_ADDR_LEN));
	}
	errno = EINVAL;
	return (-1);
}

int
addr_stob(const struct sockaddr *sa, uint16_t *bits)
{
	union sockunion *so = (union sockunion *)sa;
	int i, j, len;
	uint16_t n;
	u_char *p;

#ifdef HAVE_SOCKADDR_IN6
	if (sa->sa_family == AF_INET6) {
		len = IP6_ADDR_LEN;
		p = (u_char *)&so->sin6.sin6_addr;
	} else
#endif
	{
	p = (u_char *)&so->sin.sin_addr.s_addr;
#ifdef HAVE_SOCKADDR_SA_LEN
	len = sa->sa_len - ((void *) p - (void *) sa);
	/* Handles the special case of sa->sa_len == 0. */
	if (len < 0)
		len = 0;
	else if (len > IP_ADDR_LEN)
		len = IP_ADDR_LEN;
	#else
		len = _IP_ADDR_LEN;

#endif
		len = _IP_ADDR_LEN;
		p = (u_char *)&so->sin.sin_addr.s_addr;
	}
	for (n = i = 0; i < len; i++, n += 8) {
		if (p[i] != 0xff)
			break;
	}
	if (i != len && p[i]) {
		for (j = 7; j > 0; j--, n++) {
			if ((p[i] & (1 << j)) == 0)
				break;
		}
	}
	*bits = n;
	
	return (0);
}
	
int
addr_btom(uint16_t bits, void *mask, size_t size)
{
	int net, host;
	u_char *p;

	if (size == _IP_ADDR_LEN) {
		if (bits > IP_ADDR_BITS) {
			errno = EINVAL;
			return (-1);
		}
		*(uint32_t *)mask = bits ?
		    htonl(~0 << (IP_ADDR_BITS - bits)) : 0;
	} else {
		if (size * 8 < bits) {
			errno = EINVAL;
			return (-1);
		}
		p = (u_char *)mask;
		
		if ((net = bits / 8) > 0)
			memset(p, 0xff, net);
		
		if ((host = bits % 8) > 0) {
			p[net] = 0xff << (8 - host);
			memset(&p[net + 1], 0, size - net - 1);
		} else
			memset(&p[net], 0, size - net);
	}
	return (0);
}

int
addr_mtob(const void *mask, size_t size, uint16_t *bits)
{
	uint16_t n;
	u_char *p;
	int i, j;

	p = (u_char *)mask;
	
	for (n = i = 0; i < (int)size; i++, n += 8) {
		if (p[i] != 0xff)
			break;
	}
	if (i != (int)size && p[i]) {
		for (j = 7; j > 0; j--, n++) {
			if ((p[i] & (1 << j)) == 0)
				break;
		}
	}
	*bits = n;

	return (0);
}


static const char *octet2dec[] = {
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12",
	"13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23",
	"24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34",
	"35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45",
	"46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56",
	"57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67",
	"68", "69", "70", "71", "72", "73", "74", "75", "76", "77", "78",
	"79", "80", "81", "82", "83", "84", "85", "86", "87", "88", "89",
	"90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "100",
	"101", "102", "103", "104", "105", "106", "107", "108", "109",
	"110", "111", "112", "113", "114", "115", "116", "117", "118",
	"119", "120", "121", "122", "123", "124", "125", "126", "127",
	"128", "129", "130", "131", "132", "133", "134", "135", "136",
	"137", "138", "139", "140", "141", "142", "143", "144", "145",
	"146", "147", "148", "149", "150", "151", "152", "153", "154",
	"155", "156", "157", "158", "159", "160", "161", "162", "163",
	"164", "165", "166", "167", "168", "169", "170", "171", "172",
	"173", "174", "175", "176", "177", "178", "179", "180", "181",
	"182", "183", "184", "185", "186", "187", "188", "189", "190",
	"191", "192", "193", "194", "195", "196", "197", "198", "199",
	"200", "201", "202", "203", "204", "205", "206", "207", "208",
	"209", "210", "211", "212", "213", "214", "215", "216", "217",
	"218", "219", "220", "221", "222", "223", "224", "225", "226",
	"227", "228", "229", "230", "231", "232", "233", "234", "235",
	"236", "237", "238", "239", "240", "241", "242", "243", "244",
	"245", "246", "247", "248", "249", "250", "251", "252", "253",
	"254", "255"
};

static const char *octet2hex[] = {
	"00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0a",
	"0b", "0c", "0d", "0e", "0f", "10", "11", "12", "13", "14", "15",
	"16", "17", "18", "19", "1a", "1b", "1c", "1d", "1e", "1f", "20",
	"21", "22", "23", "24", "25", "26", "27", "28", "29", "2a", "2b",
	"2c", "2d", "2e", "2f", "30", "31", "32", "33", "34", "35", "36",
	"37", "38", "39", "3a", "3b", "3c", "3d", "3e", "3f", "40", "41",
	"42", "43", "44", "45", "46", "47", "48", "49", "4a", "4b", "4c",
	"4d", "4e", "4f", "50", "51", "52", "53", "54", "55", "56", "57",
	"58", "59", "5a", "5b", "5c", "5d", "5e", "5f", "60", "61", "62",
	"63", "64", "65", "66", "67", "68", "69", "6a", "6b", "6c", "6d",
	"6e", "6f", "70", "71", "72", "73", "74", "75", "76", "77", "78",
	"79", "7a", "7b", "7c", "7d", "7e", "7f", "80", "81", "82", "83",
	"84", "85", "86", "87", "88", "89", "8a", "8b", "8c", "8d", "8e",
	"8f", "90", "91", "92", "93", "94", "95", "96", "97", "98", "99",
	"9a", "9b", "9c", "9d", "9e", "9f", "a0", "a1", "a2", "a3", "a4",
	"a5", "a6", "a7", "a8", "a9", "aa", "ab", "ac", "ad", "ae", "af",
	"b0", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9", "ba",
	"bb", "bc", "bd", "be", "bf", "c0", "c1", "c2", "c3", "c4", "c5",
	"c6", "c7", "c8", "c9", "ca", "cb", "cc", "cd", "ce", "cf", "d0",
	"d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9", "da", "db",
	"dc", "dd", "de", "df", "e0", "e1", "e2", "e3", "e4", "e5", "e6",
	"e7", "e8", "e9", "ea", "eb", "ec", "ed", "ee", "ef", "f0", "f1",
	"f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "fa", "fb", "fc",
	"fd", "fe", "ff"
};

char *
eth_ntop(const eth_addr_t *eth, char *dst, size_t len)
{
	const char *x;
	char *p = dst;
	int i;
	
	if (len < 18)
		return (NULL);
	
	for (i = 0; i < ETH_ADDR_LEN; i++) {
		for (x = octet2hex[eth->data[i]]; (*p = *x) != '\0'; x++, p++)
			;
		*p++ = ':';
	}
	p[-1] = '\0';
	
	return (dst);
}

char *
eth_ntoa(const eth_addr_t *eth)
{
	struct addr a;
	
	addr_pack(&a, ADDR_TYPE_ETH, ETH_ADDR_BITS, eth->data, ETH_ADDR_LEN);
	return (addr_ntoa(&a));
}

int
eth_pton(const char *p, eth_addr_t *eth)
{
	char *ep;
	long l;
	int i;
	
	for (i = 0; i < ETH_ADDR_LEN; i++) {
		l = strtol(p, &ep, 16);
		if (ep == p || l < 0 || l > 0xff ||
		    (i < ETH_ADDR_LEN - 1 && *ep != ':'))
			break;
		eth->data[i] = (u_char)l;
		p = ep + 1;
	}
	return ((i == ETH_ADDR_LEN && *ep == '\0') ? 0 : -1);
}

char *
ip_ntop(const ip_addr_t *ip, char *dst, size_t len)
{
	const char *d;
	char *p = dst;
	u_char *data = (u_char *)ip;
	int i;
	
	if (len < 16)
		return (NULL);
	
	for (i = 0; i < _IP_ADDR_LEN; i++) {
		for (d = octet2dec[data[i]]; (*p = *d) != '\0'; d++, p++)
			;
		*p++ = '.';
	}
	p[-1] = '\0';
	
	return (dst);
}

char *
ip_ntoa(const ip_addr_t *ip)
{
	struct addr a;
	
	addr_pack(&a, ADDR_TYPE_IP, IP_ADDR_BITS, ip, _IP_ADDR_LEN);
	return (addr_ntoa(&a));
}

int
ip_pton(const char *p, ip_addr_t *ip)
{
	u_char *data = (u_char *)ip;
	char *ep;
	long l;
	int i;

	for (i = 0; i < _IP_ADDR_LEN; i++) {
		l = strtol(p, &ep, 10);
		if (ep == p || l < 0 || l > 0xff ||
		    (i < _IP_ADDR_LEN - 1 && *ep != '.'))
			break;
		data[i] = (u_char)l;
		p = ep + 1;
	}
	return ((i == _IP_ADDR_LEN && *ep == '\0') ? 0 : -1);
}

char *
ip6_ntop(const ip6_addr_t *ip6, char *dst, size_t len)
{
	struct { int base, len; } best, cur;
	char *p = dst;
	int i;
	uint16_t *ip6_data;

	cur.len = best.len = 0;
	
	if (len < 46)
		return (NULL);
	
	best.base = cur.base = -1;
	/*
	 * Algorithm borrowed from Vixie's inet_pton6()
	 */
	for (i = 0; i < IP6_ADDR_LEN; i += 2) {
		ip6_data = (uint16_t *)&ip6->data[i];
		if (*ip6_data == 0) {
			if (cur.base == -1) {
				cur.base = i;
				cur.len = 0;
			} else
				cur.len += 2;
		} else {
			if (cur.base != -1) {
				if (best.base == -1 || cur.len > best.len)
					best = cur;
				cur.base = -1;
			}
		}
	}
	if (cur.base != -1 && (best.base == -1 || cur.len > best.len))
		best = cur;
	if (best.base != -1 && best.len < 2)
		best.base = -1;
	if (best.base == 0)
		*p++ = ':';

	for (i = 0; i < IP6_ADDR_LEN; i += 2) {
		if (i == best.base) {
			*p++ = ':';
			i += best.len;
		} else if (i == 12 && best.base == 0 &&
		    (best.len == 10 || (best.len == 8 &&
			*(ip6_data = (uint16_t *)&ip6->data[10]) == 0xffff))) {
			if (ip_ntop((ip_addr_t *)&ip6->data[12], p,
			    len - (p - dst)) == NULL)
				return (NULL);
			return (dst);
		} else p += sprintf(p, "%x:",
			ntohs(*(ip6_data = (uint16_t *)&ip6->data[i])));
	}
	if (best.base + 2 + best.len == IP6_ADDR_LEN) {
		*p = '\0';
	} else
		p[-1] = '\0';

	return (dst);
}

char *
ip6_ntoa(const ip6_addr_t *ip6)
{
	struct addr a;
	
	addr_pack(&a, ADDR_TYPE_IP6, IP6_ADDR_BITS, ip6->data, IP6_ADDR_LEN);
	return (addr_ntoa(&a));
}

int
ip6_pton(const char *p, ip6_addr_t *ip6)
{
	uint16_t data[8], *u = (uint16_t *)ip6->data;
	int i, j, n, z = -1;
	char *ep;
	long l;
	
	if (*p == ':')
		p++;
	
	for (n = 0; n < 8; n++) {
		l = strtol(p, &ep, 16);
		
		if (ep == p) {
			if (ep[0] == ':' && z == -1) {
				z = n;
				p++;
			} else if (ep[0] == '\0') {
				break;
			} else {
				return (-1);
			}
		} else if (ep[0] == '.' && n <= 6) {
			if (ip_pton(p, (ip_addr_t *)(data + n)) < 0)
				return (-1);
			n += 2;
			ep = ""; /* XXX */
			break;
		} else if (l >= 0 && l <= 0xffff) {
			data[n] = htons((uint16_t)l);

			if (ep[0] == '\0') {
				n++;
				break;
			} else if (ep[0] != ':' || ep[1] == '\0')
				return (-1);

			p = ep + 1;
		} else
			return (-1);
	}
	if (n == 0 || *ep != '\0' || (z == -1 && n != 8))
		return (-1);
	
	for (i = 0; i < z; i++) {
		u[i] = data[i];
	}
	while (i < 8 - (n - z - 1)) {
		u[i++] = 0;
	}
	for (j = z + 1; i < 8; i++, j++) {
		u[i] = data[j];
	}
	return (0);
}
