all: tunit punit bunit bob 

tunit: trnslist.h trnslist.c tlist-test-unit.c
	gcc trnslist.c tlist-test-unit.c -o tunit

punit: puzzle.h puzzle.c puzzle-test-unit.c
	gcc puzzle.c puzzle-test-unit.c sha1.c -o punit

bunit: puzzle.h puzzle.c trnslist.h trnslist.c block.h block.c block-test-unit.c
	gcc puzzle.c trnslist.c block.c block-test-unit.c sha1.c -o bunit

bob: puzzle.h puzzle.c trnslist.h trnslist.c blockchain.c block.h block.c robtest.c
	gcc puzzle.c trnslist.c block.c blockchain.c robtest.c sha1.c -o bob

clean:
	@rm -f *.o tunit punit bunit bob