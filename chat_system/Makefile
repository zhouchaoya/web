ROOT_PATH=$(shell pwd)
CLIENT_PATH=$(ROOT_PATH)/client
CONF_PATH=$(ROOT_PATH)/conf
SERVER_PATH=$(ROOT_PATH)/server
COMM_PATH=$(ROOT_PATH)/comm
LIB_PATH=$(ROOT_PATH)/lib
LOG_PATH=$(ROOT_PATH)/log
WINDOW_PATH=$(ROOT_PATH)/window
DATA_POOL_PATH=$(ROOT_PATH)/data_pool
CC=g++

INCLUDE_PATH=-I$(SERVER_PATH) -I$(DATA_POOL_PATH) -I$(LOG_PATH)
lib=-lpthread

SERVER_BIN=udpserver
CLIENT_BIN=udpclient

SERVER_SRC=$(shell ls $(SERVER_PATH) $(LOG_PATH) $(DATA_POOL_PATH) | egrep -v '^.*\.h' | egrep '.*\.cpp')
CLIENT_SRC=$(shell ls $(CLIENT_PATH) $(LOG_PATH) | egrep -v '^.*\.h' | egrep '.*\.cpp')

SERVER_OBJ=$(shell echo $(SERVER_SRC) | sed 's/\.cpp/\.o/g')
CLIENT_OBJ=$(shell echo $(CLIENT_SRC) | sed 's/\.cpp/\.o/g')

.PHONY:all
all:$(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN):$(SERVER_OBJ)
	@echo "Link [$^] to [$@] ..."
	g++ -o $@ $^ -lpthread
#	@$(CC) -o $@ $^ $(lib)
	@echo "Link done ..."
%.o:$(SERVER_PATH)/%.cpp
	@echo "Compling [$<] to [$@]"
	@$(CC) -c $< $(INCLUDE_PATH)
$(CLIENT_BIN):$(CLIENT_OBJ)
	@echo "Link [$^] to [$@] ..."
	@$(CC) -o $@ $^ $(lib)
	@echo "Link done ..."
%.o:$(CLIENT_PATH)/%.cpp
	@echo "Compling [$<] to [$@]"
	@$(CC) -c $< $(INCLUDE_PATH)

%.o:$(LOG_PATH)/%.cpp
	@echo "Compling [$<] to [$@]"
	@$(CC) -c $< $(INCLUDE_PATH)

%.o:$(DATA_POOL_PATH)/%.cpp
	@echo "Compling [$<] to [$@]"
	@$(CC) -c $< $(INCLUDE_PATH)

.PHONY:clean
clean:
	rm -f $(SERVER_BIN) $(CLIENT_BIN) *.o

.PHONY:debug
debug:
	echo $(SERVER_BIN)
	echo $(SERVER_OBJ)
	echo $(CLIENT_BIN)
	echo $(CLIENT_OBJ)
