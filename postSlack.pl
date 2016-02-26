#!/usr/local/bin/perl
# url = # 'https://hooks.slack.com/services/AAAAAAAAA/BBBBBBBBB/CCCCCCCCCCCCCCCCCCCCCCCC';
#
$url = `cat ~/.postSlack.url`;
$url =~ s/[\r\n]+//;

print "| curl -X POST --data-binary \@- $url \n";

while(<>){
  s/[\r\n]+$//;
  last if(/^\s*$/);
  $date = `date +%Y-%m%d-%k:%M`;
  $date =~ s/[\r\n]+//;
  s/$/ $date/;

  next if(/^$last$/);
  open(PIPE, "| curl -s -o /dev/null  -X POST --data-binary \@- $url");
  print PIPE qq/payload={"text": "$_" } /;
  close(PIPE);
  $last = $_;
  print $last;
  print "\n";
}
