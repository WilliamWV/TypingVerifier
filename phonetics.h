#ifndef PHONETICS_H
#define PHONETICS_H

#include <vector>
#include <string>
#include <cmath>

#include <QString>


/**
    Follow IPA definitions
*/

/**

    Bit usage definitions:

    31------------------------------------0
    xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx


    vowels: (bit 28 = 0)
        open: bit 0 = 1
        open_mid: bit 1 = 1
        close_mid: bit 2 = 1
        close: bit 3 = 1

        back: bit 4 = 1
        central: bit 5 = 1
        front: bit 6 = 1

        rounded: bit 7 = 1

    consonant : bit 28 = 1
        glotal: bit 0 = 1
        pharyngeal: bit 1 = 1
        uvular: bit 2 = 1
        velar: bit 3 = 1
        palatal: bit 4 = 1
        retroflec: bit 5 = 1
        post alveolar: bit 6 = 1
        alveolar: bit 7 = 1
        dental: bit 8 = 1
        labio_dental: bit 9 = 1
        bilabial: bit 10 = 1

        lateral_approximant: bit 11 = 1
        approximant: bit 12 = 1
        lateral_fricative: bit 13 = 1
        fricative: bit 14 = 1
        tal_flap: bit 15 = 1
        trill : bit 16 = 1
        nasal: bit 17 = 1
        plosive: bit 18 = 1

        voiced: bit 19 = 1
*/

#define VOWEL                       0x00000000
#define V_CLOSE                     0x00000008
#define V_CLOSE_MID                 0x00000004
#define V_OPEN_MID                  0x00000002
#define V_OPEN                      0x00000001
#define V_FRONT                     0x00000040
#define V_CENTRAL                   0x00000020
#define V_BACK                      0x00000010
#define V_ROUNDED                   0x00000080
#define PULMONIC_CONSONANT          0x10000000
#define PC_GLOTAL                   0x00000001
#define PC_PHARYNGEAL               0x00000002
#define PC_UVULAR                   0x00000004
#define PC_VELAR                    0x00000008
#define PC_PALATAL                  0x00000010
#define PC_RETROFLEX                0x00000020
#define PC_POST_ALVEOLAR            0x00000040
#define PC_ALVEOLAR                 0x00000080
#define PC_DENTAL                   0x00000100
#define PC_LABIO_DENTAL             0x00000200
#define PC_BILABIAL                 0x00000400
#define PC_LATERAL_APPROXIMANT      0x00000800
#define PC_APPROXIMANT              0x00001000
#define PC_LATERAL_FRICATIVE        0x00002000
#define PC_FRICATIVE                0x00004000
#define PC_TAP_FLAP                 0x00008000
#define PC_TRILL                    0x00010000
#define PC_NASAL                    0x00020000
#define PC_PLOSIVE                  0x00040000
#define PC_VOICED                   0x00080000

// IPA SYMBOLS


