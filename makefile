all: check

quine: quine.c
	$(CC) quine.c -o quine

check: quine
	@ ./quine | diff - quine.c && echo 'All is right'
