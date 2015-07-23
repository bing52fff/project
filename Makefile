#Makefile
ROOT_PWD=$(shell pwd)
CHAT_CLI=udp_client
CHAT_SER=udp_serverd

COMM=$(ROOT_PWD)/comm
SERVER=$(ROOT_PWD)/server
CLIENT=$(ROOT_PWD)/client
WINDOW=$(ROOT_PWD)/window
DATA_POOL=$(ROOT_PWD)/data_pool
PLUG=$(ROOT_PWD)/plug
LIB=$(ROOT_PWD)/lib

CC=g++
FLAGS=#-g
LDFLAGS=#-static

INCLUDE=-I$(COMM) -I$(SERVER) -I$(CLIENT) -I$(WINDOW) -I$(DATA_POOL) 
LIB_PATH=-L$(LIB)

CLI_OBJ=udp_client.o
SER_OBJ=udp_server.o

all:$(CHAT_CLI) $(CHAT_SER)
.PHONY:all

$(CHAT_CLI):$(CLI_OBJ)
	$(CC) -o $@ $^
$(CHAT_SER):$(SER_OBJ)
	$(CC) -o $@ $^
%.o:$(COMM)/%.cpp
	$(CC) -c $<
%.o:$(SERVER)/%.cpp
	$(CC) -c $<
%.o:$(CLIENT)/%.cpp
	$(CC) -c $<
%.o:$(WINDOW)/%.cpp
	$(CC) -c $<
%.o:$(DATA_POOL)/%.cpp
	$(CC) -c $<

.PHONY:clean
clean:
	rm $(CHAT_SER) $(CHAT_CLI) *.o
