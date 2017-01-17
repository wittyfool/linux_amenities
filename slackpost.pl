#!/usr/bin/perl -s
#
#
use Data::Dumper;
my $arg;

if(defined($key)){
  $arg->{'key'} = $key;
}
if(defined($exec)){
  $arg->{'exec'} = $exec;
}

use strict;

my $url = readUrl();

my $text;
while(<>){
  $text .= $_;
}

my $json = qq/{ "channel": "#scsk", "text": "/.$text.qq/"}/;

my $cmd  = qq/curl -s -X POST --data-urlencode /;
$cmd .= qq/ 'payload=/.$json. qq/' /. $url;

if($arg->{exec}){
  print `$cmd`;
} else {
  print "[$cmd]\n";
}


sub readUrl {
  my $urlHash;
  my $urlArray;

  open(FP, $ENV{'HOME'}."/.slack") || die "Can't open ~/.slack";
  while(<FP>){
    next if(/^#/);
    if(/(\w+):\s*(\S+)/){
      $urlHash->{ $1} = $2;
      push(@$urlArray, $2);
    }
  }
  close(FP);

  my $url;
  if(defined($arg->{ 'key'})){
    $url = $urlHash->{ $arg->{'key'}};
  } else {
    $url = $urlArray->[0];
  }

  #print "url=[$url]\n";

  return $url;
}
