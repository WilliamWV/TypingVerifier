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
    vector<string> closestThan(string src, int threshold);
    void changeReferenceFile(string referenceFile);
    bool containsReferenceTo(string src);
    string getRefFileName();
private:
    vector<string> referenceWords;
    bool readReferenceFile(string refFile);
    map<int, vector<string>> sortedDistances(string src);
    bool referencesReady;
    string refFileName;
};

#endif // SIMILARITYANALIZER_H
