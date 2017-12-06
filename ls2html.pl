#!/usr/bin/perl -s
#
# -image : ‰æ‘œ—p
#
$dir = shift || do {
  $dir = '.';
};

if(opendir(DIR, $dir)){
  @files = readdir(DIR);
  closedir(DIR);
}

#print join(", ", @files);
#print "\n";

print <<_HTML;
<!DOCTYPE html>
<html>
<head>
</head>
<body>
<pre>

_HTML

print "[$dir]\n";
for $f (sort @files){
  next if ($f =~ /^\./);
  if($image){
    print qq|<img src="$dir/$f"> $dir/$f <br />\n|;
  } else {
    print qq|<a href="$dir/$f"> $f </a>\n|;
  }
}

print <<_HTML;
</pre>
</body>
</html>
_HTML
