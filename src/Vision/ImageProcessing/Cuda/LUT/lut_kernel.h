#pragma once
#include "lut_gpu.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "Utils.h"
#include <stdio.h>


#ifdef __CUDACC__

#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)

#define CUDA_BLOCK_SIZE 512
//#define USE_DEVICE_CODE

#endif



const int nStreams = 8;



cudaError_t initCuda(unsigned int size);
//cudaError_t addWithCuda(int *c, const int *a, const int *b, unsigned int size);
cudaError_t makeLUTWithCuda(unsigned int size);
cudaError_t getLUTFromGPUCUDA(uchar *c, unsigned int size);
cudaError_t setLUTtoGPUCUDA(uchar *c, unsigned int size);
//cudaError_t LUTWithCuda(uchar *c, uchar *a, unsigned int size);
cudaError_t releaseCuda(cudaError_t cudaStatus = cudaSuccess);
