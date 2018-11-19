.SUFFIXES: .pb .pbtxt .c .o .pb-c.c .pb-c.h .proto .c .o

PROTO_HDR = $(addsuffix .pb-c.h,$(basename $(wildcard tensorflow/core/framework/*.proto)))
PROTO_OBJ = $(addsuffix .pb-c.o,$(basename $(wildcard tensorflow/core/framework/*.proto)))

all: tf-test ops.pbtxt parse tpl

tf-test: tf-test.o
	gcc -o $@ $< -ltensorflow

ops: ops.o
	gcc -o $@ ops.o -ltensorflow

parse: parse.o $(PROTO_OBJ)
	gcc -o $@ parse.o $(PROTO_OBJ) -ltensorflow -lprotobuf-c

tpl: tpl.o
	gcc -o $@ $< -lneo_utl -lneo_cs

ops.pbtxt: ops.pb
	protoc-c tensorflow/core/framework/op_def.proto --decode=tensorflow.OpList < $< > $@

ops.pb: ops
	./ops > $@

.c.o:
	gcc -c -I. -I/usr/include/ClearSilver -o $@ $<

%.pb-c.c %.pb-c.h: %.proto
	protoc-c $< --c_out=.

clean:
	rm -f *.pbtxt *.pb *.o ops tf-test tensorflow/core/framework/*.pb-c.*

parse.o: $(PROTO_HDR)
