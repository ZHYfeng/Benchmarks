#!/bin/sh
klee pfscan-1.0.o -V 3 ${PWD}/file/ 0 0 0 0 2>result.txt 1>&2
