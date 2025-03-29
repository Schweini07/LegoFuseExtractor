#include "fuse.hpp"

#include <iostream>

int main(int argc, char const **argv)
{
    if (argc < 4)
    {
        std::cout << "Not enough arguments. Use 'PROGRAM path_to_csv path_to_fib path_to_extraction_directory.\n\
path_to_extraction_directory needs to end with a /.\n";
        return 1;
    }

    FuseExtractor fuse(argv[1], argv[2], argv[3]);
    if (1 == fuse.Extract())
    {
        std::cout << "Exiting program.\n";
        return 1;
    }

    return 0;
}
