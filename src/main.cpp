#include <iostream>
#include "extractor.h"

using namespace std;

int main (int argc, const char * argv[]) {
    
    Extractor e = *new Extractor();
    e.extractFromFile("s01_0001.png");
    
}