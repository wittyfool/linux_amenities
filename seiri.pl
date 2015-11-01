#!/usr/bin/perl -s
#
# out put of find
$path = shift;

if($old){
  $oldMeans = $old;
} else {
  $oldMeans = 10;
}

if($dst){
  $dstPath = $dst;
} else {
  $dstPath = ".";
}

open(FP, "find $path -maxdepth 1 -type f |") || die "find <$path> failed";
while(<FP>){
  s/[\r\n]+//;

  if($verbose){
    print $_, "\n";
  }

  next unless ( -e $_ );
  next if ( -M $_ < $oldMeans);
  
  if(/(20\d\d)(\d\d)/){
    push(@cmd, "mv $_ $dstPath/$1_$2");
    $mkdir{ "mkdir $dstPath/$1_$2" } = 1;
  } elsif(/(\d\d)-(\d\d)-\d\d/){
    push(@cmd, "mv $_ $dstPath/$1$2");
    $mkdir{ "mkdir $dstPath/$1$2" } = 1;
  } elsif(/\d\d\d\d/){
    push(@cmd, "mv $_ $dstPath/$&");
    $mkdir{ "mkdir $dstPath/$&" } = 1;
  } elsif(/\d\d\-\d\d/){
    push(@cmd, "mv $_ $dstPath/$&");
    $mkdir{ "mkdir $dstPath/$&" } = 1;
  } else {
    print "Skip $_ \n";
  }
}
close(FP);

print join("\n", map { s/mkdir/mkdir -p/; $_ } sort keys %mkdir),"\n";
print join("\n", @cmd),"\n";

