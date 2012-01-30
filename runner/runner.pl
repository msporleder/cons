#!/usr/pkg/bin/perl
use warnings;
use strict;
use POSIX;

use Getopt::Std;
getopts("p:t:a:f:o:");
our($opt_p, $opt_t, $opt_a, $opt_f, $opt_o);

my $prog = $opt_p || die usage();
my $args = $opt_a || die usage();
my $th   = $opt_t || die usage();
my $pidf  = $opt_f || die usage();
my $kido = $opt_o || die usage();

sub usage
{
  print STDERR "$0 -p /path/to/prog -a \"args\" -t #forks -f pidfile -o kid_stdout\n";
}
close STDOUT;
close STDIN;
close STDERR;

my %kids;

if (fork())
{
  exit 0;
}
else
{

FORKIT:
while (scalar keys(%kids) < $th)
{
  my $pid = fork;
  if ($pid)
  {
    #parent
    #when the child dies (system finishes and we hit exit 0)
    #it will reap and make another one
    POSIX::setsid() or die "could not detach $!";
    $kids{$pid} = 0;
    open(PIDF, ">$pidf");
    print PIDF "$$";
    close PIDF;
    while (1)
    {
      my $k = waitpid(-1,WNOHANG);
      if ($k > 0 and exists $kids{$k})
      {
        #print "parent: $k went away\n";
        delete $kids{$k};
      }
      if (scalar keys(%kids) < $th)
      {
        next FORKIT; #I love goto
      }
    }
  }
  else
  {
    #child
    close STDOUT;
    close STDIN;
    close STDERR;

    open(STDOUT, '>>', $kido);
    open(STDERR, ">&STDOUT");
    print "child: running $prog $args: $$\n";
    system("$prog $args");
    exit 0;
  }
}

}
