#!/usr/bin/perl
my $src = shift || die;
my $hostDst = shift || die;

my ($host, $dst);

if($hostDst =~ /(.+):(.*)/){
    $host = $1;
    $dst = $2;
    if($dst eq ""){
      $dst = $src;
    } elsif($dst =~ /\/$/){
      $dst = $dst.$src;
    }
} else {
  die;
}

print "src[$src]\n";
print "dst[$dst]\n";
print "host[$host]\n";

$cmd = qq#(echo "put $src $dst"; echo "ls -l $dst"; echo "quit") | /usr/bin/sftp $host#;

print "cmd[$cmd]\n";

$ret = system($cmd);

print "ret[$ret]\n";

if($ret == 0){
  exit 0;
}
exit 1;
