
#include "lut_kernel.h"

#ifdef __LINUX__
	#define __forceinline 
#endif

uchar *dev_a = 0;
uchar *dev_b = 0;
uchar *dev_c = 0;

cudaStream_t stream[nStreams];

//int main(){return 0;};

void releaseGPU() {
	releaseCuda();
};

int initGPU(uint size) {
	return (int) initCuda(size);
};

cudaError_t releaseCuda(cudaError_t cudaStatus) {
	for (int i = 0; i < nStreams; ++i) cudaStatus = cudaStreamDestroy(stream[i]);
	cudaFree(dev_c);
	cudaFree(dev_a);
	//cudaFree(dev_b);

	// cudaDeviceReset must be called before exiting in order for profiling and
	// tracing tools such as Nsight and Visual Profiler to show complete traces.
	cudaStatus = cudaDeviceReset();
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaDeviceReset failed!");
		return cudaStatus;
	}

	return cudaStatus;
}



__global__ void addKernel(int *c, const int *a, const int *b)
{
    int i = threadIdx.x;
    c[i] = a[i] + b[i];
}

#ifdef USE_DEVICE_CODE
__device__ __forceinline void device_LUT(uchar*c, uint size) {
	unsigned int i = __fmaf_rd(__fmaf_rd(blockIdx.x,blockDim.x,threadIdx.x),3,0);
	if (i >= size) return; // out of bounds
	// get color value
	unsigned int r = (i >> 16) & 0xFF;
	unsigned int g = (i >> 8) & 0xFF;
	unsigned int b = i & 0xFF;

	// make calculations
	c[i] = __fmaf_rd(r, 1, 100);
	c[i+1] = __fmaf_rd(g, 1, 100);
	c[i+2] = __fmaf_rd(b, 1, 100);
}
#endif

__global__ void applyLUTGPUKernel(uchar *dest, uchar *ori, uint size, uchar *LUT) {
	unsigned int i = (blockIdx.x*blockDim.x + threadIdx.x);
	if (i >= size) return; // out of bounds
	i *= 3;
	uint idx = (ori[i+2] << 16) | (ori[i + 1] << 8) | ori[i];
	dest[i] = (uchar)LUT[idx];
	dest[i+1] = (uchar)LUT[idx+1];
	dest[i+2] = (uchar)LUT[idx+2];
	/*

	dest[i] = min((uchar)ori[i]+100, 255);
	dest[i + 1] = min((uchar)ori[i+1], 255);
	dest[i + 2] = min((uchar)ori[i+2]+100, 255);
	*/
}

__global__ void makeLUTGPUKernel(uchar *c, uint size)
{

//RobôCIn
	/*unsigned int i = (blockIdx.x*blockDim.x + threadIdx.x);
	if (i >= size) return; // out of bounds
	// get color value
	uchar r = (i >> 16) & 0xFF;
	uchar g = (i >> 8) & 0xFF;
	uchar b = i & 0xFF;

	// make calculations
	color.y = (9798 * r + 19235 * g + 3736 * b) >> 15;
    color.u = (18514 * (b - color.y) >> 15) + 128;
    color.v = (23364 * (r - color.y) >> 15) + 128;

    index = r * 65536 + g * 256 + b;

	@todo: substitute the this->getColorLabel(color) call
	c[i] = this->getColorLabel(color);*/

//old
#ifdef USE_DEVICE_CODE
	//device_LUT(c, size);
	unsigned int i = __fmaf_rd(__fmaf_rd(blockIdx.x, blockDim.x, threadIdx.x), 3, 0);
	if (i >= size) return; // out of bounds
						   // get color value
	unsigned int r = (i >> 16) & 0xFF;
	unsigned int g = (i >> 8) & 0xFF;
	unsigned int b = i & 0xFF;

	// make calculations
	c[i] = __fmaf_rd(r, 1, 100);
	c[i + 1] = __fmaf_rd(g, 1, 100);
	c[i + 2] = __fmaf_rd(b, 1, 100);
#else
	unsigned int i = (blockIdx.x*blockDim.x + threadIdx.x);
	if (i >= size) return; // out of bounds
	// get color value
	uchar r = (i >> 16) & 0xFF;
	uchar g = (i >> 8) & 0xFF;
	uchar b = i & 0xFF;
	i *= 3;
	// make calculations
	c[i] = min((uchar)b,255);
	c[i+1] = min((uchar)g,255);
	c[i+2] = min((uchar)r+100,255);
#endif
}

