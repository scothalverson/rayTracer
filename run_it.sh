#!/bin/bash
mkdir output/generated
cd rdlFiles
FILES=*
for f in $FILES
do
	echo "Processing $f file..."
	cd ../output/
	time ./rayTracer -v -f ../rdlFiles/$f --width 1024 --height 768 --samples 8 -o $f.png
	cd ../rdlFiles/
  
done
cd ../output
FILES=*.png
for f in $FILES
do
	mv $f generated/$f
done
