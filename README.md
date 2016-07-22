Readme.txt

Notes on use:

There are two scripts that should do everything necessary to test the program:

./build.sh :
	This script compliles the raytracer.  

	Options:

		run - compliles the executable using a previously generated make file,  
		then runs the raytracer on a single input file.  the options it specifies are:
			-v -f ../rdlFiles/multilights.rdl --width 1024 --height 768 -o test.png"

			meaning:

				-v - for verbose mode
				-f ../rdlFiles/multilights.rdl - specifies the input file
				--width 1024 - sets the width of the output file
				--height 768 - sets the height of the output file
				-0 test.png - specifies the base filename for the output
			
			./build.sh run	

		rebuild - completely rebuilds the project, but does not execute it.  if the project is already compiled,
		this will delete the build directory, then rebuild

			./build.sh rebuild			
	
		clean - deletes the build/output directory

			./build.sh clean

./runMe.sh :
	This script runs the raytracer using all .rdl files found in the rdlFiles directory.  generated PNGs are located
	in "output/generated/" in the format cameraName.baseFileName.rdl.png	
	
	Note that this process will take a really long time, particularly if there are a number of rdl files, 
	or if they are complex.  Also note that there is not a good way as of yet to apply transformations to an 
	instanced shape without changing the source code.  I've added a couple scale transformations to the sphereInstance.cpp
	file as an example.  Uncomment line 22 OR 23 to test this.  Note that this will require a rebuild.
