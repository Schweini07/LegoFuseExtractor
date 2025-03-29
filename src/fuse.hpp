#include <string>
#include <vector>
#include <cstdint>

struct file
{
    uint32_t crc;
    std::string name;
    uint32_t compressed_size;
    uint32_t size;
    uint32_t offset;
};

class FuseExtractor
{
public:
    FuseExtractor(std::string csv_path, std::string fib_path, std::string extraction_directory_path);
    ~FuseExtractor() = default;

    int Extract();

private:
    int RetrieveCSVInfo(std::vector<file> & csv_data);
    int ExtractFiles(const std::vector<file> & csv_data);

    std::string csv_path;
    std::string fib_path;
    std::string extraction_directory_path;
};