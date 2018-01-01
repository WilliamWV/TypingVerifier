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
#define COMMANDS_COL 1
#define TITLE_ROW 0
#define REPLACE_ROW 1
#define SUGGESTION_ROW 1
#define REPLACE_ALL_ROW 2
#define ADD_TO_DICT_ROW 3
#define IGNORE_ROW 4
#define SUGGESTION_ROWSPAN 4
#define SUGGESTION_COL_W 100
#define COMMANDS_COL_W 50
#define ROWS_HEIGHT 25


using namespace std;

class Suggestion : public QWidget
{
    Q_OBJECT
public:
    explicit Suggestion(QWidget *parent = nullptr, QString typed);


signals:

    void replaceAll(QString suggested);
    void replace(QString suggested);
    void ignore();
    void addToDict();

private slots:
    void onSuggestedWordChanged();
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
    QString currentSuggestion;
    SimilarityAnalizer *sa;

    void initializeGridLayout();
    void connectHandlers();
    void createWidgets();
};

#endif // SUGGESTION_H
