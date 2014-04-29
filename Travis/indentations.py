#!/usr/bin/python3

import os
import sys
import re

# Counts the files badly indentated in a folder.
def countLinesFolder(folderPath):
	nbBadFiles = 0;
	# Iterates on all the files.
	for root, subFolders, files in os.walk(folderPath):
		for filename in files:
			if re.search('\.(cpp|h|pro)$', filename) and not re.search('^qcustomplot\.', filename):
				filePath = os.path.join(root, filename)
				nbBadIndentations = countLinesFile(filePath)
				if nbBadIndentations > 0:
					nbBadFiles += 1

	return nbBadFiles


# Counts the lines badly indentated in a file.
def countLinesFile(filePath):
	fp = open(filePath, 'r')
	nbBadIndentations = 0;
	for line in fp:
		if re.search('^[ ]{3}', line):
			nbBadIndentations += 1
	fp.close()
	
	if nbBadIndentations > 0:
		print("%s contains %d lines badly indentated." %(filePath, nbBadIndentations))
	return nbBadIndentations


# Main
nbBadFiles = 0
for folderPath in sys.argv:
	nbBadFiles += countLinesFolder(folderPath)

exit(nbBadFiles)