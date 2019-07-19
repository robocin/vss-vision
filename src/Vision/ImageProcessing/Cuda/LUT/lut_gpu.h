#include "Utils.h"
int initGPU(uint size);
void releaseGPU();
int makeLUTGPU(uint size);
int getLUTFromGPU(uchar *c, uint size);
int setLUTToGPU(uchar *c, uint size);
void applyLUTGPU(uchar *c, uint size);
