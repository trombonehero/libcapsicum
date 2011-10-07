#!/bin/sh

if test -z "${DIR}" ; then DIR=$( make -V .OBJDIR ); fi
if test -z "${DIR}" ; then DIR=$( dirname $0 ); fi

BIN=$DIR/test-libcapsicum
LD_LIBRARY_PATH=$DIR/../src; export LD_LIBRARY_PATH
BINARY=$BIN; export BINARY

ktrace -di $BIN $*

