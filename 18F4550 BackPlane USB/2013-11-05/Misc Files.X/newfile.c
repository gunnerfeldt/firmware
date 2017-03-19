#include <math.h>
unsigned char mfBank=11;
unsigned char mfBankQframe;
unsigned char mfBankIndex;


void main (void) {
    mfBankQframe=floor(mfBank);
    mfBankIndex=mfBank-mfBankQframe;
}