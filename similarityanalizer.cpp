#include "similarityanalizer.h"

SimilarityAnalizer::SimilarityAnalizer(string referenceFile)
{
    this->referenceWords.clear();

    this->referencesReady = this->readReferenceFile(referenceFile);

}

int SimilarityAnalizer::stringDistance(string s1, string s2){
    int s1Size = s1.size();
    int s2Size = s2.size();


    int dist[s2Size + 1][s1Size + 1];

    for(int i = 0; i< s1Size + 1; i++)
        dist[0][i] = i;
    for(int j = 1; j< s2Size + 1; j++)
        dist[j][0] = j;

    for(int j = 1; j<s2Size + 1; j++)
    {
        for(int i = 1; i<s1Size + 1; i++)
        {
            int currentChars = s1[i-1] == s2[j-1]? 0:1;
            min(
                dist[j][i-1] + 1,
                min(dist[j-1][i] + 1,
                    dist[j-1][i-1] + currentChars));
        }
    }

    return dist[s2Size][s1Size];

}

vector<string> SimilarityAnalizer::closestStrings(string src, unsigned int minReturnedStr)
{

    if(this->referenceWords.size()<minReturnedStr)
    {
        minReturnedStr = this->referenceWords.size();
    }

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
void SimilarityAnalizer::changeReferenceFile(string referenceFile)
{
    vector<string> backup = this->referenceWords;
    if(this->readReferenceFile(referenceFile) == false)
    {
        cout<<"Failed to change reference, changing back to previous reference"<<endl;
        this->referenceWords = backup;
    }
}

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
