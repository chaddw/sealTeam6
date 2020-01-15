#compiler used
CC = g++

#compiler flag
CFLAGS = -Wall 

#Core and Libraries object files needed
LIBOBJS= lapi.o lcode.o lctype.o ldebug.o ldo.o ldump.o \
	lfunc.o lgc.o llex.o lmem.o lobject.o lopcodes.o lparser.o \
	lstate.o lstring.o ltable.o ltm.o lundump.o lvm.o lzio.o \
	lauxlib.o lbaselib.o lbitlib.o lcorolib.o ldblib.o liolib.o \
	lmathlib.o loadlib.o loslib.o lstrlib.o ltablib.o lutf8lib.o \
	linit.o

#creates object files when they are needed
%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

#creates Lua library, Lua compiler, & Lua interpreter
all: liblua.a lua luac

#creates Lua library
liblua.a: $(LIBOBJS)
	ar rs liblua.a $(LIBOBJS)

#creates Lua interpreter
lua: lua.o
	$(CC) lua.o  liblua.a -o lua

#creates Lua compiler
luac: luac.o
	$(CC) luac.o liblua.a -o luac

#removes all created files
clean:
	rm *.o lua luac liblua.a
