RM = rm
ECHO = echo
COMP = g++
EDL = g++
EXE = Parking
CPPFLAGS = -Wall
EDLFLAGS = 
LIBS = 
LIBPATH = -L/shares/public/tp/tp-multitache
INCPATH = -I/shares/public/tp/tp-multitache
CLEAN = efface
RMFLAGS = -f

LIBNAMEOPT = -ltp -lncurses -ltcl

INT = Mere.h Clavier.h Entree.h
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
