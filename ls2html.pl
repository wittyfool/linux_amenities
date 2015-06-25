#!/usr/bin/perl
$dir = shift // '.';

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
for $f (@files){
  next if ($f =~ /^\./);
  print qq|<a href="$dir/$f"> $f </a>\n|;
}

print <<_HTML;
</pre>
</body>
</html>
_HTML
