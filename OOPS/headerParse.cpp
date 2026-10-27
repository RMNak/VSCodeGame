//c++
#include <string>
#include <iostream>
bool findStr()
{
    std::string str = "X-Notes-Item: $FILE/Image.1674806513313.png?OpenElement&EmbedImg=1&1674806513313; name=h_ImageURL";
    std::string delimiter = "EmbedImg=1";
    size_t pos = str.find(delimiter) + delimiter.length() + 1;
    if (pos != std::string::npos) {
        auto size = str.find(";", pos) - pos;
        std::string token = str.substr(pos,  size);
        std::cout << token << std::endl;
        return true;
    }
    return false;
}
int main()
{
    findStr();
    return 0;
}