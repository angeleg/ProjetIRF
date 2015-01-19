#include "feature.h"

/**
 * \brief   Get the proportion of black pixels in the image
 * \param   img     The image to analyze
 * \return  The percentage of black pixels
 */
double FeatureManager::getBlackPercentage(Mat img) {
    uchar THRESHOLD = 250;
    
    int black_cpt = 0;
    
    for (int i=0; i < img.rows; i++) {
        for(int j=0; j < img.cols; j++) {
            uchar pixel_value = (int)img.at<uchar>(i,j);
            if (pixel_value < THRESHOLD){
                black_cpt++;
            }
        }
    }
    return black_cpt*100/(img.rows * img.cols);
}

/**
 * \brief   Compute the position of the gravity center of the image
 * \param   img     The image to analyze
 * \return  The coordinates of the gravity center
 */
Point FeatureManager::getGravityCenter(Mat img) {
    uchar THRESHOLD = 250;
    
    Point res;
    int black_cpt = 0;
    
    for (int i = 0; i < img.rows ; i++){
        for (int j = 0; j < img.cols ; j++){
            uchar pixel_value = (int)img.at<uchar>(i,j);
            if (pixel_value < THRESHOLD){
                res.x += j;
                res.y += i;
                black_cpt++;
            }
        }
    }
    if(black_cpt > 0) {
        res.x = res.x / black_cpt;
        res.y = res.y / black_cpt;
    }
    return res;
}