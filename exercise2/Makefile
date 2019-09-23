
all: taskA taskB taskC taskD

taskA:
	clang -lpthread taskA.c -o taskA

taskB:
	clang -lpthread -g -fsanitize=thread taskA.c -o taskA

taskC:
	clang -lpthread -g -fsanitize=thread taskC.c -o taskC

taskD: double_checked.c
	clang double_checked.c -o double_checked -std=gnu11 -g -O3 -lpthread && exec ./double_checked

taskE:
	clang double_checked.c -o double_checked -std=gnu11 -g -fsanitize=thread -O3 -lpthread && exec ./double_checked

taskF:
	clang -lpthread -g -fsanitize=thread dumb_philosophers.c -o dumb_philosophers
	./dumb_philosophers

taskF-fix:
	clang -lpthread -g -fsanitize=thread smart_philosophers.c -o smart_philosophers
	./smart_philosophers