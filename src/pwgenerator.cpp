#include <cstdlib>
#include <iostream>
#include <openssl/rand.h>
#include <pwgenerator.h>

Generator::Generator()
{
    this->charset = Generator::ALPHABETIC;
}

Generator::~Generator()
{
    // nothing to do
}

std::string Generator::generatePassword(int length)
{
    std::string charset;
    if (this->charset == Generator::ALPHANUMERIC)
    {
        charset = Generator::charset_numeric + Generator::charset_alphabetic;
    }
    else if (this->charset == Generator::ALPHANUMERIC_WITH_SYMBOLS)
    {
        charset = Generator::charset_alphabetic + Generator::charset_numeric +
                  Generator::charset_symbols;
    }
    else
    {
        charset = Generator::charset_alphabetic;
    }
    std::string password = "";
    for (int i = 0; i < length; i++)
    {
        // get a random number
        // isn't there a os.random() function for this purpose with quantum
        // mechanics?
        // int random = ::random() % charset.length();
        unsigned char bytes[4];
        RAND_bytes(bytes, 4);
        int random =
            int((unsigned char)(bytes[0]) << 24 |
                (unsigned char)(bytes[1]) << 16 |
                (unsigned char)(bytes[2]) << 8 | (unsigned char)(bytes[3])) %
            charset.length();
        // index the string at the random numbers idx & add the char to our
        // password
        password += charset[random];
    }
    return password;
}

void Generator::setCharset(int charset)
{
    this->charset = charset;
}
