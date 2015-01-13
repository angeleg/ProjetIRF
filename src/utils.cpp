#include "utils.h"

namespace utils {
    
    // Usefull to ignore hidden files
    regex hiddenFileRegex("^[.].*");
    
    /**
     * \brief   Opens a directory
     * \param   path The directory path
     * \return  A pointer to the directory
     */
    DIR* openDir(string path) {
        // Try to open directory
        DIR* dir = NULL;

        dir = opendir(path.c_str());
        
        // If the folder has'nt been opened, say it
        if (dir == NULL)
            cout << "Unable to open directory : " << path << endl;
        
        return dir;
    }
    
    /**
     * \brief   Closes a directory
     * \param   dir The directory to close
     */
    void closeDir(DIR* dir) {
        if (closedir(dir) == -1)
            cout << "Unable to close directory" << endl;
    }
    
    /**
     * \brief   Retrieve the names of files contained in a specific folder
     * \param   path    The complete path of the folder
     *  \return A vector containing the names of the files
     */
    vector<string> getFilenamesFromFolder(string path, string unwanted) {
        // Init result
        vector<string> res;
        
        DIR* dir = openDir(path);
        struct dirent* readFile = NULL;
        
        // Parsing filenames
        while ((readFile = readdir(dir)) != NULL){
            if(!regex_match(readFile->d_name, hiddenFileRegex) && (readFile->d_name != unwanted) )
                res.push_back(readFile->d_name);
        }
        
        closeDir(dir);
        
        return res;
    }
    
    /**
     * \brief   Writes extracted pictogram description file on disk
     * \param   output_name The name of the file to write
     * \param   label       The label recognized by the program
     * \param   scripter    The scripter from the sheet
     * \param   page        The page number
     * \param   i           The row number in the sheet
     * \param   j           The column number in the sheet
     */
    void writeDescriptionFile(string output_name, string label, string scripter, string page , int i, int j) {
        ofstream descriptionFile;
        
        descriptionFile.open(output_name + ".txt");
        descriptionFile << "# Team members: Berthier, Géraud, Le Goff\n";
        descriptionFile << "label " << label << "\n";
        descriptionFile << "form " << scripter << page << "\n";
        descriptionFile << "scripter " << scripter << "\n";
        descriptionFile << "page " << page << "\n";
        descriptionFile << "row " << i << "\n";
        descriptionFile << "column " << j << "\n";
        
        descriptionFile.close();
    }
}