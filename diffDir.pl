#! /usr/bin/perl -w
    eval 'exec /usr/bin/perl -S $0 ${1+"$@"}'
        if 0; #$running_under_some_shell

use strict;
use File::Find ();
use Data::Dumper;

my $dir1 = shift || die;
my $dir2 = shift || die;
my $hash1 = {};
my $hash2 = {};
my $hash;
my $start = `pwd | chop`;

# Set the variable $File::Find::dont_use_nlink if you're using AFS,
# since AFS cheats.

# for the convenience of &wanted calls, including -eval statements:
use vars qw/*name *dir *prune/;
*name   = *File::Find::name;
*dir    = *File::Find::dir;
*prune  = *File::Find::prune;

sub wanted;



# Traverse desired filesystems
$hash = $hash1;
File::Find::find({wanted => \&wanted}, $dir1);

$hash = $hash2;
File::Find::find({wanted => \&wanted}, $dir2);

#print Dumper $hash1;
#print Dumper $hash2;

for my $k (sort keys %$hash1){
  if( !defined($hash2->{$k})){
    print " [$k] not found in [$dir2]\n";
    next;
  }
  if( $hash1->{ $k } ne $hash2->{ $k }){
    print " [$k] differ \n";
  }
}

exit;


sub wanted {
    my ($dev,$ino,$mode,$nlink,$uid,$gid);
    my ($full, $sum);

    (($dev,$ino,$mode,$nlink,$uid,$gid) = lstat($_)) &&
    do {
    # print("$name\n");
    #
      $full = $start.'/'.$name;

	if( -f $full){
          $sum = `sum $full`;
	  $sum =~ s/[\r\n]//;
          $hash->{ $name } = $sum;
	  #print "$name : $sum\n";
	} else {
	  #print "[$start][$name][$dir]\n";
        }
      ;
    };
}

