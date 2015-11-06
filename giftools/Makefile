INCLUDE=/usr/local/include/gd1.2
LIB=/usr/local/lib/libgd-1.2.a
 
all : gifinfo gifpalet gifadjust gifcaption gifpaste gifgrey gifsplit gifdiff gifcomp gifscale gifadjust3 gifbit gifUserPalet gifcopy

install:
	cp -i gifinfo gifpalet gifadjust gifcaption gifpaste gifgrey gifsplit gifdiff gifcomp gifscale gifadjust3 gifbit gifUserPalet gifcopy /usr/local/bin/

gifinfo : gifinfo.c
	gcc -I$(INCLUDE) gifinfo.c $(LIB) -lm -o gifinfo

gifpalet : gifpalet.c
	gcc -I$(INCLUDE) gifpalet.c $(LIB) -lm -o gifpalet

gifadjust : gifadjust.c
	gcc -I$(INCLUDE) gifadjust.c $(LIB) -lm -o gifadjust

gifadjust3 : gifadjust3.c
	gcc -I$(INCLUDE) gifadjust3.c $(LIB) -lm -o gifadjust3

gifcaption : gifcaption.c
	gcc -I$(INCLUDE) -DDIRE=\"`pwd`\" gifcaption.c $(LIB) -lm -o gifcaption

gifscale : gifscale.c
	gcc -I$(INCLUDE) -DDIRE=\"`pwd`\" gifscale.c $(LIB) -lm -o gifscale

gifgrey : gifgrey.c
	gcc -I$(INCLUDE) -DDIRE=\"`pwd`\" gifgrey.c $(LIB) -lm -o gifgrey

gifpaste : gifpaste.c
	gcc -I$(INCLUDE) -DDIRE=\"`pwd`\" gifpaste.c $(LIB) -lm -o gifpaste

gifsplit : gifsplit.c
	gcc -I$(INCLUDE) -DDIRE=\"`pwd`\" gifsplit.c $(LIB) -lm -o gifsplit

gifbit : gifbit.c
	gcc -I$(INCLUDE) -DDIRE=\"`pwd`\" gifbit.c $(LIB) -lm -o gifbit

gifUserPalet : gifUserPalet.c
	gcc -I$(INCLUDE) -DDIRE=\"`pwd`\" gifUserPalet.c $(LIB) -lm -o gifUserPalet
gifdiff : gifdiff.c
	gcc -I$(INCLUDE) -DDIRE=\"`pwd`\" gifdiff.c $(LIB) -lm -o gifdiff

gifcomp : gifcomp.c
	gcc -I$(INCLUDE) -DDIRE=\"`pwd`\" gifcomp.c $(LIB) -lm -o gifcomp

gifcopy : gifcopy.c
	gcc -I$(INCLUDE) -DDIRE=\"`pwd`\" gifcopy.c $(LIB) -lm -o gifcopy

