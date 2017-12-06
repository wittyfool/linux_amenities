#!/usr/bin/perl
# 長いファイル名をディレクトリに分ける
#
$fname = shift;

@fld = split(/\s+/, $fname);

$path = "";
for $f (@fld){
  $path .= $f;
  print "[$path]\n";
  $path .= '/';
}

