WHERE		!= uname -m
HOST		!= hostname

OPENGL_LIBS+= -lGL -lGLU -lglut
COMMON_LIBS+= -lm


#Default path to bin, include and lib
DEFAULT_LIB_INSTALL_PATH= ../lib
DEFAULT_BIN_INSTALL_PATH= ../bin
LOCAL_INCLUDE_DIR= ../include
# Use variables set to default
# Change if need
INSTALL_BIN= $(DEFAULT_BIN_INSTALL_PATH)
INSTALL_LIB= $(DEFAULT_LIB_INSTALL_PATH)

DEBUGFLAG+= -g -Wall				# until under devolopment, show all warnnings and debug features
CPPFLAGS += --std=c++17 $(DEBUGFLAG) 
CFLAGS	+= $(DEBUGFLAG) 
INCLUDE_DIR+=	-I../include -I/usr/local/include -I/usr/include \
					-I. -I../../whitenoise \
					-I$(LOCAL_INCLUDE_DIR)
LIBS_DIR += -L/usr/lib -L. -L/usr/local/lib -L$(INSTALL_LIB)
SHARED_LDFLAGS=

INCLUDE_DEP=

SRC_LIB_NAME=
OBJ_LIB_NAME=
SRC_LIB_FILES=$(SRC_LIB_NAME)
OBJ_LIB_FILES=$(OBJ_LIB_NAME)


#
# All binaries files
#
BINS = jogo
SRC= desenha.c mouse.c movimentos.c objetos.c principal.c record.c teclado.c textura.c tragetoria.c 
OBJ= desenha.o mouse.o movimentos.o objetos.o principal.o record.o teclado.o textura.o tragetoria.o

			
DEPENDS = $(SRC)


RM_FILES=$(OBJ) $(BINS) $(INSTALL_BIN)/$(BINS)


.cpp.o:

	clang++ -o $@ -c $< $(INCLUDE_DIR) $(CPPFLAGS)

.c.o:

	clang -o $@ -c $< $(INCLUDE_DIR) $(CFLAGS)

all: $(BINS)

desenha.o: desenha.c

mouse.o: mouse.c

movimento.o: movimentos.c

objetos.o: objetos.c

principal.o: principal.c

record.o: record.c

teclado.o: teclado.c

textura.o: textura.c

tragetoria.o: tragetoria.c

jogo: $(OBJ)

	clang++ -o $@ $> $(CPPFLAGS)  $(INCLUDE_DIR)	$(INCLUDE_LIB) \
							$(LIBS_DIR) $(OPENGL_LIBS) $(COMMON_LIBS)
	@echo -n ">>> Installing BIN on "
	@echo $(INSTALL_BIN)
	@cp $@ $(INSTALL_BIN)
	

clean:

	@echo -n Cleaning ... 
	@- rm -rf $(RM_FILES) >> /dev/null
	@echo Done.


