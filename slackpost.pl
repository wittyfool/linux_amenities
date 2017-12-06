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
if(defined($channel)){
  $arg->{'channel'} = $channel;
} else {
  $arg->{'channel'} = 'scsk';
}


use strict;

my $url = readUrl();
my $channel = $arg->{'channel'};

die "url is empty..." unless($url =~ /./);

my $text;
while(<>){
  $text .= $_;
}

my $json = qq/{ "channel": "#$channel", "text": "/.$text.qq/"}/;
my $cmd  = qq/curl -s -X POST --data-urlencode 'payload=/.$json. qq/' /. $url;

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
    if(/([\w\.]+):\s*(\S+)/){
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
