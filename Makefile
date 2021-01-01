default: final

final: mon.o
	cc main.c ./mongocon/con.o $(pkg-config --libs --cflags libmongoc-1.0)


mon.o:
	cc -c ./mongocon/con.c $(pkg-config --libs --cflags libmongoc-1.0)
