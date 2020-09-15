#pragma once
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include <string>

/*
Remember about:

    proper constructor that acquire a file
    proper destructor that release the file
    operator<< for displaying file content on the screen
    error handling

*/

class FileOpenError : public std::runtime_error {
public:
    FileOpenError(std::string fileName)
        : std::runtime_error{"File open failed" + fileName} {}
};

class FileHandler {
public:
    FileHandler(const std::string& fileName)
        : fp_{std::fopen(fileName.c_str(), "r")} {
        if (!fp_) {
            throw FileOpenError{fileName};
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const FileHandler& fh) {
        char c;                                    // note: int, not char, required to handle EOF
        while ((c = std::fgetc(fh.fp_)) != EOF) {  // standard C I/O file reading loop
            os << c;
        }

        if (std::ferror(fh.fp_)) {
            throw std::runtime_error("I/O error when reading");
        } else if (std::feof(fh.fp_)) {
            os << "End of file reached successfully\n";
        }

        return os;
    }

    ~FileHandler() {
        std::fclose(fp_);
    }

private:
    FILE* fp_;
};
