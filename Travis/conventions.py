#!/usr/bin/python3

import os
import sys
import re
import time

# Counts the files which don't respect the coding conventions in a folder.
def countBadFiles(folderPath):
	nbBadFiles = 0;

	# Iterates on all the files.
	for root, subFolders, files in os.walk(folderPath):
		for filename in files:
			filePath = os.path.join(root, filename)

			# Counts the files badly indentated:
			if re.search('\.(cpp|h|pro)$', filename) and not re.search('^qcustomplot\.', filename):
				nbBadIndentations = countBadLines(filePath)
				if nbBadIndentations > 0:
					nbBadFiles += 1

			# Counts the source C++ files with missplaced includes.
			if re.search('\.cpp$', filename) and filename!='main.cpp':
				nbBadIncludes = countBadIncludes(filePath, filename)
				if nbBadIncludes > 0:
					nbBadFiles += 1

			# Counts the source C++ files with duplicate includes.
			if re.search('\.h$', filename):
				nbDuplicates = countDuplicateIncludes(filePath)
				if nbDuplicates > 0:
					nbBadFiles += 1

	return nbBadFiles


# Counts the lines badly indentated in a file.
def countBadLines(filePath):
	fp = open(filePath, 'r')
	nbBadIndentations = 0
	lines = []
	numLine = 1
	for line in fp:
		if re.search('^[ ]{3}', line):
			nbBadIndentations += 1
			lines.append(numLine)
		numLine += 1
	fp.close()
	
	if nbBadIndentations > 0:
		#print("%s contains %d lines badly indentated" %(filePath, nbBadIndentations))
		sys.stdout.write("%s contains %d lines badly indentated (" %(filePath, nbBadIndentations))
		for i in range(len(lines)-1):
			sys.stdout.write("%d, " %(lines[i]))
		sys.stdout.write("%d).\n" %(lines[len(lines)-1]))
		sys.stdout.flush()
	return nbBadIndentations


# Counts includes which should be in the header file.
def countBadIncludes(filePath, filename):
	baseFilename, extension = os.path.splitext(filename)
	headerFilename = baseFilename + '.h'
	nbBadIncludes = 0

	fp = open(filePath, 'r')
	for line in fp:
		matches = re.match('^\s*#include\s+(.+)$', line)
		if matches:
			include = matches.group(1)
			if include!='"'+headerFilename+'"' and include!='"ui_'+headerFilename+'"':
				nbBadIncludes += 1
		elif re.search('^\w+::\w+\(', line):
		# The start of a method indicates the end of the includes in a source file.
			break
	fp.close()

	if nbBadIncludes > 0:
		print("%s contains %d misplaced include directives." %(filePath, nbBadIncludes))
	return nbBadIncludes


# Counts duplicate includes in header files.
def countDuplicateIncludes(filePath):
	fp = open(filePath, 'r')
	duplicates = []
	nbDuplicates = 0
	for line in fp:
		matches = re.match('^\s*#include\s+(.+)$', line)
		if matches:
			include = matches.group(1)
			if include in duplicates:
				nbDuplicates += 1
			else:
				duplicates.append(include)
		elif re.search('^class\s', line):
		# The start of the class indicates the end of the includes in a header file.
			break
	fp.close()

	if nbDuplicates > 0:
		print("%s contains %d duplicate include directives." %(filePath, nbDuplicates))
	return nbDuplicates


# Main
nbBadFiles = 0
for folderPath in sys.argv:
	nbBadFiles += countBadFiles(folderPath)

exit(nbBadFiles)
