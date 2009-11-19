#!/bin/sh


cd `dirname $0`

autoreconf
autoheader
CFLAGS="-g -O0" ./configure --enable-debug
