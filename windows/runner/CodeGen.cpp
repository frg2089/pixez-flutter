#include "CodeGen.h"

unsigned char *CodeGen::Random(int size)
{
    unsigned char *arr = new unsigned char[size]; // 创建一个 n个元素的数组

    srand(unsigned int(time(NULL))); // 随机种子
    for (int i = 0; i < size; i++)
        arr[i] = rand() % (255 - 0 + 1) + 0;
    return arr;
}

std::string CodeGen::getCodeVer()
{
    unsigned char *byteArray = CodeGen::Random(32);
    return base64_encode(byteArray, 32, true);
}

std::string CodeGen::getCodeChallenge(std::string code)
{
    SHA256 sha;
    sha.update(code);
    uint8_t *digest = sha.digest();
    std::string str = SHA256::toString(digest);
    delete[] digest;
    return base64_encode(str, true);
}