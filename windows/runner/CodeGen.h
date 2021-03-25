#pragma once
#ifndef CODE_GEN_H_
#define CODE_GEN_H_

#include <time.h>

#include "base64.h"
#include "SHA256.h"

class CodeGen
{
private:
    static unsigned char *Random(int size);

public:
    static std::string getCodeVer();
    static std::string getCodeChallenge(std::string code);
};
#endif