//VOWELS
#define V_FRONT_CLOSE_ROUND         VOWEL + V_CLOSE + V_FRONT + V_ROUNDED
#define V_FRONT_CLOSE               VOWEL + V_CLOSE + V_FRONT
#define V_FRONT_CLMID_ROUND         VOWEL + V_CLOSE_MID + V_FRONT + V_ROUNDED
#define V_FRONT_CLMID               VOWEL + V_CLOSE_MID + V_FRONT
#define V_FRONT_OPMID_ROUND         VOWEL + V_OPEN_MID + V_FRONT + V_ROUNDED
#define V_FRONT_OPMID               VOWEL + V_OPEN_MID + V_FRONT
#define V_FRONT_OPMOPEN             VOWEL + V_OPEN_MID + V_OPEN + V_FRONT
#define V_FRONT_OPEN_ROUND          VOWEL + V_OPEN + V_FRONT + V_ROUNDED
#define V_FRONT_OPEN                VOWEL + V_OPEN + V_FRONT
#define V_FCENTRAL_CCLMID_ROUND     VOWEL + V_CLOSE + V_FRONT + V_CENTRAL + V_CLOSE_MID + V_ROUNDED
#define V_FCENTRAL_CCLMID           VOWEL + V_CLOSE + V_FRONT + V_CENTRAL + V_CLOSE_MID
#define V_CENTRAL_CLOSE_ROUND       VOWEL + V_CLOSE + V_CENTRAL + V_ROUNDED
#define V_CENTRAL_CLOSE             VOWEL + V_CLOSE + V_CENTRAL
#define V_CENTRAL_CLMID_ROUNDED     VOWEL + V_CLOSE_MID + V_CENTRAL + V_ROUNDED
#define V_CENTRAL_CLMID             VOWEL + V_CLOSE_MID + V_CENTRAL
#define V_CENTRAL_MID               VOWEL + V_CLOSE_MID + V_OPEN_MID + V_CENTRAL
#define V_CENTRAL_OPMID_ROUND       VOWEL + V_OPEN_MID + V_CENTRAL + V_ROUNDED
#define V_CENTRAL_OPMID             VOWEL + V_OPEN_MID + V_CENTRAL
#define V_CENTRAL_OOPMID            VOWEL + V_OPEN_MID + V_OPEN + V_CENTRAL
#define V_CBACK_CCLMID              VOWEL + V_CLOSE + V_CLOSE_MID + V_CENTRAL + V_BACK
#define V_BACK_CLOSE_ROUND          VOWEL + V_CLOSE + V_BACK + V_ROUNDED
#define V_BACK_CLOSE                VOWEL + V_CLOSE + V_BACK
#define V_BACK_CLMID_ROUND          VOWEL + V_CLOSE_MID + V_BACK + V_ROUNDED
#define V_BACK_CLMID                VOWEL + V_CLOSE_MID + V_BACK
#define V_BACK_OPMID_ROUND          VOWEL + V_OPEN_MID + V_BACK + V_ROUNDED
#define V_BACK_OPMID                VOWEL + V_OPEN_MID + V_BACK
#define V_BACK_OPEN_ROUND           VOWEL + V_OPEN + V_BACK + V_ROUNDED
#define V_BACK_OPEN                 VOWEL + V_OPEN + V_BACK

