#!/usr/bin/perl
$dict = '/usr/share/gjiten/dics/edict';


open($fp, '<', $dict) || die "Can't read [$dict]\n";
while(<$fp>){
  s/[\r\n]//;
  if(/\[(.+)\]/){
    $words{ $count } = $1;
    $count++;
  }
}
close($fp);

$total = $count * $count * 1000;
print "count=[$count]\n";
print "total=[$total]\n";
print "---\n";
for $try (1..10){

  $rnd1 = int(rand $count);
  $rnd2 = int(rand $count);

  $num = sprintf("%03d", rand 1000);

  print $words{ $rnd1 }.$num.$words{ $rnd2 };
  print "\n";
}


