#ifndef __irf_project__extractor__
#define __irf_project__extractor__

#include <opencv2/opencv.hpp>
#include <iostream>
#include <regex>
#include <fstream>
#include "pictogram_identifier.h"

using namespace std;
using namespace cv;

class Extractor{
private:
    Mat drawn_picto_area;
    Mat printed_picto_area;
    string input_folder;
    string output_folder;
    string template_folder;
    string current_file;
    int number_of_squares_found;
    int success_cpt;
    
public:
    Extractor(string input_f, string output_f, string template_f);
    vector<Point>  findSquares(string filename);
    vector<vector<int>> generateGrid(vector<Point> found_squares, int precision);
    void extractFromFile(string filename);
};

#endif