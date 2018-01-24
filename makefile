CC = gcc
CFLAGS = -W -Wall -g
IFLAGS = -I include
IFLAGS2 = -I/usr/include/cairo
LFLAGS = -lcairo -lm -lX11
TAR = tar
MODE =

SOURCE = src
INCLUDE = include
BIN = bin
OBJET = obj

SRC = $(wildcard $(SOURCE)/*.c)
SRC_FILES1 := $(filter-out src/main.c, $(SRC))
SRC_FILES2 := $(filter-out src/main2.c, $(SRC))
OBJS= $(patsubst $(SOURCE)%.c,$(OBJET)%.o, $(SRC_FILES2))
OBJS_FILES := $(patsubst $(SOURCE)%.c,$(OBJET)%.o, $(SRC_FILES1))
INC = $(wildcard $(INCLUDE)/*.h)
AOUT = main
AOUT2 = main2



all:
ifeq ($(MODE),TEXTE)

	make main

else

	make main2

endif

main2 : $(OBJS_FILES)

	$(CC) $(CFLAGS) -o main $^ $(IFLAGS) $(LFLAGS)

$(OBJET)/%.o : $(SOURCE)/%.c

	$(CC) $(CFLAGS) $(IFLAGS) -c  $< -o $@ $(IFLAGS2) $(LFLAGS)

main : $(OBJS)

	$(CC) $(CFLAGS) -o $@ $^ $(IFLAGS) $(LFLAGS)

$(OBJET)/%.o : $(SOURCE)/%.c

	$(CC) $(CFLAGS) $(IFLAGS) -c  $< -o $@ $(IFLAGS2) $(LFLAGS)


##main : $(OBJET)/$(OBJS)
	##$(CC) $(CFLAGS) -o $(BIN)/$@ $^
	##move $@ $(BPATH)
##%.o : %.c
	##$(CC) $(CFLAGS) -o $@ -c $<
	##move $@ $(OPATH)

clean :
	 rm  obj/*.o
	 rm -rf html latex
cleaner : clean
	rm $(AOUT)

archive :
		$(TAR) -czvf game_of_life.tar.gz -c grilles Doxyfile bin obj $(SRC) $(INC) makefile
