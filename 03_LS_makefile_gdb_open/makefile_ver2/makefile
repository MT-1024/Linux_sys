src = $(wildcard *.c) #fun1.c fun2.c main.c sum.c
obj = $(patsubst %.c , %.o ,$(src)) #fun1.o fun2.o main.o sum.o
ALL : a.out

a.out : $(obj)
	gcc $^ -o $@ 

%.o : %.c
	gcc $< -o $@ 

clean :
	-rm -rf a.out

.PHONY : clean ALL
