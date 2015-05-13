#!/bin/sh
#a2ps $1 -o $1.ps
e2ps -afw 0.5 -p $1 > $1.ps
ps2pdf $1.ps $1.pdf
