#!/usr/bin/perl -s
# Usage : attachMail.pl [-smtp=mysmtp.foo.jp] from@somewhere.com \
# to@somewhere subject(euc) contents-file attachfile
#
# http://homepage3.nifty.com/hippo2000/perltips/perlmail.htm
#
#

alarm($timeout) if($timeout);

use Encode;
use Net::SMTP;
use MIME::Entity;
use MIME::Words qw (:all);

if(defined($smtp)){
  $smtpServer = $smtp;
} else {
  print "-smtp=???\n";
  die;
}


print STDERR "[$smtpServer]\n" if($debug);

$from    = shift || usage();
$to      = shift || usage();
$subject = shift || usage();
$contents = shift || usage();
$attach  = shift;

$subject =~ s/^\"//;
$subject =~ s/\"$//;

$subject = encode_mimeword(encode('jis', decode('euc-jp', $subject)), 'B', 'iso-2022-jp');

getHonbun();

#unless( -e $contents){
#  die "[$contents] not found.\n";
#}
#
#open(FP, $contents) || die "Can't open [$contents].\n";
#while(<FP>){
#  s/%%SUBJECT%%/$subject/g;
#  push(@honbun, $_);
#}
#close(FP);

$smtp = Net::SMTP->new($smtpServer) or die "Can't connect smtp server.";
doSend();

#SMTP接続の終了
$smtp->quit;

print "OK\n";
alarm(0) if($timeout);
exit 0;


sub doSend {

  $smtp->mail($from);
  $smtp->to($to);
  
  #データ部の組み立て
  $smtp->data();
  $mm = MIME::Entity->build(
	From => $from,
	To   => $to,
	Subject => $subject,
	Type => 'text/plain;charset="iso-2022-jp"',
	Data => \@honbun,
	Encodeing => "7bit"	);

  if($attach){
    $mm->attach( Path => $attach,
	Type => 'application/octet-stream',
	Disposition => 'attachment',
	Encoding   => 'Base64'  );
  }

  $smtp->datasend($mm->stringify);

  # データの終わり、メール送信
  $smtp->dataend(); 
}

sub usage {
print <<USAGE;
# Usage : attachMail.pl [-smtp=mysmtp.foo.jp] from\@somewhere.com \
# to\@somewhere subject contents-file attach-file
USAGE

  exit 1;
}


sub getHonbun {
  if($body){			# -body オプションでメール本文を直接コマンドラインから取る
    push(@honbun, $contents);
    return ;
  }
  unless( -e $contents){
    die "[$contents] not found.\n";
  }

  open(FP, $contents) || die "Can't open [$contents].\n";
  while(<FP>){
    s/%%SUBJECT%%/$subject/g;
    push(@honbun, $_);
  }
  close(FP);
}


