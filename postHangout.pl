#!/usr/bin/perl -s
#

$config = readConfig('postHangout.config');

$token = $config->{'token'};
$key = $config->{'key'};
$room = $config->{'room'};
$thread = $config->{'thread'};
#
$url = $config->{'url'}.'/spaces/'.$config->{'room'}.'/messages';


#
$cmd = "curl -s -m 15 -H 'Content-Type:application/json' -d \@- $url\\?key=$key\\&token=$token";
$pipe  = "curl -s -m 15 -H 'Content-Type:application/json' -d \@- $url\\?key=$key\\&token=$token";

print $cmd;
print "\n";

while(<>){
	s/[\r\n]+$//;
	$msg .= $_;
	$msg .= "\\n";
};

$msg =~ s/\n$//;

$threadLine = <<_THREAD_LINE;
 "thread": { "name": "spaces/$room/threads/$thread" }, 
_THREAD_LINE

if($nothread){
  $threadLine = "";
}

if($exec){
	$date = `date`;

	open(PIPE, '|-', $pipe) || die;
	print PIPE <<_PIPE;
{ 
  $threadLine
 "text" : "$msg"
}
_PIPE
	close(PIPE);
} else {
	print <<_PIPE;
{ 
  $threadLine
 "text" : "$msg"
}
_PIPE
}

sub readConfig  {
    my $f = shift;
    my $conf = {};
    open(my $fp, '<', $f) || die;
    while(<$fp>){
        if(/(\S+)\s+(\S+)/){
            $conf->{$1} = $2;
        }
    }
    close($fp);

    return $conf;
}
