all: main

parser.o: remote/callback/parser.cpp
	g++ -c remote/callback/parser.cpp


execute.o: execute.cpp
	g++ -c execute.cpp

logger.o: logger.cpp
	g++ -c logger.cpp

exception.o: exception.cpp
	g++ -c exception.cpp

push_data.o: remote/callback/push_data.cpp
	g++ -c remote/callback/push_data.cpp

callback.o: remote/callback.cpp
	g++ -c remote/callback.cpp

operation_executer.o: remote/operation_executer.cpp
	g++ -c remote/operation_executer.cpp

operation.o: remote/operation.cpp
	g++ -c remote/operation.cpp

main.o: main.cpp
	g++ -c main.cpp

main: callback.o operation_executer.o operation.o main.o push_data.o exception.o logger.o execute.o parser.o
	g++ callback.o main.o operation_executer.o operation.o push_data.o  exception.o logger.o execute.o parser.o -o main

client: client2.cpp
	g++ client2.cpp -o client

clean:
	rm -rf *.o main

go_lwp_simple:
	go build lwp_simple.go

go_daemon:
	go build daemon.go

go: go_lwp_simple go_daemon
