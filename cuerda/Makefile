all: cuerda.gif *.png datos_cuerda.dat

cuerda.gif:*.png
	convert -loop 0 -delay 3 *.png cuerda.gif

*.png:datos_cuerda.dat
	python animacion.py

datos_cuerda.dat:cuerda.x
	./cuerda.x

cuerda.x:cuerda.c
	gcc -o cuerda.x cuerda.c -lm

clean:
	rm *.png
	rm cuerda.x
	rm datos_cuerda.dat
