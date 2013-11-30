#!/usr/bin/perl

use warnings;
use strict;
my $test_dir = $ENV{"DALE_TEST_DIR"} || ".";
$ENV{PATH} .= ":.";

use Data::Dumper;
use Test::More tests => 3;

my @res = `dalec $ENV{"DALE_TEST_ARGS"} $test_dir/t/src/refs-basic.dt -o refs-basic`;
is(@res, 0, 'No compilation errors');

@res = `./refs-basic`;
is($?, 0, 'Program executed successfully');

chomp for @res;
is_deeply(\@res, [qw(0 1 2)], 'Got expected results');

if (@res) {
    print Dumper(\@res);
}

`rm refs-basic`;

1;