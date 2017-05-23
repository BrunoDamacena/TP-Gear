CC=gcc
OPCOES_COMPILADOR=-I. -lglut -lGLU -lGLEW -lGL -lSOIL -lm -ISDL -lSDL_mixer `sdl-config --cflags --libs` 
TODOS_ARQUIVOS_PONTOH = model/props/props.h model/pista/pista.h
TODOS_ARQUIVOS_OBJ = TP-Gear.o model/props/props.o model/pista/pista.o

%.o: ../%.c $(TODOS_ARQUIVOS_PONTOH)
	$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	gcc -o TP-Gear.out $^ $(OPCOES_COMPILADOR)

run: all
	./TP-Gear.out

clean:
	rm *.o model/*/*.o *.out
