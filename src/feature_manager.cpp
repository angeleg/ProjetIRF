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
