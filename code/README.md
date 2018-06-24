Name :- Rajan Ashok Dhage
MIS :- 111603015

Project Name: 
	Creating source code for sort command line.
Subject Inforamtion :
	'sort' command line sorts any file whose name is entered after the command sort (ex., sort filename ). General sort command sorts contents of file given to it. It sorts that data considering character sequence upto '\n' as one string. And then it sorts that strings alphabatically( for general case) or according to given attributes. There are different attributes for sort command. Example, -b, -d, -g, -f, 
-i, -M etc. and some more.
Project work:
	Writig source code for the attributes that are given follow,
		 -k -n -b  -d  -i  -r  -m  -t -u (we can read more about it by typing 'man sort' on linux terminal)
	Sort command should be able to process data for combination of different attributes also.
Description of work done:-
	I have used Doubly linked NULL terminated list. In the linked list in the node I have stored original string and string made by making all letters small. And same is for kth coloumn.
	I have done all operations on the linked list and printed the results.
