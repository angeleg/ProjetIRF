#include <iostream>
#include "extractor.h"

using namespace std;

int main (int argc, const char * argv[]) {
    Extractor e = *new Extractor();
    
    vector<cv::Point> points = e.findSquares();
        
    vector<vector<int>> v = e.generateGrid(points, 10);
    
    cout << "Rows v-position" << endl;
    
    for(int i=0; i<v[0].size(); i++){
        cout << v[0][i] << endl;
    }
    
    cout << "Columns h-position" << endl;
    
    for(int i=0; i<v[1].size(); i++){
        cout << v[1][i] << endl;
    }
    
}