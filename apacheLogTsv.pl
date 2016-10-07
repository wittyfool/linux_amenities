#!/usr/bin/perl -s
use Data::Dumper;

while(<>){
  s/[\r\n]+$//;
  @fld = split(/\s+/, $_);

  $uq = unQuote( \@fld );

  print join("\t", @$uq);
  print "\n";
}

sub unQuote {
  my $ar = shift;
  my $quote = 0;
  my $word = "";
  my $list = [];

  foreach $a (@$ar){

    if(($a =~ /^[\["]/) && !($a =~ /"$/)){
	  $quote = 1;

    } elsif($a =~ /[\]"]$/){
	  $word =~ s/^\ //;
      push(@$list, $word.' '.$a);
	  $quote = 0;
	  $word = "";
	  next;
    }

	if($quote){
	  $word .= ' '.$a;
    } else {
      push(@$list, $a);
    }
  }

  return $list;
}
    
