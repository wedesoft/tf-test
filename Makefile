.SUFFIXES: .pb .pbtxt .c .o

all: tf-test ops.pbtxt

ops.pbtxt: ops.pb
	protoc-c tensorflow/core/framework/op_def.proto --decode=tensorflow.OpList < $< > $@

ops.pb: ops
	./ops > $@

tf-test: tf-test.o
	gcc -o $@ $< -ltensorflow

ops: ops.o
	gcc -o $@ $< -ltensorflow

.c.o:
	gcc -c -o $@ $<
