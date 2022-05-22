#ifndef RESOLVER_HEADER_COVID_CHESTX
#define RESOLVER_HEADER_COVID_CHESTX

#include "tensorflow/lite/c/c_api_internal.h"

// Declare ops Register
namespace tflite
{
    namespace ops
    {
        namespace micro
        {
            TfLiteRegistration* Register_DEPTHWISE_CONV_2D();
            TfLiteRegistration* Register_CONV_2D();
            TfLiteRegistration* Register_MAX_POOL_2D();
            TfLiteRegistration* Register_QUANTIZE();
            TfLiteRegistration* Register_PADV2();
        }
    }
}

#endif