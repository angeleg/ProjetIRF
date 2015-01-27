#include "feature.h"

/**
 * \brief   Constructor
 * \param   db_f    Database input folder
 * \param   arff_f  ARFF output folder
 */
FeatureManager::FeatureManager(string db_f, string arff_f) {
    this->db_folder = db_f;
    this->arff_folder = arff_f;
}

Mat FeatureManager::normalize(Mat img, Rect cropping) {
    
    Mat img_crop = img(cropping);
    
    int max_side;
    if(img_crop.rows > img_crop.cols)
        max_side = img_crop.rows;
    else
        max_side = img_crop.cols;
    
    // Create a new white image
    Mat normalized(Size(max_side + 10, max_side + 10), CV_8U);
    normalized = Scalar(255);
    
    // Add padding to the image
    for(int i=5; i<max_side+5; i++) {
        for(int j=5; j<max_side+5; j++) {
            if(i-5 < img_crop.rows && j-5 < img_crop.cols)
                normalized.at<uchar>(i,j) = img_crop.at<uchar>(i-5,j-5);
        }
    }
    
    // Resize it
    Size size(250, 250);
    resize(normalized, normalized, size, INTER_CUBIC);
    
    return normalized;
}

/**
 * \brief   Computes features from each pictogram and exports the corresponding arff file
 * \param   output_file     The name of the arff file to output
 */
void FeatureManager::writeArff(string output_file) {
    
    ofstream arff_file;
    arff_file.open(this->arff_folder + output_file);
    arff_file << "@RELATION PICTOGRAM_FEATURES\n\n";
    
    // Attributes
    arff_file << "@ATTRIBUTE surface NUMERIC\n";
    arff_file << "@ATTRIBUTE ratio NUMERIC\n";
    arff_file << "@ATTRIBUTE diagonalAngle NUMERIC\n";
    this->printZonesGravityCenterAttributes(arff_file);
    
    arff_file << "@ATTRIBUTE blackPercentage NUMERIC\n";
    arff_file << "@ATTRIBUTE gravityCenterX NUMERIC\n";
    arff_file << "@ATTRIBUTE gravityCenterY NUMERIC\n";
    
    arff_file << "@ATTRIBUTE class {accident,bomb,car,casualty,electricity,fire,firebrigade,flood,gas,injury,paramedics,person,police,roadblock}\n";
    
    // Data
    arff_file << "\n@DATA\n";
    vector<string> filenames = utils::getFilenamesFromFolder(this->db_folder, "");
    regex fileRegex("([a-z]+)_[0-9]+_[0-9]+_[0-9]_[0-9].([a-z]*)");
    match_results<string::const_iterator> resultFile;
    
    for(int i=0; i < filenames.size(); i++) {
        string filename = filenames[i];
        
        // Get infos from filename
        if(!regex_match(filename, resultFile, fileRegex))
            continue;
        
        string label = resultFile[1];
        string extension = resultFile[2];
        
        // Skip .txt files
        if(extension.compare("txt") == 0)
           continue;
        
        cout << "Starting processing file : " << filename << endl;

        // Begin metrics feature extraction
        Mat pictogram = imread(this->db_folder + filename, CV_LOAD_IMAGE_GRAYSCALE);
        Rect boundaries = computeDrawingBorders(pictogram);
        
        // Skip blank pictograms
        if(boundaries.width <= 0 || boundaries.height <= 0) {
            cout << "%%%%% Ignored file because of blank pictogram : " << filename << "%%%%%" << endl;
            continue;
        }
        
        Mat cropped_pictogram = pictogram(boundaries);
        
        // @ATTRIBUTE surface
        arff_file << boundaries.width*boundaries.height << ",";
        
        // @ATTRIBUTE ratio
        arff_file << ((double)boundaries.height) / boundaries.width << ",";
        
        // @ATTRIBUTE diagonalAngle
        arff_file << atan(((double)boundaries.width) / boundaries.height) << ",";
        
        vector<Point> gravityCenters = this->getZonesGravityCenters(cropped_pictogram);
        
        // @ATTRIBUTES ZONE_i_j_GRAVITY_CENTER_X/Y NUMERIC
        for(int i=0; i < gravityCenters.size(); i++) {
            arff_file << gravityCenters[i].x << "," << gravityCenters[i].y << ",";
        }
        
        
        // %%%%% NORMALIZATION %%%%%
        Mat normalized_pictogram = this->normalize(pictogram, boundaries);
        
        // @ATTRIBUTE blackPercentage
        arff_file << this->getBlackPercentage(normalized_pictogram) << ",";
        
        Point gravity_center = getGravityCenter(normalized_pictogram);
        
        // @ATTRIBUTE gravityCenterX
        arff_file << gravity_center.x << ",";
        
        // @ATTRIBUTE gravityCenterY
        arff_file << gravity_center.y << ",";
        
        // @ATTRIBUTE class
        arff_file << label << "\n";
    }
    
    arff_file.close();
    
}
