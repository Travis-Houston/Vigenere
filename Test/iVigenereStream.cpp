#include "IVigenereStream.h"

iVigenereStream::iVigenereStream(Cipher aCipher, const std::string& aKeyword, const char* aFileName)
    : fCipher(aCipher), fCipherProvider(aKeyword)
{
    if (aFileName != nullptr)
        open(aFileName);
}

iVigenereStream::~iVigenereStream()
{
    close();
}

void iVigenereStream::open(const char* aFileName)
{
    close();
    fIStream.open(aFileName);
}

void iVigenereStream::close()
{
    if (fIStream.is_open())
        fIStream.close();
}

void iVigenereStream::reset()
{
    seekstart();
}

bool iVigenereStream::good() const
{
    return fIStream.good();
}

bool iVigenereStream::is_open() const
{
    return fIStream.is_open();
}

bool iVigenereStream::eof() const
{
    return fIStream.eof();
}

iVigenereStream& iVigenereStream::operator>>(char& aCharacter)
{
    if (fIStream)
    {
        char ch;
        fIStream.get(ch);
        if (fIStream)
        {
            auto lCallable = [](Vigenere& aCipherProvider, char aCharacter)
            {
                return aCipherProvider.decode(aCharacter);
            };
            aCharacter = fCipher(fCipherProvider, ch);
        }
    }
    return *this;
}