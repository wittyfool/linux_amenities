#!/bin/bash
file=$1
base="$(basename -s .pdf $file)"
tmpdir="/var/tmp"

mkdir -p $tmpdir/jpeg

pdftoppm -q -f 1 -l 900 -jpeg $file $tmpdir/jpeg/pages & 

sleep 1
while [[ -n $(jobs -r) ]]; do ls -ltr $tmpdir/jpeg | tail -1; sleep 1; done

wait

zip $base.cbz $tmpdir/jpeg/pages-*.jpg
rm $tmpdir/jpeg/pages-*.jpg
