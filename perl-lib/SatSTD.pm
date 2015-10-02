package SatSTD;

use lib '/home/nobu/perl5/lib/perl5';
use Object::Simple -base;
use Data::Dumper;
use Fcntl qw(SEEK_CUR);

has 'src';
has fp => undef;
has blockData => undef;
has debug => 0;

use strict;


sub exists {
  my $self = shift;

  print "src = ".$self->src."\n";
  return 1 if ( -e $self->src);
  return 0;
}

sub open {
  my $self = shift;

  open(my $fp, '<', $self->src) || die "Can't open file";
  print "file opened\n" if($self->debug);
  $self->fp($fp);
  $self->blockData([]);

}

sub block {
  my $self = shift;
  my $number = shift || die "block(<block-number>)";
  my $header = {
      length => 3,
      unpack => "WS",
    };
  

  $self->open() unless ($self->fp);

  my @dat;

  if(($number <1)||($number>12)){
    die "block number=<$number> illegal\n";
  }
  if($number == 12){
    $header->{length} = 0;
  }

#  仕様書 ブロック10 -- タイポ?
#  if($number == 10){
#    $header->{length} = 5;
#    $header->{unpack} = "WL";
#  }

  my $buf = "";
  my $buf2 = "";
  if($header->{length}>0){
    read($self->fp, $buf, $header->{length});
    @dat = unpack( $header->{unpack}, $buf);

    if($self->debug){
      print "=== block[$number] ===\n";
      print Dumper \@dat;
    }

    if($dat[0] != $number){
	die "block number mismatch $dat[0] <=> $number";
    }
    read($self->fp, $buf2, $dat[1] - $header->{length});
  } elsif($number == 12){
    my ($w, $h, $flag) = unpack("x5SSW", $self->blockData->[2]);
    print STDERR "dimention: $w x $h ($flag)\n";
    if($flag == 0){
      read($self->fp, $buf2, $w * $h * 2);
    }

  } else {
    ;
  }

  $self->blockData->[ $number ] = $buf.$buf2;

  if($self->debug){
    print "=== END === \n";
  }

}

sub info {
  my $self = shift;
  my @data = unpack("x5SSW", $self->blockData->[2]);

  return "Info = ".Dumper \@data;

}

sub image {
  my $self = shift;

  return $self->blockData->[12];

}



1;
