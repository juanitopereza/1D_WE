all: datosE.dat datosLF.dat solversE.x solversLF.x soluciones.pdf errores.pdf

soluciones.pdf errores.pdf: datosE.dat datosLF.dat plots.py
	python plots.py
datosE.dat: solversE.x
	./solversE.x
datosLF.dat: solversLF.x
	./solversLF.x
solversE.x: solversE.cpp
	gcc -o solversE.x solversE.cpp
solversLF.x: solversLF.cpp
	gcc -o solversLF.x solversLF.cpp

clean:
	rm *.dat *.x
