#!/usr/bin/perl
#
use Encode;

while(<>){
  $str .= $_;
}
$str = encode_utf8($str);
$str =~ s/([^ 0-9a-zA-Z])/"%".uc(unpack("H2",$1))/eg;
$str =~ s/ /+/g;
print($str);