int makeLUTGPU(uint lut_size)
{

    // create LUT with CUDA
    cudaError_t cudaStatus = makeLUTWithCuda(lut_size);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "makeLUTWithCuda failed!");
        return 1;
    }


    return 0;
}

cudaError_t initCuda(unsigned int size) {
	cudaError_t cudaStatus;
	// Choose which GPU to run on, change this on a multi-GPU system.
	cudaStatus = cudaSetDevice(0);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
		goto Error;
	}

	// Allocate GPU buffers for three vectors (two input, one output)    .
	cudaStatus = cudaMalloc((void**)&dev_c, size * sizeof(uchar) * 3);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMalloc failed!");
		goto Error;
	}

	cudaStatus = cudaMalloc((void**)&dev_a, size * sizeof(uchar) * 3);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMalloc failed!");
		goto Error;
	}

	//cudaStatus = cudaMalloc((void**)&dev_b, size * sizeof(int));


	for (int i = 0; i < nStreams; ++i) {
		cudaStatus = cudaStreamCreate(&stream[i]);
		//cudaStreamCreateWithFlags(&stream[i], cudaStreamNonBlocking);
	}
		
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMalloc failed!");
		goto Error;
	}
	return cudaStatus;
Error:
	return releaseCuda(cudaStatus);
}

// Helper function for using CUDA to make LUT in parallel.
cudaError_t makeLUTWithCuda(uint size)
{

	cudaError_t cudaStatus;

	uint blockSize = CUDA_BLOCK_SIZE;
	uint gridSize = (size + blockSize-1) / blockSize;
	//gridSize = min(gridSize, 100);
	//fprintf(stderr,"grid, block %u %u\n", gridSize, blockSize);
	// Launch a kernel on the GPU with one thread for each element.
	makeLUTGPUKernel <<< gridSize, blockSize >>>(dev_c, size);

	// Check for any errors launching the kernel
	cudaStatus = cudaGetLastError();
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "makeLUTGPUKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
		goto Error;
	}

	// cudaDeviceSynchronize waits for the kernel to finish, and returns
	// any errors encountered during the launch.
	cudaStatus = cudaDeviceSynchronize();
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
		goto Error;
	}

	return cudaStatus;
Error:
	return releaseCuda(cudaStatus);
}



// Helper function for using CUDA to make LUT in parallel.
cudaError_t applyLUTWithCuda(uchar *c, uint size)
{

	cudaError_t cudaStatus;

	cudaMemcpy(dev_a, c, size*3, cudaMemcpyHostToDevice);
	/*cudaStatus = cudaDeviceSynchronize();
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "memcpy failed: %s\n", cudaGetErrorString(cudaStatus));
		goto Error;
	}*/
	uint blockSize = CUDA_BLOCK_SIZE;
	uint gridSize = (size + blockSize - 1) / blockSize;
	//gridSize = min(gridSize, 100);
	//fprintf(stderr, "grid, block %u %u\n", gridSize, blockSize);
	// Launch a kernel on the GPU with one thread for each element.
	applyLUTGPUKernel << < gridSize, blockSize >> >(dev_a, dev_a, size, dev_c);

	// Check for any errors launching the kernel
	cudaStatus = cudaGetLastError();
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "applyLUTGPUKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
		goto Error;
	}
	
	// cudaDeviceSynchronize waits for the kernel to finish, and returns
	// any errors encountered during the launch.
	/*cudaStatus = cudaDeviceSynchronize();
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
		goto Error;
	}*/
	cudaMemcpy(c, dev_a, size * 3, cudaMemcpyDeviceToHost);
	cudaStatus = cudaDeviceSynchronize();
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "memcpy failed: %s\n", cudaGetErrorString(cudaStatus));
		goto Error;
	}

	return cudaStatus;