//CONSONANTS
#define PC_PLOS_BILAB_VOICED        PULMONIC_CONSONANT + PC_PLOSIVE + PC_BILABIAL + PC_VOICED
#define PC_PLOS_BILAB               PULMONIC_CONSONANT + PC_PLOSIVE + PC_BILABIAL
#define PC_PLOS_DENTA               PULMONIC_CONSONANT + PC_DENTAL + PC_ALVEOLAR + PC_PLOSIVE
#define PC_PLOS_PALVE               PULMONIC_CONSONANT + PC_ALVEOLAR + PC_POST_ALVEOLAR + PC_PLOSIVE
#define PC_PLOS_RETRO_VOICED        PULMONIC_CONSONANT + PC_PLOSIVE + PC_RETROFLEX + PC_VOICED
#define PC_PLOS_RETRO               PULMONIC_CONSONANT + PC_PLOSIVE + PC_RETROFLEX
#define PC_PLOS_PALAT_VOICED        PULMONIC_CONSONANT + PC_PALATAL + PC_PLOSIVE + PC_VOICED
#define PC_PLOS_PALAT               PULMONIC_CONSONANT + PC_PALATAL + PC_PLOSIVE
#define PC_PLOS_VELAR_VOICED        PULMONIC_CONSONANT + PC_PLOSIVE + PC_VELAR + PC_VOICED
#define PC_PLOS_VELAR               PULMONIC_CONSONANT + PC_PLOSIVE + PC_VELAR
#define PC_PLOS_UVULA_VOICED        PULMONIC_CONSONANT + PC_PLOSIVE + PC_UVULAR + PC_VOICED
#define PC_PLOS_UVULA               PULMONIC_CONSONANT + PC_PLOSIVE + PC_UVULAR
#define PC_PLOS_GLOTAL              PULMONIC_CONSONANT + PC_PLOSIVE + PC_GLOTAL
#define PC_NASAL_BILABIAL_VOICED    PULMONIC_CONSONANT + PC_NASAL + PC_BILABIAL + PC_VOICED
#define PC_NASAL_LABDENT_VOICED     PULMONIC_CONSONANT + PC_NASAL + PC_LABIO_DENTAL + PC_VOICED
#define PC_NASAL_PALVE              PULMONIC_CONSONANT + PC_ALVEOLAR + PC_POST_ALVEOLAR + PC_NASAL
#define PC_NASAL_RETRO_VOICED       PULMONIC_CONSONANT + PC_NASAL + PC_RETROFLEX + PC_VOICED
#define PC_NASAL_PALAT_VOICED       PULMONIC_CONSONANT + PC_NASAL + PC_PALATAL + PC_VOICED
#define PC_NASAL_VELAR_VOICED       PULMONIC_CONSONANT + PC_NASAL + PC_VELAR + PC_VOICED
#define PC_NASAL_UVULA_VOICED       PULMONIC_CONSONANT + PC_NASAL + PC_UVULAR + PC_VOICED
#define PC_TRILL_BILABIAL_VOICED    PULMONIC_CONSONANT + PC_TRILL + PC_BILABIAL + PC_VOICED
#define PC_TRILL_PALVE              PULMONIC_CONSONANT + PC_TRILL + PC_ALVEOLAR + PC_POST_ALVEOLAR
#define PC_TRILL_UVULA_VOICED       PULMONIC_CONSONANT + PC_UVULAR + PC_TRILL + PC_VOICED
#define PC_TAP_PALVE                PULMONIC_CONSONANT + PC_TAP_FLAP + PC_ALVEOLAR + PC_POST_ALVEOLAR
#define PC_TAP_RETRO_VOICED         PULMONIC_CONSONANT + PC_TAP_FLAP + PC_RETROFLEX + PC_VOICED
#define PC_FRIC_BILABIAL_VOICED     PULMONIC_CONSONANT + PC_FRICATIVE + PC_BILABIAL + PC_VOICED
#define PC_FRIC_BILABIAL            PULMONIC_CONSONANT + PC_FRICATIVE + PC_BILABIAL
#define PC_FRIC_LABDENT_VOICED      PULMONIC_CONSONANT + PC_FRICATIVE + PC_LABIO_DENTAL + PC_VOICED
#define PC_FRIC_LABDENT             PULMONIC_CONSONANT + PC_FRICATIVE + PC_LABIO_DENTAL
#define PC_FRIC_DENT_VOICED         PULMONIC_CONSONANT + PC_FRICATIVE + PC_DENTAL + PC_VOICED
#define PC_FRIC_DENT                PULMONIC_CONSONANT + PC_FRICATIVE + PC_DENTAL
#define PC_FRIC_ALVEOL_VOICED       PULMONIC_CONSONANT + PC_FRICATIVE + PC_ALVEOLAR + PC_VOICED
#define PC_FRIC_ALVEOL              PULMONIC_CONSONANT + PC_FRICATIVE + PC_ALVEOLAR
#define PC_FRIC_POSTALV_VOICED      PULMONIC_CONSONANT + PC_FRICATIVE + PC_POST_ALVEOLAR + PC_VOICED
#define PC_FRIC_POSTALV             PULMONIC_CONSONANT + PC_FRICATIVE + PC_POST_ALVEOLAR
#define PC_FRIC_RETROFLEX_VOICED    PULMONIC_CONSONANT + PC_FRICATIVE + PC_RETROFLEX + PC_VOICED
#define PC_FRIC_RETROFLEX           PULMONIC_CONSONANT + PC_FRICATIVE + PC_RETROFLEX
#define PC_FRIC_PALAT_VOICED        PULMONIC_CONSONANT + PC_FRICATIVE + PC_PALATAL + PC_VOICED
#define PC_FRIC_PALAT               PULMONIC_CONSONANT + PC_FRICATIVE + PC_PALATAL
#define PC_FRIC_VELAR_VOICED        PULMONIC_CONSONANT + PC_FRICATIVE + PC_VELAR + PC_VOICED
#define PC_FRIC_VELAR               PULMONIC_CONSONANT + PC_FRICATIVE + PC_VELAR
#define PC_FRIC_UVULAR_VOICED       PULMONIC_CONSONANT + PC_FRICATIVE + PC_UVULAR + PC_VOICED
#define PC_FRIC_UVULAR              PULMONIC_CONSONANT + PC_FRICATIVE + PC_UVULAR
#define PC_FRIC_PHARYNG_VOICED      PULMONIC_CONSONANT + PC_FRICATIVE + PC_PHARYNGEAL + PC_VOICED
#define PC_FRIC_PHARYNG             PULMONIC_CONSONANT + PC_FRICATIVE + PC_PHARYNGEAL
#define PC_FRIC_GLOTAL_VOICED       PULMONIC_CONSONANT + PC_FRICATIVE + PC_GLOTAL + PC_VOICED
#define PC_FRIC_GLOTAL              PULMONIC_CONSONANT + PC_FRICATIVE + PC_GLOTAL
#define PC_LATFRIC_DENTA            PULMONIC_CONSONANT + PC_LATERAL_FRICATIVE + PC_ALVEOLAR + PC_DENTAL
#define PC_LATFRIC_PALVE            PULMONIC_CONSONANT + PC_LATERAL_FRICATIVE + PC_ALVEOLAR + PC_POST_ALVEOLAR
#define PC_APPROX_LABDENT_VOICED    PULMONIC_CONSONANT + PC_APPROXIMANT + PC_LABIO_DENTAL + PC_VOICED
#define PC_APPROX_PALVE             PULMONIC_CONSONANT + PC_APPROXIMANT + PC_ALVEOLAR + PC_POST_ALVEOLAR + PC_VOICED
#define PC_APPROX_RETRO_VOICED      PULMONIC_CONSONANT + PC_APPROXIMANT + PC_RETROFLEX + PC_VOICED
#define PC_APPROX_PALAT_VOICED      PULMONIC_CONSONANT + PC_APPROXIMANT + PC_PALATAL + PC_VOICED
#define PC_APPROX_VELAR_VOICED      PULMONIC_CONSONANT + PC_APPROXIMANT + PC_VELAR + PC_VOICED
#define PC_LATAPP_PALVE             PULMONIC_CONSONANT + PC_LATERAL_APPROXIMANT + PC_ALVEOLAR + PC_POST_ALVEOLAR + PC_VOICED
#define PC_LATAPP_RETRO_VOICED      PULMONIC_CONSONANT + PC_LATERAL_APPROXIMANT + PC_RETROFLEX + PC_VOICED
#define PC_LATAPP_PALAT_VOICED      PULMONIC_CONSONANT + PC_LATERAL_APPROXIMANT + PC_PALATAL + PC_VOICED
#define PC_LATAPP_VELAR_VOICED      PULMONIC_CONSONANT + PC_LATERAL_APPROXIMANT + PC_VELAR + PC_VOICED


#define MAX_DISTANCE 100
#define CONSONANT_VOWEL_DISTANCE MAX_DISTANCE
#define VOWEL_BIT 28
#define ROUNDED_VOWEL_BIT 7
#define VOICED_CONS_BIT 19

#define VOWEL_OPENING_START 0
#define VOWEL_OPENING_END 3
#define VOWEL_SRC_START 4
#define VOWEL_SRC_END 6

#define CONS_SOUNDGEN_START 11
#define CONS_SOUNDGEN_END 18
#define CONS_OBSTRUCTION_START 0
#define CONS_OBSTRUCTION_END 10


using namespace std;
class Phonetics
{
public:
    Phonetics(string reference = NULL);

    int phonemStringDistance(vector<int> w1, vector<int> w2);
    int phonemStringDistance(QString w1, QString w2);
    static vector<int> phonemsFromString(QString src);

private:
    int phonemsDistance (int f1, int f2);
    vector<int> vowels;
    vector<int> consonants;
    bool isVowel(int s);

    int vowelDistance(int v1, int v2);
    int vowelsSrcPositionDistance(int v1, int v2);
    int vowelsOpeningDistance(int v1, int v2);
    bool isVowelRound(int v);

    int consonantDistance(int c1, int c2);
    int consonantSoundGenerationDist(int c1, int c2);
    int consonantObstructionDist(int c1, int c2);
    bool isVoicedConsonant(int c);

    int normalizeDistance(int strSize, int rawDistance);
    bool isBitOn(int src, unsigned int bit);
    bool isPowerOf2(int src);

    int getOpeningFromVowel(int v);
    int getSrcFromVowel(int v);

    int getSoundTypeFromCons(int c);
    int getObstructionFromCons(int c);

    int build_AND_Mask(unsigned int initBit, unsigned int finalBit);
    float bitCenterOfMass(int src, int beg, int end);
    string referenceFile;

};

#endif // PHONETICS_H
