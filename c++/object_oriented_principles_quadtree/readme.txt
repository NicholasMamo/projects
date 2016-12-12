To run the program, the following steps are required. All steps should be followed in the terminal:
    1. cd path/to/directory
    2. g++ -std=c++11 -Wall -o main *.cpp && ./main
    
Upon compiling and running, a help screen will be displayed with the following instruction:

Please enter the commands in the following format. The type and filename may be omitted as indicated: 
command [type] [filename]
Commands: 
	load type filename - load the given quadtree file having the indicated color type
	save filename - save the current quadtree file
	convert type filename - convert the given image file made up of the indicated color type
	show - print the current quadtree
	help - show this text
	quit - quit the program
Colors: 
	Boolean
	Color
	Monochrome
	
All commands are case-insensitive.
