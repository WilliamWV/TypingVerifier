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
float Phonetics::phonemStringDistance(vector<int> w1, vector<int> w2)
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
float Phonetics::phonemStringDistance(QString w1, QString w2)
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
float Phonetics::phonemsDistance (int f1, int f2)
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

/**
    float Phonetics::vowelDistance(int v1, int v2)
    @brief controls te general behaviour of comparisions
    between vowels

    @param v1: fisrt vowel
    @param v2: second vowel
    @returns distance
*/
float Phonetics::vowelDistance(int v1, int v2)
{
    float srcDist = this->vowelsSrcPositionDistance(v1, v2);
    float openDist = this->vowelsOpeningDistance(v1, v2);
    float roundDist;
    if(this->isVowelRound(v1) == this->isVowelRound(v2))
        roundDist = 0;
    else
        roundDist = 1;

    return VOWEL_SRC_COEF * srcDist +
            VOWEL_OPEN_COEF * openDist +
            VOWEL_ROUND_COEF * roundDist;
}


/**
    float Phonetics::vowelsSrcPositionDistance(int v1, int v2)
    @brief based on the phonological human system source of the
    vowel sound determine a base distance from two IPA symbols
    based on this characteristic, the distance returned may be
    scaled by some coefficient to make sense

    @param v1: first vowel
    @param v2: second vowel
    @returns floating point value representing a base of the distance
*/
float Phonetics::vowelsSrcPositionDistance(int v1, int v2)
{
    float v1Src = this->bitAveragePos(
                    this->getSrcFromVowel(v1),
                    VOWEL_SRC_START,
                    VOWEL_SRC_END);
    float v2Src = this->bitAveragePos(
                    this->getSrcFromVowel(v2),
                    VOWEL_SRC_START,
                    VOWEL_SRC_END);

    if(v2Src == -1 || v1Src == -1)
        return MAX_DISTANCE;

    return abs(v1Src - v2Src);
}

/**
    float Phonetics::bitAveragePos(int src, int beg, int end)
    @brief determines the average position on the source integer
    of bits that are equals to one, this will be useful because
    a IPA symbol can have characteristics that blend various
    categories

    @param src: source integer to analize
    @param beg: initial bit to analize
    @param end: last bit to analize
    @returns average position of bits on 1
*/
float Phonetics::bitAveragePos(int src, unsigned int beg, unsigned int end)
{
    float sum = 0;
    int bitsOn1 = 0;
    for(int i = beg; i<=end; i++)
    {
        if(isBitOn(src, i)){
            sum+=i;
            bitsOn1++;
        }
    }

    if(bitsOn1>0){
        return sum/(float) bitsOn1;
    }
    else{
        return -1;
    }

}

/**
    float Phonetics::vowelsSrcPositionDistance(int v1, int v2)
    @brief based on the mouth opening to generate the vowel,
    determine a base distance from two IPA symbols, the distance
    returned may be scaled by some coefficient to make sense

    @param v1: first vowel
    @param v2: second vowel
    @returns floating point value representing a base of the distance
*/
float Phonetics::vowelsOpeningDistance(int v1, int v2)
{
    float v1Open = this->bitAveragePos(
                    this->getOpeningFromVowel(v1),
                    VOWEL_OPENING_START,
                    VOWEL_OPENING_END);
    float v2Open = this->bitAveragePos(
                    this->getOpeningFromVowel(v2),
                    VOWEL_OPENING_START,
                    VOWEL_OPENING_END);

    if(v2Open == -1 || v1Open == -1)
        return MAX_DISTANCE;

    return abs(v1Open - v2Open);
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

/**
    float Phonetics::consonantDistance(int c1, int c2)
    @brief controls te general behaviour of comparisions
    between consonants
    @param c1: first consonant
    @param c2: second consonant
    @returns distance
*/
float Phonetics::consonantDistance(int c1, int c2)
{
    float genDist = this->consonantSoundGenerationDist(c1, c2);
    float obsDist = this->consonantObstructionDist(c1, c2);
    float voicedDist;
    if(this->isVoicedConsonant(c1) == this->isVoicedConsonant(c2))
        voicedDist = 0;
    else
        voicedDist = 1;

    return CONS_GENTYPE_COEF * genDist +
            CONS_OBSTR_COEF * obsDist +
            CONS_VOICED_COEF * voicedDist;
}


/**
    float Phonetics::consonantSoundGenerationDist(int c1, int c2)
    @brief based on sound generation type, ex: nasal; of consonants
    determine an estimation of distance, once this is not a gradual
    change like vowels there are just three possible return values
    that represents no difference, some differences and everything
    different
    @param c1: first consonant
    @param c2: second consonant
    @return distance
*/
float Phonetics::consonantSoundGenerationDist(int c1, int c2)
{
    int c1Gen = this->getSoundTypeFromCons(c1);
    int c2Gen = this->getSoundTypeFromCons(c2);

    float distance;
    if(c1Gen == c2Gen){
        distance = 0;
    }
    else if(c1Gen & c2Gen){
        //there is common characteristics
        distance = 0.5;
    }
    else
        distance = 1;

    return distance;

}

/**
    float Phonetics::consonantSoundGenerationDist(int c1, int c2)
    @brief based on obstruction type, ex: dental; of consonants
    determine an estimation of distance, once this is not a gradual
    change like vowels there are just three possible return values
    that represents no difference, some differences and everything
    different, this is very similar to
    float Phonetics::consonantSoundGenerationDist(int c1, int c2)
    @param c1: first consonant
    @param c2: second consonant
    @return distance
*/
int Phonetics::consonantObstructionDist(int c1, int c2)
{
    int c1Obs = this->getObstructionFromCons(c1);
    int c2Obs = this->getObstructionFromCons(c2);

    float distance;
    if(c1Obs == c2Obs){
        distance = 0;
    }
    else if(c1Obs & c2Obs){
        //there is common characteristics
        distance = 0.5;
    }
    else
        distance = 1;

    return distance;
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
