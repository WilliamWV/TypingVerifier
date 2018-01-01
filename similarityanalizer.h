#ifndef SIMILARITYANALIZER_H
#define SIMILARITYANALIZER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>

using namespace std;
class SimilarityAnalizer
{
public:

    SimilarityAnalizer(string referenceFile = NULL);
    int stringDistance(string s1, string s2);
    vector<string> closestStrings(string src, unsigned int minReturnedStr = 1);
    vector<string> closestThan(string src, unsigned int threshold);
    void changeReferenceFile(string referenceFile);
    bool containsReferenceTo(string src);
private:
    vector<string> referenceWords;
    bool readReferenceFile(string refFile);
    bool referencesReady;
};

#endif // SIMILARITYANALIZER_H
