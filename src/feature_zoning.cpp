#include "feature.h"

const int ZONES_ROWS = 4;
const int ZONES_COLS = 3;

/**
 * \brief   Computes the gravity center by zone
 * \param   img     The image we want to process
 * \return  A vector containing the gravity center coordinates for
 *          each zone (the image is parsed horizontally first then vertically)
 */
vector<Point> FeatureManager::getZonesGravityCenters(Mat img) {
    vector<Point> res;
    
    int i = 0;
    int j = 0;
    
    int zone_width = img.cols / ZONES_COLS;
    int zone_height = img.rows / ZONES_ROWS;
    
    while(i < ZONES_ROWS) {

        Rect zone_rect = Rect(j*zone_width, i*zone_height, zone_width, zone_height);
        res.push_back(this->getGravityCenter(img(zone_rect)));
        
        // Iterate
        if((j+1) % ZONES_COLS == 0) {
            j = 0;
            i++;
        }
        else
            j++;
    }
    return res;
}

/**
 * \brief   Computes the black percentage by zone
 * \param   img     The image we want to process
 * \return  A vector containing the black percentage for each zone
 *          (the image is parsed horizontally first then vertically)
 */
vector<double> FeatureManager::getZonesBlackPercentage(Mat img) {
    vector<double> res;
    
    int i = 0;
    int j = 0;
    
    int zone_width = img.cols / ZONES_COLS;
    int zone_height = img.rows / ZONES_ROWS;
    
    while(i < ZONES_ROWS) {
        
        Rect zone_rect = Rect(j*zone_width, i*zone_height, zone_width, zone_height);
        res.push_back(this->getBlackPercentage(img(zone_rect)));
        
        // Iterate
        if((j+1) % ZONES_COLS == 0) {
            j = 0;
            i++;
        }
        else
            j++;
    }
    return res;
}

/**
 * \brief   Writes the attributes for each zone's gravity center (x and y coordinates)
 * \param   f   The file where we want to write
 */
void FeatureManager::printZonesGravityCenterAttributes(ofstream &f) {
    for(int i=0; i < ZONES_ROWS; i++) {
        for(int j=0; j < ZONES_COLS; j++) {
            f << "@ATTRIBUTE zone_" << i << "_" << j << "_gravity_center_x NUMERIC" << endl;
            f << "@ATTRIBUTE zone_" << i << "_" << j << "_gravity_center_y NUMERIC" << endl;
        }
    }
}

/**
 * \brief   Writes the attributes for each zone's black percentage
 * \param   f   The file where we want to write
 */
void FeatureManager::printZonesBlackPercentageAttributes(ofstream &f) {
    for(int i=0; i < ZONES_ROWS; i++) {
        for(int j=0; j < ZONES_COLS; j++) {
            f << "@ATTRIBUTE zone_" << i << "_" << j << "_black_percentage NUMERIC" << endl;
        }
    }
}
