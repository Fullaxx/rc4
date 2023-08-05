#!/bin/bash

set -e

OPT="-O2"
DBG="-ggdb3 -DDEBUG"
CFLAGS="-Wall"
OPTCFLAGS="${CFLAGS} ${OPT}"
DBGCFLAGS="${CFLAGS} ${DBG}"

gcc ${OPTCFLAGS} wiki_vec_rc4.c rc4.c -o wiki_vec_rc4.exe
gcc ${DBGCFLAGS} wiki_vec_rc4.c rc4.c -o wiki_vec_rc4.dbg

strip *.exe
