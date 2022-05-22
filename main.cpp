#include "Arduino.h"
#include "tensorflow/lite/c/c_api_internal.h"
#include "tensorflow/lite/experimental/micro/micro_interpreter.h"
#include "tensorflow/lite/experimental/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "model_setting.h"
#include "model.h"
#include "image_provider.h"
#include "resolver.h"


namespace
{
  // Initialize model, interpreter and error_reporter and point them to null pointer
  // We will set these variables later
  const tflite::Model* model = nullptr;
  tflite::MicroInterpreter* interpreter = nullptr;
  tflite::ErrorReporter* error_reporter = nullptr;

  TfLiteTensor* input = nullptr; // This is where we will store our image before send it to interpreter

  // Memory space
  // For kTensorArenaSize, i allocate 150*1024 of memory space which is 153600
  // So, you have to make sure that your microcontroller can handle this !
  const int kTensorArenaSize = 150*1024;
  static uint8_t tensor_arena[kTensorArenaSize];

} // namespace initializeMainObj

void setup() {

    // Get MicroErrorReporter and assign its address to error_reporter
    static tflite::MicroErrorReporter static_micro;
    error_reporter = &static_micro;

    // Get model from model.h
    model = tflite::GetModel(tflite_model);

    // Initialize resolver and add ops to its
    // If there is some ops that missing, there will be some error when you run it
    // So you can add its by using the same structure as below
    static tflite::MicroMutableOpResolver resolver;
    resolver.AddBuiltin(tflite::BuiltinOperator_CONV_2D, tflite::ops::micro::Register_CONV_2D(),3,3);
    resolver.AddBuiltin(tflite::BuiltinOperator_DEPTHWISE_CONV_2D, tflite::ops::micro::Register_DEPTHWISE_CONV_2D(),3,3);
    resolver.AddBuiltin(tflite::BuiltinOperator_MAX_POOL_2D, tflite::ops::micro::Register_MAX_POOL_2D());
    resolver.AddBuiltin(tflite::BuiltinOperator_QUANTIZE, tflite::ops::micro::Register_QUANTIZE());
    resolver.AddBuiltin(tflite::BuiltinOperator_PADV2, tflite::ops::micro::Register_PADV2());
    
    // Create an Interpreter and allocate tensor_arena
    static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
    interpreter = &static_interpreter;

    // Allocate memory
    interpreter->AllocateTensors();

    // Grab input from interpreter
    input = interpreter->input(0);

}


void loop() {

    // Get image from our function
    GetDummyImage(input->data.uint8, kTotalImageFlattenSize);

    // Invoke our interpreter to run inference
    interpreter->Invoke();

    // Grab output from interpreter after invoking
    TfLiteTensor* output = interpreter->output(0);

    // Print out the output using Error_reporter
    error_reporter->Report("Output: %d", output);
}
