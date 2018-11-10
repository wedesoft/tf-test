#include <stdio.h>
#include <tensorflow/c/c_api.h>

int main(void)
{
  TF_Buffer *buffer = TF_GetAllOpList();
  FILE *f = fopen("ops.pb", "w");
  fwrite(buffer->data, buffer->length, 1, f);
  fclose(f);
  TF_DeleteBuffer(buffer);
  return 0;
}
