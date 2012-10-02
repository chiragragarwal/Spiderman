code:
	gcc -c spidey.c -o spidey.o
	gcc -c inputMatrix.c -o inputMatrix.o
	gcc -o spider spiderMain.c spidey.o inputMatrix.o

clean:
	rm -r spidey.o inputMatrix.o	

