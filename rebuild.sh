#!/bin/sh


cd `dirname $0`

autoreconf
CFLAGS="-g -O0" ./configure --enable-debug
