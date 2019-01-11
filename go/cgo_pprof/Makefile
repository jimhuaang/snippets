
compile: sigprof.go sigprof.c
	go build -buildmode=c-archive -o sigprof.a sigprof.go
	gcc -o sigprof sigprof.c sigprof.a -pthread


.DEFAULT_GOAL = compile

# Target name % means that this is a rule that matches anythings, @: is a recipe;
# the : means do nothing
%:
	@:

