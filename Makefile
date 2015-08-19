all: clean build

build: ip_formatter.c
	gcc -o ip_formatter ip_formatter.c

debug: clean ip_formatter.c
	gcc -g -o ip_formatter ip_formatter.c

.PHONY: clean
clean:
	if [ -f ip_formatter ]; then rm ip_formatter; fi
	if [ -d ip_formatter.dSYM ]; then rm -rf *.dSYM; fi

