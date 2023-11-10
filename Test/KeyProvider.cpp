#include "KeyProvider.h"

// Initialize key provider. [10]
// aKeyword is a string of letters.
KeyProvider::KeyProvider(const std::string& aKeyword)
{
    //call the initialize function, initializes the KeyProvider object using aKeyword argument.
    initialize(aKeyword);
}

// Destructor, release resources. [4]
KeyProvider::~KeyProvider()
{}

// Initialize (or reset) keyword [30]
void KeyProvider::initialize(const std::string& aKeyword)
{
    //Assign the length of the Keyword to variable fSize.
    fSize = aKeyword.length();
    //Creates an array of character with a size of fSize and assign to fKeyword.
    fKeyword = new char[fSize];
    //Initialize the Index to 0. This variable is used to track the current keyword index.
    fIndex = 0;

    //Loop that iterates over each character in the aKeyword.
    for (size_t i = 0; i < fSize; i++)
    {
        //converts the character to uppercase.
        fKeyword[i] = toupper(aKeyword[i]);
    }
}

// Dereference, returns current keyword character. [4]
char KeyProvider::operator*() const
{
    //Returns the character in the current index in the fKeyword array.
    return fKeyword[fIndex];
}

// Push new keyword character. [18]
// aKeyCharacter is a letter (isalpha() is true).
// aKeyCharacter replaces current keyword character.
// Key provider advances to next keyword character.
KeyProvider& KeyProvider::operator<<(char aKeyCharacter)
{
    //check if aKeyCharacter is an alphabet char.
    if (isalpha(aKeyCharacter))
    {
        //Converts aKeyCharacter to uppercase.
        fKeyword[fIndex] = toupper(aKeyCharacter);
        //Updates the fIndex value to the next index.
        //The modulo wraps the array to the first index if the index reaches the fSize value.
        fIndex = (fIndex + 1) % fSize;
    }
    //Returns a reference to the current KeyProvider object.
    return *this;
}