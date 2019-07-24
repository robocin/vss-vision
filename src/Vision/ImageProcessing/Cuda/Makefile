lut_compile:
	nvcc -c LUT/lut_kernel.cu \
     -o ../../../lut_kernel.o \
     -Wno-deprecated-gpu-targets

#lut_copy:
	#cp lut_kernel.o ../../../lut_kernel.o
	
clean:
	rm ../../../lut_kernel.o 
	rm ../../../VSSL

lut: clean lut_compile #lut_copy
#lut_generate_static

#-I /usr/include/opencv \
     #-L /usr/lib \
     `#pkg-config --cflags --libs opencv` \
