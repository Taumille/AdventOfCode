all:
	rm main || echo "No file to remove"
	gcc -Wall -fstack-protector -g --static -o main part2.c -lm
	./main

fun:
	rm main || echo "No file to remove"
	gcc -Wall -g --static -o main mainfun.c
	./main
