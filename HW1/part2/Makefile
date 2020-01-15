lua: lua.c
	g++ -c lua.c

luac: luac.c
	g++ -c luac.c

liblua: liblua.a
	g++ -c liblua.a

all: lua.c luac.c liblua.a
	g++ -c lua.c luac.c liblua.a

clean:
	rm *.o 
