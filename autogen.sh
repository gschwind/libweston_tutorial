#!/bin/sh
libtoolize -f -c
aclocal
autoheader -f
autoconf -f
automake -a -f -c

