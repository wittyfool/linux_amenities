#!/usr/local/bin/perl
for $f (</gp7000/share2/data/gms/gif/IR1F*.gif>){
  $x = ""; $y = "";
  $cmd = "fullCenter $f";
#  print "$cmd \n";
  $ret = `$cmd'`;
  for $_ (split(/\n/, $ret)){
    if(/center_x/){
      ($x) = /([\d\.]+)/;
    }
    if(/center_y/){
      ($y) = /([\d\.]+)/;
    }
  }
  $x = int $x;
  $y = int $y;
  $x -= 230;
  $y -= 230;

  $x = 0 - $x;
  $y = 0 - $y;

  print "readim(\"$f\");\n";
  print "shift($x, $y);\n";
}
