ALL : a.out

fun1.o : fun1.c
	gcc -c fun1.c
fun2.o : fun2.c
	gcc -c fun2.c
sum.o : sum.c
	gcc -c sum.c
main.o : main.c
	gcc -c main.c
a.out : fun1.o fun2.o sum.o main.o
	gcc fun1.o fun2.o sum.o main.o -o a.out
