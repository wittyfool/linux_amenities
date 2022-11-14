#!/usr/bin/perl -s
while(<>){
  @fld = split(/[,\s]+/, $_);
  if( $all){
    shift(@fld);
    for $w (@fld){
      $cnt{ $w }++;
    }
  } else {
    $word = shift(@fld);
    $cnt{ $word }++;
  }
}

for $k (sort { $cnt{$b}<=>$cnt{$a} } keys %cnt){
  print "$k --> $cnt{ $k }\n";
}
