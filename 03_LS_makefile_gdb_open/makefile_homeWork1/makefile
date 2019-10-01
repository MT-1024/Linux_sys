src = $(wildcard ./src/*.c) #fun1.c fun2.c main.c sum.c
obj = $(patsubst ./src/%.c, ./obj/%.o,$(src)) #fun1.o fun2.o main.o sum.o

inc_path=./inc

ALL:a.out

a.out : $(obj)
	gcc $^ -o $@ -I $(inc_path) 

./obj/%.o : ./src/%.c
	gcc -c $< -o $@ -I $(inc_path) 

clean :
	-rm -rf a.out $(obj)

.PHONY : clean ALL
