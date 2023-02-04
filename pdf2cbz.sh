#!/bin/bash
file=$1
base="$(basename -s .pdf $file)"

pdfimages -f 1 -l 900 -j $file jpeg/pages
zip $base.cbz jpeg/pages-*.jpg
rm jpeg/pages-*.jpg
