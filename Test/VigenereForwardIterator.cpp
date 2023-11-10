#include "VigenereForwardIterator.h"

VigenereForwardIterator::VigenereForwardIterator(iVigenereStream& aIStream)
    : fIStream(aIStream), fCurrentChar('\0'), fEOF(false)
{
    if (fIStream)
    {
        fIStream >> fCurrentChar;
        if (fIStream.eof())
        {
            fEOF = true;
        }
    }
}

char VigenereForwardIterator::operator*() const
{
    return fCurrentChar;
}

VigenereForwardIterator& VigenereForwardIterator::operator++()
{
    if (fIStream)
    {
        fIStream >> fCurrentChar;
        if (fIStream.eof())
        {
            fEOF = true;
        }
    }
    return *this;
}

VigenereForwardIterator VigenereForwardIterator::operator++(int)
{
    VigenereForwardIterator temp = *this;
    ++(*this);
    return temp;
}

bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const
{
    return fEOF == aOther.fEOF;
}

bool VigenereForwardIterator::operator!=(const VigenereForwardIterator& aOther) const
{
    return !(*this == aOther);
}

VigenereForwardIterator VigenereForwardIterator::begin() const
{
    return *this;
}

VigenereForwardIterator VigenereForwardIterator::end() const
{
    VigenereForwardIterator temp = *this;
    temp.fEOF = true;
    return temp;
}