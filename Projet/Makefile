CFLAGS=-lgraph
CC=gcc 
OBJS=obj
EXE=Graphe


$(OBJS)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -o $@ -c $< $(CFLAGS)

all: $(OBJS)/Affichage.o $(OBJS)/Chargement.o $(OBJS)/Dij.o $(OBJS)/main.o
	gcc -o $(EXE) $(OBJS)/Affichage.o $(OBJS)/Chargement.o $(OBJS)/Dij.o $(OBJS)/main.o $(CFLAGS)
clean:
	rm $(OBJS)/*.o