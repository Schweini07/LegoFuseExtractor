#include <iostream>
#include <fstream>

#include "fuse.hpp"
#include "util/FileSystemDirectoryHandler.hpp"

FuseExtractor::FuseExtractor(std::string csv_path, std::string fib_path, std::string extraction_directory_path)
: csv_path(csv_path), fib_path(fib_path), extraction_directory_path(extraction_directory_path)
{
}

int FuseExtractor::Extract()
{
    std::vector<file> csv_data;
    if (1 == RetrieveCSVInfo(csv_data))
    {
        std::cout << "Something went wrong while trying to retrieve the CSV data.\n";
        return 1;
    }

    if (1 == ExtractFiles(csv_data))
    {
        std::cout << "Something went wrong while trying to extract the files contained in the FIB.\n";
        return 1;
    }

    return 0;
}

int FuseExtractor::RetrieveCSVInfo(std::vector<file> & csv_data)
{
    std::ifstream csv_file(csv_path, std::ios::binary);
    if (!csv_file)
    {
        std::cout << "Could not open CSV file. Wrong path?\n";
        return 1;
    }

    std::string line;
    std::getline(csv_file, line); // Skip first line
    while (std::getline(csv_file, line))
    {
        file file_struct;

        int index = line.find(',');
        std::string test = line.substr(0, index);
        file_struct.crc = std::stoul(line.substr(0, index), nullptr, 16);
        index++;

        int previous_index = index;
        index = line.find(',', index);
        file_struct.name = line.substr(previous_index, index-previous_index);
        index++;

        previous_index = index;
        index = line.find(',', index);
        file_struct.compressed_size = std::stoul(line.substr(previous_index, index-previous_index));
        index++;

        previous_index = index;
        index = line.find(',', index);
        file_struct.size = std::stoul(line.substr(previous_index, index-previous_index));
        index++;

        previous_index = index;
        index = line.find(',', index);
        file_struct.offset = std::stoul(line.substr(previous_index, index-previous_index), nullptr, 16);
        index++;

        csv_data.push_back(file_struct);
    }

    csv_file.close();

    return 0;
}

int FuseExtractor::ExtractFiles(const std::vector<file> & csv_data)
{
    std::ifstream fib_file(fib_path, std::ios::binary);
    if (!fib_file.good())
    {
        std::cout << "Could not open FIB file. Wrong path?\n";
        return 1;
    }
    
    for (const file & file_info : csv_data)
    {
        fib_file.seekg(file_info.offset, std::ios::beg);

        std::string extraction_path = extraction_directory_path + file_info.name;
        FileSystemDirectoryHandler::CreateDirectory(extraction_path.c_str());

        std::ofstream extracted_file(extraction_path, std::ios::binary);

        std::vector<char> data_buffer(file_info.compressed_size);
        fib_file.read(data_buffer.data(), file_info.compressed_size);
        extracted_file.write(data_buffer.data(), file_info.compressed_size);
        
        extracted_file.close();
    }

    return 0;
}
