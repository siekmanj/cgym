CC=gcc

# The below variables may need to change depending on your mujoco install location.
MJDIR=$(HOME)/.mujoco/mujoco200_linux
MJLIB=-lmujoco200 -lGL -lglew $(MJDIR)/bin/libglfw.so.3
MJINC=-I$(MJDIR)/include -L$(MJDIR)/bin
MJKEY=$(MJDIR)/mjkey.txt


SRC=mj_env/*.c #cassie_env/*.c
INC=-I./include -I ./mj_env/ $(MJINC)
LIB=$(MJLIB)

libout:
	$(CC) -shared -o libcgym.so -fPIC $(SRC) $(INC) -DMJKEYPATH=$(MJKEY) $(LIB)
