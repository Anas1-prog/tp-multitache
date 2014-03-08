RM = rm
ECHO = echo
COMP = g++
EDL = g++
EXE = Parking
CPPFLAGS = -Wall
EDLFLAGS = 
LIBS = 
LIBPATH = -L/home/keke/Repo/tp-multitache/tp-multitache
INCPATH = -I/home/keke/Repo/tp-multitache/tp-multitache
CLEAN = efface
RMFLAGS = -f

LIBNAMEOPT = -ltp -lncurses -ltcl

INT = Mere.h Clavier.h Entree.h Util.h Sortie.h
REAL = $(INT: .h = .cpp)
OBJ = $(INT:.h=.o)

.PHONY : $(CLEAN)

$(EXE) : $(OBJ)
	$(ECHO) EDL de $(EXE)
	$(EDL) -o $(EXE) $(OBJ) $(LIBPATH) $(LIBNAMEOPT) $(INCPATH)
	
%.o : %.cpp
	$(ECHO) compilation $<
	$(COMP) $(CPPFLAGS) $(INCPATH) -c $<

efface :
	$(ECHO) Nettoyage
	rm -f *.o $(EXE) core
