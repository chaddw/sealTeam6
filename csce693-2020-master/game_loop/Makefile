
#
include ../makedefs

PGM = game_loop

OBJS = \
	main.o \
	Game.o

all: $(PGM)

$(PGM): $(OBJS)
	$(CXX) -Wall -Wextra -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f $(PGM)
