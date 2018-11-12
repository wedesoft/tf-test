#include <stdio.h>
#include <tensorflow/c/c_api.h>
#include "tensorflow/core/framework/op_def.pb-c.h"

int main(void)
{
  TF_Buffer *buffer = TF_GetAllOpList();
  Tensorflow__OpList *op_list = tensorflow__op_list__unpack(NULL, buffer->length, buffer->data);
  printf("unpacked %d operations\n", op_list->n_op);
  for (int i=0; i<op_list->n_op; i++)
    printf("* %s\n", op_list->op[i]->name);
  tensorflow__op_list__free_unpacked(op_list, NULL);
  TF_DeleteBuffer(buffer);
  return 0;
}
