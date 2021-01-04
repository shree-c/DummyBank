default: final

final:
	cc main.c  mygetline.c ./mongocon/con.c -I/usr/local/include/libbson-1.0 -I/usr/local/include/libmongoc-1.0 -lmongoc-1.0 -lbson-1.0	


#mon.o:
	#cc -c ./mongocon/con.c $(pkg-config --libs --cflags libmongoc-1.0)
