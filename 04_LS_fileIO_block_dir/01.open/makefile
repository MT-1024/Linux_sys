src = $(wildcard *.c)
target = $(patsubst %.c,%, $(src))

ALL : $(target)

%:%.c
	gcc $< -o $@
clean:
	-rm -rf $(target)
	-rm -rf test.log
.PHONY : clean ALL
