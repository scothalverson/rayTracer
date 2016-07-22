#!/bin/bash
directory="output"
executable="rayTracer"
options="-v -f ../rdlFiles/sphere_cube_base.rdl --width 800 --height 600 --samples 9 -o test.png"

if [ "$1" = "rebuild" ]; then
{
	echo "rebuilding..."
	echo "********************************************************************************"
	echo "Building RDL Library..."
	cd rdlLanguageParser
	cmake .
	make
	cd ..
	echo "Done buidling RDL Library."
	echo "********************************************************************************"
	rm -r output
	mkdir output
	cd output
	cmake ..
	make

	echo "done rebuilding."
}
elif [ "$1" = "clean" ]; then
{
	echo "cleaning up..."
	rm -r output
	echo "done cleaning."
}
else
{
	if [ -d $directory ]; then
	{
		echo "not rebuilding..."

		cd output
		make

		echo "done compiling."
	}
	else
	{
		echo "rebuild not specified, but $directory does not exist.  rebuilding..."
		echo "********************************************************************************"
		echo "Building RDL Library..."
		cd rdlLanguageParser
		cmake .
		make
		cd ..		
		echo "Done buidling RDL Library."
		echo "********************************************************************************"
		mkdir output
		cd output
		cmake ..
		make
	}
	fi
}
fi

if [ "$2" = "run" ] && [ $1 != "clean" ]; then
{
	./$executable $options
}
elif [ "$1" = "run" ]; then
{
	time ./$executable $options
}
fi 

