#!/usr/bin/perl
####################################################
#
#          Counts the lines badly indentated.
#
####################################################
use strict;
use warnings;
use English;

if($#ARGV < 0) {
	print "Usage: perl indentations.pl folder1 [folder2...]\n";
	exit(0);
}

my $badFiles = 0;
foreach my $folder (@ARGV) {
	$badFiles += countLinesFolder($folder);
}

exit($badFiles);


###########################################################################
#  Iterates recursively on folders to count the lines badly indentated.
###########################################################################
sub countLinesFolder {
	my $badFiles = 0;
	my $dir = $_[0];

	opendir(DIR, $dir);
	my @entries = readdir(DIR);
	closedir DIR;
	foreach my $entry (@entries) {
		if(-d "$dir/$entry" && $entry ne '..' && $entry ne '.') {
			$badFiles += countLinesFolder("$dir$entry/");
		}
	}

	$badFiles += countLinesFiles($dir);

	return $badFiles;
}

##########################################################
#  Counts the files badly indentated in a folder.
##########################################################
sub countLinesFiles {
	my $dir = $_[0];
	my $badFiles = 0;
	foreach my $fp (glob("$dir*.cpp $dir*.h $dir*.pro")) {
		unless($fp =~ /qcustomplot\.(h|cpp)$/) {
			open my $fh, "<", $fp or die "can't read open '$fp': $OS_ERROR";
			my $nbBadIndentations = 0;
			while(my $line = <$fh>) {
				if($line =~ /^[ ]{3}/) {
					$nbBadIndentations++;
				}
			}
			if($nbBadIndentations > 0) {
				print "$fp contains $nbBadIndentations lines badly indentated.\n";
				$badFiles++;
			}
			close $fh or die "can't read close '$fp': $OS_ERROR";
		}
	}
	return $badFiles;
}
