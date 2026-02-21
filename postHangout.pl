#!/usr/bin/perl -s
#
use JSON;

$config = readConfig('postHangout.config.json');

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
    open(my $fp, '<', $f) || die "Cannot open config file '$f': $!";
    local $/;
    my $text = <$fp>;
    close($fp);

    my $conf = eval { decode_json($text) };
    die "Failed to parse JSON config file '$f': $@" if $@;
    return $conf;
}
