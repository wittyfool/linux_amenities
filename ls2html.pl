#!/usr/bin/perl
$dir = shift || do {
  $dir =  '.';
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
  print qq|<a href="$dir/$f"> $f </a>\n|;
}

print <<_HTML;
</pre>
</body>
</html>
_HTML
