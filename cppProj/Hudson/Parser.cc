#include "Parser.h"

#include <string>
#include <cstdio>

Parser::Parser(int date, const std::string &outputFilename)
{
}

void Parser::onUDPPacket(const char *buf, size_t len)
{
    printf("Received packet of size %zu\n", len);
}

