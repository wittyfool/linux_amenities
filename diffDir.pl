#! /usr/bin/perl -s

#! /usr/bin/perl -w
#    eval 'exec /usr/bin/perl -S $0 ${1+"$@"}'
#        if 0; #$running_under_some_shell


my $arg = {
  debug => $debug,
};

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

print Dumper $hash1 if $arg->{debug};
print Dumper $hash2 if $arg->{debug};

my $kk;

for my $k (sort keys %$hash1){
  ($kk = $k ) =~ s/^$dir1/$dir2/;

  if( !defined($hash2->{$kk})){
    print " [$k] not found in [$dir2]\n";
    next;
  }
  if( $hash1->{ $k } ne $hash2->{ $kk }){
    print " [$k] differ \n";
  }
}

exit;


sub wanted {
    my ($dev,$ino,$mode,$nlink,$uid,$gid);
    my ($full, $sum);

    (($dev,$ino,$mode,$nlink,$uid,$gid) = lstat($_)) &&
    do {
      print("wanted: $name\n") if($arg->{debug});
    #
      if($name =~ /^\//){
        $full = $name;
      } else {
        $full = $start.'/'.$name;
      }

	if( -f $full){
          $sum = `sum $full 2>/dev/null`;
	  $sum =~ s/[\r\n]//;
          $hash->{ $name } = $sum;
	  #print "dir[$dir] name[$name] : sum[$sum]\n";
	} else {
	  print "Not file?? [$start][$name][$dir]\n" if($arg->{debug});
        }
      ;
    };
}

