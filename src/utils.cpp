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
        // If we had a problem closing the folder, say it
        if (closedir(dir) == -1)
            cout << "Unable to close directory" << endl;
    }
    
    /**
     * \brief   Retrieve the names of files contained in a specific folder
     * \param   path    The complete path of the folder
     *  \return A vector containing the names of the files
     */
    vector<string> getFilenamesFromFolder(string path){
        // Init result
        vector<string> res;
        
        DIR* dir = openDir(path);
        struct dirent* readFile = NULL;
        
        // Parsing filenames
        while ((readFile = readdir(dir)) != NULL){
            if(!regex_match(readFile->d_name, hiddenFileRegex))
                res.push_back(readFile->d_name);
        }
        
        closeDir(dir);
        
        return res;
    }
}