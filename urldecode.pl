#!/usr/bin/perl
#
use Encode;

while(<>){
  $str .= $_;
}
$str =~ s/\+/ /g;
$str =~ s/%([0-9a-fA-F]{2})/pack("H2",$1)/eg;
print($str);
