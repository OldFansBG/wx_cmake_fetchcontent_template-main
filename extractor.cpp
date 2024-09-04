#include "extractor.h"
#include <archive.h>
#include <archive_entry.h>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

bool ISOExtractor::extractISO(const std::string &isoPath, const std::string &outputFolderPath)
{
    struct archive *archive;
    struct archive_entry *entry;
    int result;

    // Create the output directory if it does not exist
    fs::create_directories(outputFolderPath);

    archive = archive_read_new();
    archive_read_support_format_iso9660(archive);

    if ((result = archive_read_open_filename(archive, isoPath.c_str(), 10240)))
    {
        std::cerr << "Could not open archive: " << archive_error_string(archive) << std::endl;
        return false;
    }

    while (archive_read_next_header(archive, &entry) == ARCHIVE_OK)
    {
        const char *currentFile = archive_entry_pathname(entry);
        std::string fullOutPath = outputFolderPath + "/" + currentFile;

        std::cout << "Extracting: " << fullOutPath << std::endl;

        archive_entry_set_pathname(entry, fullOutPath.c_str());

        if ((result = archive_read_extract(archive, entry,
                                           ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_TIME)) != ARCHIVE_OK)
        {
            std::cerr << "Extraction failed: " << archive_error_string(archive) << std::endl;
            archive_read_close(archive);
            archive_read_free(archive);
            return false;
        }
    }

    archive_read_close(archive);
    archive_read_free(archive);

    return true;
}