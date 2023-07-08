#!/bin/bash

set -e

OPT="-O2"
DBG="-ggdb3 -DDEBUG"
CFLAGS="-Wall"
OPTCFLAGS="${CFLAGS} ${OPT}"
DBGCFLAGS="${CFLAGS} ${DBG}"

gcc ${OPTCFLAGS} wiki_vec.c rc4.c -o wiki_vec.exe
gcc ${OPTCFLAGS} wiki_vec.c rc4.c -o wiki_vec.dbg

strip *.exe
