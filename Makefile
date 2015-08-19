all: clean build

build: netty.c
	gcc -o netty netty.c

debug: clean netty.c
	gcc -g -o netty netty.c

.PHONY: clean
clean:
	if [ -f netty ]; then rm netty; fi
	if [ -d netty.dSYM ]; then rm -rf *.dSYM; fi

