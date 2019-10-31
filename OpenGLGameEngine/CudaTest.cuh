#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

int CudaStart();
cudaError_t addWithCuda(int* c, const int* a, const int* b, unsigned int size);