#include <assert.h>
#include <stdio.h>
#include <tensorflow/c/c_api.h>

#define CHECK(status) \
if (TF_GetCode(status) != TF_OK) { \
  printf("Error: %s\n", TF_Message(status)); \
  assert(TF_GetCode(status) == TF_OK); \
};


int main() {
  printf("Hello from TensorFlow C library version %s\n", TF_Version());
  TF_Status *status = TF_NewStatus();
  TF_Graph *graph = TF_NewGraph();
  TF_OperationDescription *desc = TF_NewOperation(graph, "Placeholder", "x");
  TF_SetAttrType(desc, "dtype", TF_FLOAT);
  TF_Operation *op = TF_FinishOperation(desc, status);
  CHECK(status);

  TF_Output input;
  input.oper = op;
  input.index = 0;

  TF_OperationDescription *desc2 = TF_NewOperation(graph, "Identity", "id");
  TF_AddInput(desc2, input);
  TF_Operation *id = TF_FinishOperation(desc2, status);
  CHECK(status);

  TF_SessionOptions *opts = TF_NewSessionOptions();
  TF_Session *session = TF_NewSession(graph, opts, status);
  CHECK(status);

  TF_Output out;
  out.oper = id;
  out.index = 0;

  TF_Tensor *output;

  TF_Tensor *input_value = TF_AllocateTensor(TF_FLOAT, NULL, 0, 4);
  ((float *)TF_TensorData(input_value))[0] = 3.0;

  TF_SessionRun(session, NULL, &input, &input_value, 1, &out, &output, 1, NULL, 0, NULL, status);
  CHECK(status);

  printf("Result %f\n", *(float *)TF_TensorData(output));

  TF_DeleteTensor(input_value);
  TF_DeleteTensor(output);
  TF_DeleteSessionOptions(opts);
  TF_DeleteSession(session, status);
  CHECK(status);
  TF_DeleteGraph(graph);
  TF_DeleteStatus(status);
  return 0;
}
