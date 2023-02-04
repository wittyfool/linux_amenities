#!/bin/bash
file=$1
base="$(basename -s .pdf $file)"
tmpdir="/var/tmp"

mkdir -p $tmpdir/jpeg

pdftoppm -f 1 -l 900 -jpeg $file $tmpdir/jpeg/pages
zip $base.cbz $tmpdir/jpeg/pages-*.jpg
rm $tmpdir/jpeg/pages-*.jpg
