#pragma once

enum genNames	{GEN_F0, GEN_F1, GEN_NR};
enum genSignals {GEN_SIN, GEN_COS};

void genSetFreq(int genNumber, double freqHz);
void genGetValue(float* outBuffer, int16_t blockSize, int genNumber, int signalType);
void genInit(int genNumber);


