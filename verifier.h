#ifndef VERIFIER_H
#define VERIFIER_H

#include "similarityanalizer.h"
#include "suggestion.h"
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QWidgetItem>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#define C2_MIN_WIDTH 100
#define C1_MIN_WIDTH 200
#define ROWS_MIN_HEIGHT 25
#define DEFAULT_SPACING 5
#define LAYOUT_ROWS 11

#define LOAD_BUTTON_ROW 1
#define SAVE_BUTTON_ROW 2
#define LANG_LABEL_ROW 4
#define LANG_COMBOBOX_ROW 5
#define VERIFY_BUTTON_ROW 7
#define AUTOVERIFY_CHB_ROW 9
#define TEXT_ROW 0

#define COMMANDS_COL 1
#define TEXT_COL 0
#define EMPTY_STRING QString("")
#define HIGHLIGHT_TAG "<font color=\"red\">"
#define HIGHLIGHT_CLOSE_TAG "</font>"

#define HIGHLIGHT_TAG_SIZE 18
#define N_OF_WORDS_ON_CONTEXT 10 //5 each side

using namespace std;

class Verifier : public QWidget
{
    Q_OBJECT

public:
    explicit Verifier(QWidget *parent = 0);
    ~Verifier();

private slots:

    void on_text_changed();
    void on_language_cb_modified();
    void on_auto_verify_changed();
    void on_verify_button_clicked();
    void on_load_button_clicked();
    void on_save_button_clicked();
    void on_suggest_replace(QString srcString, QString suggestion);
    void on_suggest_replace_all(QString srcString, QString suggestion);
    void on_suggest_addToDict(QString srcString);
    void on_suggest_requiredNext();
    void on_suggest_close();
    void on_suggest_contextChanged(QString newContext);
private:
    QGridLayout *gridLayout;
    QPushButton *loadPB;
    QPushButton *savePB;
    QPushButton *verifyPB;
    QTextEdit *textView;
    QLabel *languageLB;
    QComboBox *languageCB;
    QCheckBox *autoVerificationCHB;
    QWidgetItem *textItem;
    QWidgetItem *verifyPBItem;
    QString currentText;
    bool autoVerify;
    vector<int> wrongWordsIndex;
    Suggestion *sug;
    SimilarityAnalizer *sAnalizer;
    QStringList words;

    void createWidgets();
    void createFileManagWidgets();
    void createLanguageChooser();
    void createVerifyWidgets();
    void createTextView();
    void initializeGridLayout();
    QStringList getWordsFromText();
    void connectHandlers();
    void generateError(QString message);
    QString buildVerificationAns(vector<int> mistakes);
    QString getNextMistake();
    vector<int> getWrongWords();
    void updateText(int wordIndex, QString srcString, QString suggestion);
    int findInitialWordCharIndex(int wordIndex);
    void connectSuggestionHandlers();
    void modifyReferenceFile(vector<string> refWords);
    QString getWordContext(int wordIndex);
    int getInitialWordOnContext(int mainWord);
    int getFinalWordOnContext(int mainWord);
    QString highlightWord(QString context, int wordIndex);

};


#endif // VERIFIER_H
