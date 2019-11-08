src = $(wildcard *.c)
target = $(patsubst %.c,%,$(src))
inc_path = /usr/include/mysql/
lib_path = /usr/lib/x86_64-linux-gnu/

all : $(target)
%:%.c
	gcc $< -I$(inc_path) -L$(lib_path) -lmysqlclient
clean:
	-rm -rf a.out 
.PHONY: all clean
