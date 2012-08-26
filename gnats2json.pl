#!/usr/pkg/bin/perl
use JSON;
use Data::Dumper;

my $gdb = "/var/tmp/gnatsdb/home/gnats/gnatsdb";
my $txt;
my %p;
my $infield = "Header";

while(<>)
{
  if ( m#^>([A-Z].+?):\s*(.*)\s*$# )
  {
    $txt = "";
    $txt = $2;
#clean up whitespace
    chomp $p{$infield};
    #$p{$infield} =~ s#\s+$##g;
    #$p{$infield} =~ s#^\s+##g;
    $infield = $1;
    $p{$infield} = $txt;
  } else {
    $p{$infield} .= $_;
  }
}

#print Dumper \%p;
#my %{$p{Number}} => %p;
push(@j, \%p);
my $json = to_json( \@j, {pretty => 1} );
#my $cmd = "curl -vvv localhost:8983/solr/update/json -H 'Content-type:application/json' -d \'$json\'";
#print "$cmd\n";
#qx#"$cmd"#;
print "$json";
