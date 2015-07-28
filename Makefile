#Makefile
ROOT_PWD=.#$(shell pwd)
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
FLAGS=#-D_DEBUG_#-g
LDFLAGS=#-static
LINK=-lpthread -ljson_linux-gcc-4.6_libmt -lncurses

INCLUDE=-I$(COMM) -I$(SERVER) -I$(CLIENT) -I$(WINDOW) -I$(DATA_POOL)
LIB_PATH=-L$(LIB)

SRC=$(COMM)/*.cpp $(SERVER)/*.cpp $(CLIENT)/*.cpp $(WINDOW)/*.cpp $(DATA_POOL)/*.cpp

CLI_OBJ=udp_client.o util.o data_pool.o udp_data.o udp_json.o window.o
SER_OBJ=udp_server.o util.o data_pool.o udp_data.o udp_json.o window.o

all:$(CHAT_CLI) $(CHAT_SER)
.PHONY:all

$(CHAT_CLI):$(CLI_OBJ)
	$(CC) -o $@ $^ $(INCLUDE) $(LINK) $(FLAGS)
$(CHAT_SER):$(SER_OBJ)
	$(CC) -o $@ $^ $(INCLUDE) $(LINK) $(FLAGS)
%.o:$(COMM)/%.cpp
	$(CC) -c $< $(INCLUDE) $(LINK) $(FLAGS)
%.o:$(SERVER)/%.cpp 
	$(CC) -c $< $(INCLUDE) $(LINK)
%.o:$(CLIENT)/%.cpp
	$(CC) -c $< $(INCLUDE) $(LINK)
%.o:$(WINDOW)/%.cpp
	$(CC) -c $< $(INCLUDE) $(LINK)
%.o:$(DATA_POOL)/%.cpp
	$(CC) -c $< $(INCLUDE) $(LINK)

.PHONY:clean
clean:
	rm $(CHAT_SER) $(CHAT_CLI) *.o
