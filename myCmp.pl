#!/usr/bin/perl
#
# バイナリファイルを比較して(short値)
# 相違の比率を報告
#
$f1 = shift || die;
$f2 = shift || die;

open($fp1, '<', $f1) || die;
open($fp2, '<', $f2) || die;

$eq_cnt=0;
$cnt=0;
while(1){
  read($fp1, $x1, 2) or last;
  read($fp2, $x2, 2) or last;
  $x1 = unpack('s', $x1);
  $x2 = unpack('s', $x2);
  $cnt++;
  if($x1 == $x2){
    $eq_cnt++;
    # print "x1,x2=[$x1][$x2]\n";
  }
}

$eq = int(($eq_cnt/ $cnt) * 100);

print "cnt=[$cnt] eq=[$eq_cnt]  $eq% equal    [$f1] [$f2]\n";
