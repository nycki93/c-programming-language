default:
	echo No project specified

hello: hello.c	
	gcc hello.c -o hello

2-2-getline: 2-2-getline.c
	gcc 2-2-getline.c -o 2-2-getline

2-3-hex-to-int: 2-3-hex-to-int.c
	gcc 2-3-hex-to-int.c -o 2-3-hex-to-int

clean:
	rm -f \
		hello \
		2-2-getline \
		2-3-hex-to-int
