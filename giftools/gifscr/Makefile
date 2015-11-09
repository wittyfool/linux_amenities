INCLUDE=/usr/local/include/gd
LIB=/usr/local/lib/libgd.a
OBJ= readim.o image.o effect.o

gifscr: $(OBJ) main.o script.yy.o
	gcc main.o script.yy.o $(OBJ) $(LIB) -ll -lm -o gifscr

fullCenter: $(OBJ) fullCenter.o
	gcc fullCenter.o $(OBJ) $(LIB) -lm -o fullCenter

script.yy.c : script.l
	lex -t script.l > script.yy.c

clean:
	rm *.o script.yy.c

image.o:
	gcc -c image.c

readim.o:
	gcc -I$(INCLUDE) -c readim.c


