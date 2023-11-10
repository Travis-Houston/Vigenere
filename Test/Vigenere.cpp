#include "Vigenere.h"

// Initialize Vigenere scrambler [8]
Vigenere::Vigenere(const std::string& aKeyword) : fKeyword(aKeyword), fKeywordProvider(aKeyword) {
    //calls the initializeTable function.
    initializeTable();
}

// Return the current keyword. [22]
// This method scans the keyword provider and copies the keyword characters
// into a result string.
std::string Vigenere::getCurrentKeyword() {
    //initialize an empty string that holds the result characters.
    std::string result;
    //create a temprary keyProvider object.
    KeyProvider tempProvider(fKeyword);
    //Loop that iterates through the characters of the keyword.
    for (size_t i = 0; i < fKeyword.size(); i++) {
        //Result = empty result + current keyword character.
        result += *tempProvider;
        //Advances the tempProvider object to the next character in the keyword.
        tempProvider << *tempProvider;
    }
    //returns the complete keyword
    return result;
}

// Reset Vigenere scrambler. [6]
// This method has to initialize the keyword provider.
void Vigenere::reset() {
    fKeywordProvider.initialize(fKeyword);
}

// Encode a character using the current keyword character and update keyword. [36]
char Vigenere::encode(char aCharacter)
{
    //Initialize encoding holder variable
    char result = aCharacter;
    //check if result is an alphabet char.
    if (isalpha(result))
    {
        //Converts aCharacter to uppercase.
        char aCharacter_upper = toupper(aCharacter);
        //retrieves the encoded character from the fMappingTable.
        //% 'A' operation is used to map the character's index to the corresponding position in the mapping table. 
        result = fMappingTable[*fKeywordProvider % 'A'][aCharacter_upper % 'A'];
        //Advances the fKeywordProvider object to the next character in the keyword.
        fKeywordProvider << aCharacter_upper;
        //check and convert to lowercase.
        if (islower(aCharacter)) result = tolower(result);
    }
    //returns the complete encoding.
    return result;
}

// Decode a character using the current keyword character and update keyword. [46]
char Vigenere::decode(char aCharacter)
{
    char result = aCharacter;
    if (isalpha(result))
    {
        char aCharacter_upper = toupper(aCharacter);
        //This line retrieves the decoded character from the fMappingTable.
        //(CHARACTERS - 2) - *fKeywordProvider % 'A' map the character's index to the corresponding position in the mapping table (remove header and footer). 
        result = fMappingTable[(CHARACTERS - 2) - *fKeywordProvider % 'A'][aCharacter_upper % 'A'];
        //Advances the fKeywordProvider object to the next character in the keyword.
        fKeywordProvider << result;
        //check and convert to lowercase.
        if (islower(aCharacter)) result = tolower(result);
    }
    return result;
} 

// Initialize the mapping table
// Row 1: B - A
// Row 26: A - Z
void Vigenere::initializeTable()
{
    for (char row = 0; row < CHARACTERS; row++)
    {
        char lChar = 'B' + row;
        for (char column = 0; column < CHARACTERS; column++)
        {
            if (lChar > 'Z')
            {
                lChar = 'A';
            }
            fMappingTable[row][column] = lChar++;
        }
    }
}