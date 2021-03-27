default: final
final:
	cc ./main.c ./mongocon/con.c ./mygetline.c ./ac_no_gen.c -I/usr/include/libbson-1.0 -I/usr/include/libmongoc-1.0 -lmongoc-1.0 -lbson-1.0
