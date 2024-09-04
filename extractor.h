#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include <string>

class ISOExtractor
{
public:
    bool extractISO(const std::string &isoPath, const std::string &outputFolderPath);
};

#endif // EXTRACTOR_H