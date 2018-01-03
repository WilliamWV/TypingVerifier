#include "similarityanalizer.h"

/**
    Class Constructor
    SimilarityAnalizer::SimilarityAnalizer(string referenceFile)
    @brief construct the class with an optional reference to a
    file that will be used as a dictionary with one words per line
    @param referenceFile: path of the dictionary file

*/
SimilarityAnalizer::SimilarityAnalizer(string referenceFile)
{
    this->referenceWords.clear();

    this->referencesReady = this->readReferenceFile(referenceFile);
    if(this->referencesReady)
        this->refFileName = referenceFile;
}

/**
    int SimilarityAnalizer::stringDistance(string s1, string s2){
    @brief calculates the levenshtein distance with the well-known
    dynamic programming algorithm
    @param s1: first string
    @param s2: second string
    @return distance of the strings that represents the number of
    changes (insertion, deletion or alteration) to transform one
    string on the other

*/
int SimilarityAnalizer::stringDistance(string s1, string s2){
    int s1Size = s1.size();
    int s2Size = s2.size();


    int dist[s2Size+1][s1Size + 1];
    for(int i = 0; i< s1Size + 1; i++)
        dist[0][i] = i;
    for(int j = 1; j< s2Size + 1; j++)
        dist[j][0] = j;

    for(int j = 1; j<s2Size + 1; j++)
    {
        for(int i = 1; i<s1Size + 1; i++)
        {
            int currentChars = s1[i-1] == s2[j-1]? 0:1;
            dist[j][i] = min( dist[j][i-1] + 1,min(dist[j-1][i] + 1, dist[j-1][i-1] + currentChars));
        }
    }

    return dist[s2Size][s1Size];

}

/**
    vector<string> SimilarityAnalizer::closestStrings(string src, unsigned int minReturnedStr)
    @brief based on the reference dictionary returns the closest words based
    on the distance calculated by the function stringDistance of this class
    @param src: string to compare with reference
    @param minReturnedStr: minimum number of returned strings, that is the nth closest
    strings, the number of returned strings may be greater because if there is more words
    with the same distace all are returned
    @returns vector of the closest strings sorted from more closest to less closest
*/
vector<string> SimilarityAnalizer::closestStrings(string src, unsigned int minReturnedStr)
{

    if(this->referenceWords.size()<minReturnedStr)
    {
        minReturnedStr = this->referenceWords.size();
    }

    map<int, vector<string>> distances = this->sortedDistances(src);
    vector<string> answer;
    int currentDistance = 0;
    unsigned int wordsAdded = 0;
    while(wordsAdded<minReturnedStr)
    {
        try{
            vector<string> currentWords = distances[currentDistance];
            for(vector<string>::iterator str= currentWords.begin();
                str!= currentWords.end(); ++str)
            {
                answer.push_back(*str);
            }

            wordsAdded+=currentWords.size();

        }
        catch(exception ex)
        {
            currentDistance++;
        }

    }

    return answer;
}

/**
    vector<string> SimilarityAnalizer::closestThan(string src, unsigned int threshold)
    @brief return a vector with the reference words which distances
    from reference string is at most the value of threshold, the
    vector is sorted ascendingly based on distance
    @param src: source string
    @param threshold: maximum accepted distance
    @returns vector with these reference strings
*/

vector<string> SimilarityAnalizer::closestThan(string src, int threshold)
{
    if(threshold<0)
        threshold = 0;
    map<int, vector<string>> distances = this->sortedDistances(src);
    vector<string> answer;
    for(int i = 0; i<=threshold; i++)
    {
        try{
            answer.insert(
                        std::end(answer),
                        std::begin(distances[i]),
                        std::end(distances[i]));
        }catch(exception ex)
        {
            //do nothing
        }
    }
    return answer;
}
/**
    void SimilarityAnalizer::changeReferenceFile(string referenceFile)
    @brief change the reference file
    @param referenceFile: path to the new reference file
*/
void SimilarityAnalizer::changeReferenceFile(string referenceFile)
{
    vector<string> backup = this->referenceWords;
    if(this->readReferenceFile(referenceFile) == false)
    {
        cout<<"Failed to change reference, changing back to previous reference"<<endl;
        this->referenceWords = backup;
    }else
    {
        this->refFileName = referenceFile;
    }

}

/**
    bool SimilarityAnalizer::containsReferenceTo(string src)
    @brief check if there is reference to some string
    @param string to verify if there is reference
    @returns true if exists reference, false otherwise

*/
bool SimilarityAnalizer::containsReferenceTo(string src)
{
    for (vector<string>::iterator it= this->referenceWords.begin();
         it!= this->referenceWords.end(); ++it)
    {
        if(src.compare(*it) == 0)
            return true;
    }
    return false;
}


/**
    bool SimilarityAnalizer::readReferenceFile(string refFile)
    @brief read the file passed as reference and construct the
    reference vector
    @param refFile: path of the file to read
    @returns true if it was sucessful, false otherwise
*/
bool SimilarityAnalizer::readReferenceFile(string refFile)
{
    try{
        ifstream inputDict;

        inputDict.open(refFile);
        string word;
        while(inputDict>>word)
        {
            this->referenceWords.push_back(word);
        }
        inputDict.close();
        return true;
    }
    catch(exception ex)
    {
        cout<<"failed to read reference file";
        return false;
    }
}
/**
    map<int, vector<string>> SimilarityAnalizer::sortedDistances()
    @brief generates a map with distance integers associated
    with a vector of words from reference that have rhis distance
    from the source string
    @param src: string to compare with words from reference
    @returns a map associatting distance with reference words

*/
map<int, vector<string>> SimilarityAnalizer::sortedDistances(string src)
{
    map<int, vector<string>> distances;
    for (vector<string>::iterator str= this->referenceWords.begin();
         str!= this->referenceWords.end(); ++str)
    {
        int currentDist = this->stringDistance(src, *str);

        try
        {
            distances[currentDist].push_back(*str);
        }
        catch(exception ex)
        {
            vector<string> initializer;
            initializer.push_back(*str);
            distances[currentDist] = initializer;
        }
    }
    return distances;
}

/**
    string SimilarityAnalizer::getRefFileName()
    @brief used to get the file name, by now is used
    by class Verifier to add a word to the dictionary
    when requested
    @returns string with the name of the reference file
*/
string SimilarityAnalizer::getRefFileName()
{
    return this->refFileName;
}
