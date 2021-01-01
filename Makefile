default: final

final:
	cc main.c ./mongocon/con.c mygetline.c $(pkg-config --libs --cflags libmongoc-1.0)


#mon.o:
	#cc -c ./mongocon/con.c $(pkg-config --libs --cflags libmongoc-1.0)
