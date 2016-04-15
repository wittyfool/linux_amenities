#!/usr/bin/perl -s
$width=100 unless(defined($width));
$pscmd = qq#ps -A --width=120 --format "user pid ppid stime command"#;

open(PIPE, "$pscmd |") || exit 1;
while(<PIPE>){
  chomp;
  s/^\s+//;
  next if(/^UID/);

  @fld = split(/\s+/, $_, 5);
  # ($uid, $pid, $ppid, $c, $stime) = (@fld)[(0..4)];
  ($uid, $pid, $ppid, $stime, $cmd) = (@fld)[(0..4)];

if(0){
  if($stime =~ /:/){
    ($tty, $time) = (@fld)[(5..6)];
    $cmd = join(" ", (@fld)[(7..$#fld)]);
  } else {
    $stime .= $fld[5];
    ($tty, $time) = (@fld)[(6..7)];
    $cmd = join(" ", (@fld)[(8..$#fld)]);
  }
}
   
  ${ $children{ $ppid } }{ $pid } = 1;
  $cmd{ $pid } = $cmd;
  $uid{ $pid } = $uid;
  $stime{ $pid } = $stime;
}

if(defined($user)){
  checkUser(0);
}

trace(0,0, "");

close(PIPE);

exit 0;

sub checkUser {
  my($p) = shift;
  my($cnt)=0;
  my($ret)=0;

  for $k (keys %{ $children{ $p }}){
    next if($k eq $p);
    $cnt++;
    if( checkUser($k)){
      $ret = 1;
    }
  }

  if($cnt==0){ #--- 子プロセスがない場合
    if($uid{$p} eq $user){
      $disp{ $p } = 1;
      return 1 
    }
    return 0;
  } 

  $disp{ $p } = $ret;

  return $ret;
}


sub trace {
  my($p) = shift;
  my($c) = shift;
  my($msg) = shift;
  my($msg2);
  my($cnt)=0;
  my(@list);

  @list = (sort { ($a)<=>($b)} keys %{ $children{ $p }});

  for $k (@list){
    $head = $msg;
    $head =~ s/\s*$//;

    if($msg eq ""){
      $head .= "[$k]";
    } else {
      $head .= "--[$k]";
    }
    next if(defined($user) && ($disp{$k}!=1));

    $out  = padStr($head,    '.', 24).' ';
    $out .= padStr($uid{$k}, ' ',  5).' ';
    $out .= padStr($stime{ $k }, ' ', 7).' ';  #<--- add 01/20
    $out .= $cmd{$k};
    $out = substr($out, 0, $width);
    print $out,"\n";

    if($k eq $list[$#list]){
      # $msg2 = "$msg \\ ";	#------------------ 悩みどころ・・・
      $msg2 = "$msg | ";
    } else {
      $msg2 = "$msg | ";
    }
    if($k != $p){
      $cnt++;
      $cr = 0;
      if(defined($user)){
	trace($k, $c+1, $msg2) if($disp{$k})
      } else {
        trace($k, $c+1, $msg2);
      }
    }
  }
if(0){
  if(($cnt>0)&&($cr==0)){
    $tmp = $msg;
    $tmp =~ s/\|\s*$//;
    print "$tmp\n";
    $cr = 1;
  }
}

}

sub padStr {
  my($str, $pad, $n) = @_;
  my($l,$s) = (0,"");

  $l = length($str);
  if($l < $n){
    $s = $pad x ($n-$l);
  }
  return $str.$s;
} 
