#! /usr/bin/env python

import os
import sys
import time
import re

change_no = 0

def main():
	i = 0
	for arg in sys.argv[1:]:
		print arg
#		for i >= 1:
#			print "Too many arguments, bailing out !!\n"
#			sys.exit()
#			break
		change_no = int(arg)
		i = i + 1

	if i == 0:
		print "No cmd line args passed !! change_no[%d]\n" % change_no
	else:
		print "Change number is [%d]\n" % change_no


if __name__ == "__main__":
	main()

	print "main: Change number [%d]\n " % change_no

	if change_no > 0:
		print "Delete change number [%d]\n" % change_no
	else:
		print "No change number passed !!\n"