Error:
	return releaseCuda(cudaStatus);
}

void applyLUTGPU(uchar *c, uint size) {
	applyLUTWithCuda(c, size);
}

cudaError_t getLUTFromGPUCUDA(uchar *c, uint size) {
	cudaError_t cudaStatus;
	// Copy output vector from GPU buffer to host memory.
	cudaStatus = cudaMemcpy(c, dev_c, size * sizeof(uchar), cudaMemcpyDeviceToHost);
	//cudaStatus = cudaMemcpyAsync(c, dev_c, size * sizeof(uchar), cudaMemcpyDeviceToHost);
	/*int streamSize = (size) / nStreams;
	for (int i = 0; i < nStreams; ++i) {
		uint offset = i * streamSize;
		uint streamBytes = max(size - offset, 0);
		cudaMemcpyAsync(c+offset, dev_c+offset, streamBytes, cudaMemcpyDeviceToHost, stream[i]);
	}

	for (int i = 0; i < nStreams; ++i) {
		cudaStreamSynchronize(stream[i]);
	}*/

	cudaStatus = cudaDeviceSynchronize();

	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMemcpy failed!");
	}
	return cudaStatus;
}

int getLUTFromGPU(uchar *c, uint size) {
	if (getLUTFromGPUCUDA(c, size) != cudaSuccess) return 1;
	return 0;
}

cudaError_t setLUTToGPUCUDA(uchar *c, uint size) {
	cudaError_t cudaStatus;
	// Copy output vector from host memory to GPU buffer.
	cudaStatus = cudaMemcpy(dev_c,c , size * sizeof(uchar), cudaMemcpyHostToDevice);
	//cudaStatus = cudaMemcpyAsync(dev_c, c, size * sizeof(uchar), cudaMemcpyHostToDevice);
	/*int streamSize = (size) / nStreams;
	for (int i = 0; i < nStreams; ++i) {
		uint offset = i * streamSize;
		uint streamBytes = max(size - offset, 0);
		cudaMemcpyAsync(dev_c+offset, c+offset, streamBytes, cudaMemcpyHostToDevice, stream[i]);
	}

	for (int i = 0; i < nStreams; ++i) {
		cudaStreamSynchronize(stream[i]);
	}*/

	cudaStatus = cudaDeviceSynchronize();

	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMemcpy failed!");
	}
	return cudaStatus;
}

int setLUTToGPU(uchar *c, uint size) {
	if (setLUTToGPUCUDA(c, size) != cudaSuccess) return 1;
	return 0;
}
//
//// Helper function for using CUDA to make LUT in parallel.
//cudaError_t LUTWithCuda(uchar *c, uchar *a, unsigned int size)
//{
//  
//	cudaError_t cudaStatus;
//
//    // Copy input vectors from host memory to GPU buffers.
//    cudaStatus = cudaMemcpy(dev_a, a, size * sizeof(uchar)*3, cudaMemcpyHostToDevice);
//    if (cudaStatus != cudaSuccess) {
//        fprintf(stderr, "cudaMemcpy failed!");
//        goto Error;
//    }
//
//    // Launch a kernel on the GPU with one thread for each element.
//    //addKernel<<<1, size>>>(dev_c, dev_a, dev_b);
//
//    // Check for any errors launching the kernel
//    cudaStatus = cudaGetLastError();
//    if (cudaStatus != cudaSuccess) {
//        fprintf(stderr, "addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
//        goto Error;
//    }
//    
//    // cudaDeviceSynchronize waits for the kernel to finish, and returns
//    // any errors encountered during the launch.
//    cudaStatus = cudaDeviceSynchronize();
//    if (cudaStatus != cudaSuccess) {
//        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
//        goto Error;
//    }
//
//    // Copy output vector from GPU buffer to host memory.
//    cudaStatus = cudaMemcpy(c, dev_c, size * sizeof(uchar)*3, cudaMemcpyDeviceToHost);
//    if (cudaStatus != cudaSuccess) {
//        fprintf(stderr, "cudaMemcpy failed!");
//        goto Error;
//    }
//    return cudaStatus;
//Error:
//	return releaseCuda(cudaStatus);
//}
