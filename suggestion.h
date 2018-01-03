#ifndef SUGGESTION_H
#define SUGGESTION_H

#include "similarityanalizer.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QGridLayout>
#include <QWidgetItem>

#define SUGGESTION_COL 0
#define BUTTONS_COL 1
#define TITLE_ROW 0
#define REPLACE_ROW 1
#define SUGGESTION_ROW 1
#define REPLACE_ALL_ROW 2
#define ADD_TO_DICT_ROW 3
#define IGNORE_ROW 4
#define SUGGESTION_ROWSPAN 4
#define SUGGESTION_COL_W 100
#define BUTTONS_COL_W 50
#define ROWS_H 25
#define N_OF_ROWS 4
#define SPACING 5
#define TITLE_WIDHT 2
#define BASE_SIMILARITY_THRESHOLD 2
#define MIN_SUGGESTED_WORD 5
#define MAX_SIMILARITY_THRESHOLD 4
#define SUGGESTION_WINDOW_HEIGHT 180
#define SUGGESTION_WINDOW_WIDTH 375
using namespace std;

class Suggestion : public QWidget
{
    Q_OBJECT
public:
    explicit Suggestion(QString typed, SimilarityAnalizer *refAnalizer, QWidget *parent = nullptr);
    void updateWord(QString newWord);

signals:

    void replaceAll(QString currentSrcWord,QString suggested);
    void replace(QString currentSrcWord, QString suggested);
    void addToDict(QString currentSrcWord);
    void requestNextMistake();

private slots:
    void onSuggestedWordChanged(int row);
    void onReplacePBClicked();
    void onReplaceAllPBClicked();
    void onIgnorePBClicked();
    void onAddToDictPBClicked();


private:

    QPushButton *replacePB;
    QPushButton *replaceAllPB;
    QPushButton *ignorePB;
    QPushButton *addToDictPB;
    QListWidget *suggestionChooser;
    QLabel *suggestionTitle;
    QGridLayout *gridLayout;
    QWidgetItem *suggestionItem;
    QWidgetItem *titleItem;
    QString currentSuggestion;
    QString currentSrcWord;
    SimilarityAnalizer *sAnalizer;

    void initializeGridLayout();
    void connectHandlers();
    void createWidgets(QString typed);
    void createSuggestion(QString typed);
};

#endif // SUGGESTION_H
