# FUSE Extractor for Lego NDS/3DS games
This program extracts files from a FUSE file paired with a CSV to a specified extraction directory. Currently decompressing is not supported, therefore many files might be exported in a compressed format.\
This code was only tested with "Lego City Undercover: The Chase Begins", so if you run into any issues with other games feel free to open up an issue on Github.

## Build
To build the program navigate to the CMakeLists.txt in a terminal and run the commands `cmake -S . -B build` and `cmake --build build`. The binary should now be located in the build directory.

## Run
To run the program use this syntax `PROGRAM path_to_fib_file path_to_csv_file path_to_extraction_directory`. The extraction directory path must end with a slash(/)!
