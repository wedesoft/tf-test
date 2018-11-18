#include <stdio.h>
#include <tensorflow/c/c_api.h>
#include "tensorflow/core/framework/op_def.pb-c.h"

int main(void)
{
  TF_Buffer *buffer = TF_GetAllOpList();
  Tensorflow__OpList *op_list = tensorflow__op_list__unpack(NULL, buffer->length, buffer->data);
  printf("unpacked %d operations\n", op_list->n_op);
  for (int i=0; i<op_list->n_op; i++) {
    struct _Tensorflow__OpDef *op = op_list->op[i];
    printf("* %s\n", op->name);
    for (int j=0; j<op->n_input_arg; j++) {
      Tensorflow__OpDef__ArgDef *arg = op->input_arg[j];
      printf("  * %s\n", arg->name);
    };
    for (int j=0; j<op->n_attr; j++) {
      Tensorflow__OpDef__AttrDef *attr = op->attr[j];
      printf("  - %s\n", attr->name);
    };
    for (int j=0; j<op->n_output_arg; j++) {
      Tensorflow__OpDef__ArgDef *arg = op->output_arg[j];
      printf(" -> %s\n", arg->name);
    };
  };
  tensorflow__op_list__free_unpacked(op_list, NULL);
  TF_DeleteBuffer(buffer);
  return 0;
}
