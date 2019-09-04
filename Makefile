CC=gcc

# The below variables may need to change depending on your mujoco install location.
MJDIR=$(HOME)/.mujoco/mujoco200_linux
MJLIB=-lmujoco200 -lGL -lglew $(MJDIR)/bin/libglfw.so.3
MJINC=-I$(MJDIR)/include -L$(MJDIR)/bin
MJKEY=$(MJDIR)/mjkey.txt


SRC=mj_env/*.c
INC=$(MJINC) -Iinclude -Imj_env/
LIB=$(MJLIB)

libout:
	echo $(INC)
	$(CC) -shared -o libcgym.so -fPIC $(SRC) $(INC) -DMJKEYPATH=$(MJKEY) $(LIB)
