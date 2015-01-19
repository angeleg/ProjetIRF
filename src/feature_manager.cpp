#include "feature_manager.h"

/**
 * \brief   Constructor
 * \param   db_f    Database input folder
 * \param   arff_f  ARFF output folder
 */
FeatureManager::FeatureManager(string db_f, string arff_f) {
    this->db_folder = db_f;
    this->arff_folder = arff_f;
}

/**
 * \brief   Generic method allowing to find the first non white pixel starting from a border of a
 *          grayscaled pictogram
 * \param   grayscaled_pictogram     The grayscaled pictogram from which we want to find the border
 * \param   parse_from_zero         Determining the way of parsing (increase or decrease)
 * \param   parse_by_row            Determining if we parse the file horizontally or vertically
 * \return  The number of the first row or column were we encountered a non white pixel
 */
int findFirstPixel(Mat grayscaled_pictogram, bool parse_from_zero, bool parse_by_row) {
    
    uchar THRESHOLD = 220;
    
    int i;
    int j;
    int bigBound;
    int littleBound;
    
    // Set boundaries
    if(parse_by_row) {
        bigBound = grayscaled_pictogram.rows;
        littleBound = grayscaled_pictogram.cols;
    }
    else {
        bigBound = grayscaled_pictogram.cols;
        littleBound = grayscaled_pictogram.rows;
    }
    
    // Init counters
    if(parse_from_zero) {
        i = 0;
        j = 0;
    }
    
    else {
        i = bigBound - 1;
        j = littleBound - 1;
    }
    
    // Parse image
    while( (parse_from_zero && i < bigBound) || (!parse_from_zero && i > 0) ) {
        
        // Detect first non white pixel
        if(parse_by_row && grayscaled_pictogram.at<uchar>(i,j) < THRESHOLD)
            break;
        else if(!parse_by_row && grayscaled_pictogram.at<uchar>(j,i) < THRESHOLD)
            break;
        
        // Increase counter
        if(parse_from_zero) {
            if( ((j+1) % littleBound) == 0 ) {
                j = 0;
                i++;
            }
            else
                j++;
        }
        // Decrease counter
        else {
            if(j-1 == 0) {
                j = littleBound - 1;
                i--;
            }
            else
                j--;
        }
    }
    
    return i;
}

/**
 * \brief   Find the borders of the drawn pictogram
 * \param   grayscaled_pictogram     The grayscaled pictogram from which we want to find the borders
 * \return  The rectangle representing the region containing the data
 */
Rect FeatureManager::computeDrawingBorders(Mat grayscaled_pictogram) {
    
    int leftBorder = findFirstPixel(grayscaled_pictogram, true, false);
    int topBorder = findFirstPixel(grayscaled_pictogram, true, true);
    int rightBorder = findFirstPixel(grayscaled_pictogram, false, false);
    int bottomBorder = findFirstPixel(grayscaled_pictogram, false, true);
    
    std::cout << leftBorder << ", " << topBorder << ", " << rightBorder << ", " << bottomBorder << std::endl;
    Rect roi = Rect(leftBorder, topBorder, rightBorder - leftBorder, bottomBorder - topBorder);
    
    //imshow("", grayscaled_pictogram(roi));
    //waitKey();
    
    return roi;
}


void FeatureManager::writeArff(string output_file) {
    ofstream arff_file;
    arff_file.open(this->arff_folder + output_file);
    
    arff_file << "@RELATION PICTOGRAM_FEATURES\n\n";
    
    // Attributes
    arff_file << "@ATTRIBUTE surface NUMERIC\n";
    arff_file << "@ATTRIBUTE ratio NUMERIC\n";
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

        // Begin basic feature extraction
        Mat pictogram = imread(this->db_folder + filename, CV_LOAD_IMAGE_GRAYSCALE);
        Rect boundaries = computeDrawingBorders(pictogram);
        
        // attribute : surface
        arff_file << boundaries.width*boundaries.height << ",";
        
        // attribute : ratio
        arff_file << ((double)boundaries.height) / boundaries.width << ",";
        
        // attribute : class
        arff_file << label << "\n";
    }
    
}
