#!/bin/sh
# Copyright (c) 2013 The Carboncoin Core developers
# Distributed under the MIT/X11 software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
#
# Helper script for pull-tester.
#Param 1: path to carboncoin srcroot
#Param ...: arguments for build-test.sh

if [ $# -lt 1 ]; then
  echo "usage: $0 [carboncoin srcroot] build-test arguments..."
fi

killall -q carboncoin-cli
killall -q carboncoind

cd $1
shift

./autogen.sh
./configure
./qa/pull-tester/build-tests.sh "$@"
