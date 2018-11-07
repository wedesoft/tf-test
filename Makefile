tf-test: tf-test.o
	gcc -o $@ $< -ltensorflow

.c.o:
	gcc -c -o $@ $<
