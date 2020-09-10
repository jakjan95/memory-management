#pragma once
#include <fstream>
#include <string>

class FileHandler {
public:
    //fp_(fopen...) w liscie inicjalizacyjnej
    FileHandler(const std::string& fileName)
        : fileName_{fileName} {
            //wyjatek rzucamy :P
        file_.open(fileName_);
        //fp 
    }

    friend std::ostream& operator<<(std::ostream& os, FileHandler fh) {
        for (std::string line{}; std::getline(file_, line);) {
            os << line;
        }
        return os;
    }

    ~FileHandler(){
        //std::fclose(fp_);
    }

private:
    //FILE* fp_;
    std::string fileName_;
    std::ifstream file_;
};
