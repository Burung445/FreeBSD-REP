#!/bin/sh
# $FreeBSD: head/tools/regression/geom_mirror/test-2.t 153186 2005-12-07 01:27:23Z pjd $

. `dirname $0`/conf.sh

echo "1..4"

balance="round-robin"
us0=45
us1=`expr $us0 + 1`
us2=`expr $us0 + 2`
ddbs=2048
nblocks1=1024
nblocks2=`expr $nblocks1 / \( $ddbs / 512 \)`
src=`mktemp /tmp/$base.XXXXXX` || exit 1
dst=`mktemp /tmp/$base.XXXXXX` || exit 1

dd if=/dev/random of=${src} bs=$ddbs count=$nblocks2 >/dev/null 2>&1

mdconfig -a -t malloc -s `expr $nblocks1 + 1` -u $us0 || exit 1
mdconfig -a -t malloc -s `expr $nblocks1 + 1` -u $us1 || exit 1
mdconfig -a -t malloc -s `expr $nblocks1 + 1` -u $us2 || exit 1

gmirror label -b $balance $name /dev/md${us0} /dev/md${us1} /dev/md${us2} || exit 1
devwait

dd if=${src} of=/dev/mirror/${name} bs=$ddbs count=$nblocks2 >/dev/null 2>&1

dd if=/dev/mirror/${name} of=${dst} bs=$ddbs count=$nblocks2 >/dev/null 2>&1
if [ `md5 -q ${src}` != `md5 -q ${dst}` ]; then
	echo "not ok 1"
else
	echo "ok 1"
fi
dd if=/dev/md${us0} of=${dst} bs=$ddbs count=$nblocks2 >/dev/null 2>&1
if [ `md5 -q ${src}` != `md5 -q ${dst}` ]; then
	echo "not ok 2"
else
	echo "ok 2"
fi
dd if=/dev/md${us1} of=${dst} bs=$ddbs count=$nblocks2 >/dev/null 2>&1
if [ `md5 -q ${src}` != `md5 -q ${dst}` ]; then
	echo "not ok 3"
else
	echo "ok 3"
fi

dd if=/dev/md${us2} of=${dst} bs=$ddbs count=$nblocks2 >/dev/null 2>&1
if [ `md5 -q ${src}` != `md5 -q ${dst}` ]; then
	echo "not ok 4"
else
	echo "ok 4"
fi

gmirror remove $name md${us0} md${us1} md${us2}
mdconfig -d -u $us0
mdconfig -d -u $us1
mdconfig -d -u $us2
rm -f ${src} ${dst}
