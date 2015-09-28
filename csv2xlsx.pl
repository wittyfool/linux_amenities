#!/usr/bin/perl
#
use Encode;
use Excel::Writer::XLSX;

my $book = Excel::Writer::XLSX->new( 'test.xlsx');

my $sheet = $book->add_worksheet();

$sheet->write_utf16be_string(0,0, strPack('�����Ǥ�'));
$sheet->write_utf16be_string(1,1, strPack('�����Ǥ�����'));

sub strPack {
  my $str = shift;

  Encode::from_to($str, "euc-jp", "UTF-16BE");

  return $str;

if(0){
  my $str = decode('euc-jp', shift);
  my @dec = split(//, $str);
  my @split = ();

  map { push(@split, unpack('H*', encode('UTF16BE', $_))) } @dec;
  return pack('n*', map{ hex($_) } @split);
}

}

