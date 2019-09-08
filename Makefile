CC=gcc
INC=-Iinclude
ASSETS=$(shell pwd)/assets

MJDIR=$(HOME)/.mujoco/mujoco200_linux
MJKEY=$(MJDIR)/mjkey.txt
MJSRC=mj_env/*.c
MJINC=-I$(MJDIR)/include $(INC) -L$(MJDIR)/bin
MJLIB=-lmujoco200 -lGL -lglew $(MJDIR)/bin/libglfw.so.3

mj_envs: $(MJSRC)
	$(CC) -o libmjenvs.so -shared -fPIC $(MJSRC) $(MJINC) -DMJKEYPATH=$(MJKEY) -DMJASSETS=$(ASSETS) $(MJLIB)


CASSIEDIR=$(HOME)/cassie-mujoco-sim
CASSIESRC=cassie_env/*.c
CASSIEINC=-I$(CASSIEDIR)/include $(INC) $(MJINC)
CASSIELIB=-L$(CASSIEDIR) -lcassiemujoco

cassie_envs: $(CASSIESRC)
	$(CC) -o libcassieenvs.so -shared -fPIC $(CASSIESRC) $(CASSIEINC) -DMJKEYPATH=$(MJKEY) -DCASSIEASSETS=$(ASSETS) $(CASSIELIB) -Wl,-rpath=$(CASSIEDIR)

cassie_demo: demo/cassie_demo.c
	$(CC) -o test -Iinclude -I. -L. demo/cassie_demo.c -lcassieenvs

mj_demo: demo/mj_demo.c
	$(CC) -o test -Iinclude -I. -I$(MJDIR)/include -L. demo/mj_demo.c -lmjenvs

