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
/**
    bool Phonetics::isVowelRound(int v)
    @brief Return true if is a rounded vowel
    @param v: vowel
    @returns true if is rounded vowel, false otherwise
*/
bool Phonetics::isVowelRound(int v)
{
    return(this->isBitOn(v, ROUNDED_VOWEL_BIT));
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

/**
    bool Phonetics::isPowerOf2(int src)
    @brief return true if the number is power of 2
    false otherwise
*/
bool Phonetics::isPowerOf2(int src)
{
    return (src != 0) && ((src & (src-1)) == 0);
}

/**
    bool Phonetics::isVoicedConsonant(int c)
    @brief determine if a consonant is voiced
    @param c : consonant
    @returns true: voiced; false: unvoiced
*/
bool Phonetics::isVoicedConsonant(int c)
{
    return (this->isBitOn(c, VOICED_CONS_BIT));
}

/**
    int Phonetics::getOpeningFromVowel(int v)
    @brief from the vowel representation gets the bits that represent
    the opening part
    @param v: vowel
    @returns representation of the type of opening of the passed vowel
*/
int Phonetics::getOpeningFromVowel(int v)
{
    int mask = this->build_AND_Mask(VOWEL_OPENING_START, VOWEL_OPENING_END);
    return v & mask;
}

/**
    int Phonetics::getSrcFromCons(int v)
    @brief from the vowel representation gets the bits that represent
    the vowel source
    @param v: vowel
    @returns representation of the vowel's source
*/
int Phonetics::getSrcFromVowel(int v)
{
    int mask = this->build_AND_Mask(VOWEL_SRC_START, VOWEL_SRC_END);
    return v & mask;
}

/**
    int Phonetics::getSoundTypeFromCons(int c)
    @brief from the consonant representation gets the bits that represent
    the sound source part
    @param c: consonant
    @returns representation of the sound source of the passed consonant
*/
int Phonetics::getSoundTypeFromCons(int c)
{
    int mask = this->build_AND_Mask(CONS_SOUNDGEN_START, CONS_SOUNDGEN_END);
    return c & mask;
}
/**
    int Phonetics::getObstructionFromCons(int c)
    @brief from the consonant representation gets the bits that represent
    the obstruction part
    @param c: consonant
    @returns representation of the type of obstruciton of the passed consonant
*/
int Phonetics::getObstructionFromCons(int c)
{
    int mask = this->build_AND_Mask(CONS_OBSTRUCTION_START, CONS_OBSTRUCTION_END);
    return c & mask;
}
/**
    int Phonetics::build_AND_Mask(unsigned int initBit, unsigned int finalBit)
    @brief build an AND mask putting 1 on specified positions
    @param initBit: first bit 1
    @param finalBit: last bit 1
    @returns the mask
*/
int Phonetics::build_AND_Mask(unsigned int initBit, unsigned int finalBit)
{
    int mask = 0;
    for(int i = initBit; i<=finalBit; i++)
    {
        mask+= (int) pow(2, i);
    }
    return mask;
}
