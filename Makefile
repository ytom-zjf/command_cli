CC := gcc
CCFLAG := 

TARGET_NAME := appliction

INC :=	-I ./ \
		-I ./inc \

SRC := 	main_appliction.c \
		./src/ring_buffer.c \
		./src/core_cli.c \
		./src/cli_cmd.c

default : all

.PHONY: all
all: 
	$(CC) $(CCFLAG) $(INC) $(SRC) -o $(TARGET_NAME)

.PHONY: debug
debug: 
	$(CC) $(CCFLAG) -g $(INC) $(SRC) -o $(TARGET_NAME)


.PHONY: clean
clean:
	rm  $(TARGET_NAME)
