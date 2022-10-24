
DEPS:=../lua-5.3.6/src
LIBS := -llua -lm -ldl

thread_a:=./thread/a/thread_a

$(thread_a): ./thread/a/main.c
	$(CC) -o $@ $^ -I$(DEPS) -L$(DEPS) $(LIBS)