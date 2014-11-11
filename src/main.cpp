#include <iostream>
#include <opencv2/opencv.hpp>
#include "extractor.h"

using namespace std;
using namespace cv;

int main (int argc, const char * argv[]) {
    Extractor e = *new Extractor();
    e.extract();
}