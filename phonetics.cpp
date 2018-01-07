#include "phonetics.h"

Phonetics::Phonetics(string reference)
{

}

/**
    int Phonetics::phonemStringDistance(vector<int> w1, vector<int> w2)
    @brief Given two vectors of phonems returns the phonological distance
    between them
    @param w1, first vector of phonems
    @param w2, second vector of phonems

*/
int Phonetics::phonemStringDistance(vector<int> w1, vector<int> w2)
{
    int rawDistance = 0;
    int minSize = min(w1.size(), w2.size());
    int maxSize = max(w1.size(), w2.size());

    for(int i = 0; i<minSize; i++)
    {
        rawDistance += this->phonemsDistance(w1[i], w2[i]);
    }
    rawDistance += (MAX_DISTANCE* (maxSize - minSize));
    return this->normalizeDistance(maxSize, rawDistance);

}
/**
    int Phonetics::phonemStringDistance(string w1, string w2)
    @brief given two std::string return the phonetical distance
    between them.
    @param w1: first string
    @param w2: second string
    @returns distance between them
*/
int Phonetics::phonemStringDistance(QString w1, QString w2)
{
    return this->phonemStringDistance(
                Phonetics.phonemsFromString(w1),
                Phonetics.phonemsFromString(w2));
}

static Phonetics::vector<int> phonemsFromString(QString src)
{

}

/**
    int Phonetics::phonemsDistance (int f1, int f2)
    @brief given two phonems return the distance between them,
    depending if they are both vowels, both consonants or one
    vowel and one consonant
    @param f1 one phonem represented as one of the constants defined
    in this class definition
    @param another phonem
    @returns distance between the two phonems

*/
int Phonetics::phonemsDistance (int f1, int f2)
{
    if(f1 == f2)
        return 0;

    if(this->isVowel(f1) != this->isVowel(f2))
        return CONSONANT_VOWEL_DISTANCE;
    else{
        if(this->isVowel(f1))
            return this->vowelDistance(f1, f2);
        else
            return this->consonantDistance(f1, f2);
    }

}

/**
    bool Phonetics::isVowel(int s)
    @brief determine whether a phonem is a symbol following the
    representation explained in the class definition
    @param s: symbol to analise
    @returns true: is vowel, false otherwise
*/
bool Phonetics::isVowel(int s)
{
    return (this->isBitOn(s, VOWEL_BIT));
}

int Phonetics::vowelsSrcPositionDistance(int v1, int v2)
{

}
int Phonetics::vowelsOpeningDistance(int v1, int v2)
{

}
bool Phonetics::isVowelRound(int v)
{

}

int Phonetics::consonantSoundGenerationDist(int c1, int c2)
{

}
int Phonetics::consonantObstructionDist(int c1, int c2)
{

}

/**
    bool Phonetics::isBitOn(int src, unsigned int bit)
    @brief determine if a given bit of the integer value
    passed as first argument is 1
    @param src: integer variable whose bits will be checked
    @param bit: position of the desired bit
    @returns 1 = true if the bit is 1, 0 = false, otherwise
*/
bool Phonetics::isBitOn(int src, unsigned int bit)
{
    return (src & (1<<(bit)));
}


