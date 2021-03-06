#!/usr/bin/perl -s
#
$url = `grep url postHangout.config | cut -f 2`;
$token = `grep token postHangout.config | cut -f 2`;
$key = `grep key postHangout.config | cut -f 2`;
$room = `grep room postHangout.config | cut -f 2`;
$thread = `grep thread postHangout.config | cut -f 2`;

$url =~ s/[\r\n]+$//;
$token =~ s/[\r\n]+$//;
$key =~ s/[\r\n]+$//;
$room =~ s/[\r\n]+$//;
$thread =~ s/[\r\n]+$//;
$url .= "/spaces/$room/messages";
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
