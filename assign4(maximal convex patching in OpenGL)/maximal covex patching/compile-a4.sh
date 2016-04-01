#!/bin/bash
GCCVERSION="$(g++ --version | grep ^g++ | sed 's/^.* //g')"
echo "g++ version installed is ${GCCVERSION}"
BASEVERSION=4.9
GCCVERSION=${GCCVERSION%.*}
#echo $GCCVERSION, $BASEVERSION
var=$(awk 'BEGIN{ print "'$GCCVERSION'"<"'$BASEVERSION'" }')
if [ "$var" -eq 1 ];then
	echo "You need g++ version >= 4.9 to correctly compile this program. Earlier g++ versions will show unexpected behaviors."
	exit
else
	echo "You have compatible g++ version to compile this program"
fi

g++ -std=c++11 -lglut -lGLU run.cpp -o run.out
echo "run.out created"
