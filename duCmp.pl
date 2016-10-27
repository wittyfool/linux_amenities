#!/usr/bin/perl
# file1, file2 : output of "du -sk *"
#
$f1 = shift || die;
$f2 = shift || die;

$h1 = toHash($f1);
$h2 = toHash($f2);

for $k (sort keys %$h2){
  $diff->{ $k } = $h2->{$k} - $h1->{$k};
}
for $k (sort keys %$h2){
  print $diff->{$k}."   ";
  print $k."     ".$h1->{$k}." --> ".$h2->{$k}."\n";
}

sub toHash {
  my $f = shift;
  my $ret = {};

  open(FP, '<', $f) || die;
  while(<FP>){
    s/[\r\n]+//;
    ($num, $dir) = /(\d+)\s+(\S+)/;
    $ret->{ $dir } = $num;
  }
  close(FP);
  return $ret;
}
