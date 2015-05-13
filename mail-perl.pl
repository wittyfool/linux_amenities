#!/usr/bin/perl -s
use Data::Dumper;
my $arg = {
	debug => $debug,
	src => $src,
};

if(!defined($src)){
	die "Need -src=????";
}

#
my $sendmail = '/usr/sbin/sendmail';
my $template = $arg->{src};

use CGI;
use MIME::Base64;
use Jcode;
use strict;

my $uuid = `/usr/bin/uuidgen`;
$uuid =~ s/[\r\n]+//;
my $uuid_short = $uuid;
$uuid_short =~ s/\-.+//;
my $msg;
my $templateText = "";

if(!open(fh, '<', $template)){
	die "Can't open config file.";
}

while(<fh>){
  $templateText .= $_;
}
close(fh);

{
	my $bind = {};

	for my $k (keys %ENV){
		$bind->{ 'ENV_'.$k } = $ENV{ $k };
	}
	$bind->{ ENV } = Dumper \%ENV;
	$bind->{ uuid } = $uuid;
	$bind->{ uuid_short } = $uuid_short;

    if(defined($templateText)){
		$msg = evalTemplate($templateText, $bind );

		# MIME 処理
		my $header = 1;
		my $message;
		my @message = split(/\n/, $msg);
		for my $m (@message){
			if(/^$/){
				$header = 0;
			}
			if($header && $m =~ /^Subject: (.+)/){
				$message .= "Subject: =?utf-8?B?".encode_base64($1, "")."?=";
			} else {
				$message .= $header ? $m : Jcode::convert($m, 'jis', 'utf-8');
			}
			$message .="\n";
		}
		# ----

		if( !open(fh, '|'. $sendmail.' -t')){
			outputExit("Can't send mail");
		} else {
			print fh $message;
			close(fh);
		}

		if(1){
			if( !open(fh, '>', '/var/tmp/maillog.txt')){
				warn "Can't send maillog";
			} else {
				print fh $message;
				close(fh);
			}
		}

	} else {
		$msg = qq/Can't open config file./;
	}
}


# ---------------------- END of MAIN -----------

sub evalTemplate {
	my $temp = shift;
	my $hash = shift;

	my $evaluated = $temp;
	while( $evaluated =~ /\[%\s+(\S+)\s+%\]/){
		my $e = ( $hash->{$1} ?  $hash->{$1} : '<空欄>' );
		$evaluated = $`.$e.$';
	}

	return $evaluated;
}
