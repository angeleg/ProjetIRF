#include "feature_manager.h"

FeatureManager::FeatureManager(string db_f, string arff_f) {
    this->db_folder = db_f;
    this->arff_folder = arff_f;
}


// TODO : load in grayscale
Rect FeatureManager::computeDrawingBorders(Mat pictogram) {
    
    uchar THRESHOLD = 220;
    int rows = pictogram.rows;
    int cols = pictogram.cols;
    
    int leftBorder;
    int topBorder;
    int rightBorder;
    int bottomBorder;
    
    int i=0;
    int j=0;
    bool found = false;
    
    // Find left border
    while(!found && i < cols) {
        
        if(pictogram.at<uchar>(j,i) < THRESHOLD) {
            found = true;
            break;
        }
        
        // Iteration
        if( ((j+1) % rows) == 0 ) {
            j = 0;
            i++;
        }
        else {
            j++;
        }
    }
    
    leftBorder = i;
    
    // Find top border
    i=0;
    j=0;
    found=false;
    
    while(!found && i < rows) {
        
        if(pictogram.at<uchar>(i,j) < THRESHOLD) {
            found = true;
            break;
        }
        
        // Iteration
        if( ((j+1) % cols) == 0 ) {
            j = 0;
            i++;
        }
        else {
            j++;
        }
    }
    
    topBorder = i;
    
    // Find right border
    i = cols - 1;
    j = rows - 1;
    found=false;
    
    while(!found && i > 0) {
        
        if(pictogram.at<uchar>(j,i) < THRESHOLD) {
            found = true;
            break;
        }
        
        // Iteration
        if( (j-1) == 0 ) {
            j = rows - 1;
            i--;
        }
        else {
            j--;
        }
    }
    
    rightBorder = i;
    
    // Find bottom border
    i= rows - 1;
    j= cols - 1;
    found=false;
    
    while(!found && i > 0) {
        
        if(pictogram.at<uchar>(i,j) < THRESHOLD) {
            found = true;
            break;
        }
        
        // Iteration
        if(j-1 == 0) {
            j = cols - 1;
            i--;
        }
        else {
            j--;
        }
    }
    
    bottomBorder = i;
    
    std::cout << leftBorder << ", " << topBorder << ", " << rightBorder << ", " << bottomBorder << std::endl;
    
    Rect roi = Rect(leftBorder, topBorder, rightBorder - leftBorder, bottomBorder - topBorder);
    
    imshow("", pictogram(roi));
    waitKey();
    
    return roi;
}