// Desc: Contains the ProcessInfo struct
update the include 
#pragma once
#include <string>

struct ProcessInfo {
    const std::wstring processName;
    const unsigned long pid;
    const unsigned long tid;
};