#include <filesystem>
#include "ProcessInfo.h"
#include "bussdownrolly.h"

bool Start(ProcessInfo processInfo, const std::filesystem::path& filePath)
{
    Shtreeba shtreeba(processInfo, filePath);
    shtreeba.inject();
    return EXIT_SUCCESS;
}