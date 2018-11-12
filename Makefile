.SUFFIXES: .pb .pbtxt .c .o .pb-c.c .pb-c.h .proto

PROTO = $(addsuffix .pb-c.o,$(basename $(wildcard tensorflow/core/framework/*.proto)))

all: tf-test ops.pbtxt tensorflow/core/framework/op_def.pb-c.c

ops.pbtxt: ops.pb
	protoc-c tensorflow/core/framework/op_def.proto --decode=tensorflow.OpList < $< > $@

ops.pb: ops
	./ops > $@

tf-test: tf-test.o
	gcc -o $@ $< -ltensorflow

ops: ops.o $(PROTO)
	gcc -o $@ ops.o $(PROTO) -ltensorflow -lprotobuf-c

.c.o:
	gcc -c -I. -o $@ $<

%.pb-c.c %.pb-c.h: %.proto
	protoc-c $< --c_out=.

clean:
	rm -f *.pbtxt *.pb *.o ops tf-test tensorflow/core/framework/*.pb-c.*

tensorflow/core/framework/op_def.pb-c.o: tensorflow/core/framework/op_def.pb-c.h
