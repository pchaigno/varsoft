#!/usr/bin/python3
import os
import sys
import re
import time

def countLines(folderPath):
	nbLines = 0;

	# Iterates on all the files.
	for root, subFolders, files in os.walk(folderPath):
		for filename in files:
			filePath = os.path.join(root, filename)

			# Counts the lines:
			if re.search('\.(cpp|h|pro|ui|java|py|sh)$', filename) and not re.search('^qcustomplot\.', filename):
				fp = open(filePath, 'r')
				for line in fp:
					nbLines += 1
				fp.close()

	return nbLines


# Main
nbLines = 0
for folderPath in sys.argv:
	nbLines += countLines(folderPath)

print nbLines
exit(0)
