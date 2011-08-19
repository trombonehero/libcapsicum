#!/bin/sh

if test -z "${DIR}" ; then DIR=$( make -V .OBJDIR ); fi
if test -z "${DIR}" ; then DIR=$( dirname $0 ); fi

BIN=$DIR/test/test-libcapsicum
LD_LIBRARY_PATH=$DIR/src; export LD_LIBRARY_PATH

make > /dev/null || exit 1
$BIN $*

