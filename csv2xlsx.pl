#!/usr/bin/perl
#
use Encode;
use Excel::Writer::XLSX;

my $book = Excel::Writer::XLSX->new( 'test.xlsx');

my $sheet = $book->add_worksheet();

$sheet->write_utf16be_string(0,0, strPack('漢字です'));
$sheet->write_utf16be_string(1,1, strPack('本当ですか？'));


sub strPack {
  my $str = shift;

  Encode::from_to($str, "euc-jp", "UTF-16BE");

  return $str;


}

