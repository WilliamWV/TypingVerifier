#include "suggestion.h"

Suggestion::Suggestion(QWidget *parent, QString typed, SimilarityAnalizer *refAnalizer) :
    QWidget(parent)
{
    this->initializeGridLayout();
    this->createWidgets(typed);
    this->sAnalizer = refAnalizer;
    this->connectHandlers();
    this->setLayout(this->gridLayout);
    this->show();
    this->createSuggestions(typed);
    this->currentSrcWord = typed;

}

void Suggestion::intializeGridLayout()
{
    this->gridLayout = new QGridLayout();
    this->gridLayout->setColumnMinimumWidth(SUGGESTION_COL, SUGGESTION_COL_W);
    this->gridLayout->setColumnMinimumWidth(BUTTONS_COL, BUTTONS_COL_W);

    for (int i = 0; i<N_OF_ROWS; i++)
    {
        this->gridLayout->setRowMinimumHeight(i, ROWS_H);
    }
    this->gridLayout->setSpacing(SPACING);
    this->setFixedSize(this->width(), this->height());

}
void Suggestion::connectHandlers()
{
    connect(
        this->replacePB, SIGNAL(clicked(bool)),
        this, SLOT(onReplacePBClicked()));
    connect(
        this->replaceAllPB, SIGNAL(clicked(bool)),
        this, SLOT(onReplaceAllPBClicked()));
    connect(
        this->addToDictPB, SIGNAL(clicked(bool)),
        this, SLOT(onAddToDictPBClicked()));
    connect(
        this->ignorePB, SIGNAL(clicked(bool)),
        this, SLOT(onIgnorePBClicked()));
    connect(
        this->suggestionChooser, SIGNAL(currentRowChanged(int)),
        this, SLOT(onSuggestedWordChanged(int));

}
void Suggestion::createWidgets(QString typed)
{
    this->replacePB = new QPushButton("Replace");
    this->replaceAllPB = new QPushButton("Replace all");
    this->addToDictPB = new QPushButton("Add to Dictionary");
    this->ignorePB = new QPushButton("Ignore");
    this->suggestionChooser = new QListWidget();
    this->suggestionTitle = new QLabel(
                                    QString("Suggestions for: ")
                                    .append(typed)
                                    .append("\n"));
    this->suggestionItem = new QWidgetItem(this->suggestionChooser);
    this->titleItem = new QWidgetItem(this->suggestionTitle);

    this->gridLayout->addItem(
                this->titleItem,
                TITLE_ROW, SUGGESTION_COL,
                1, TITLE_WIDHT);
    this->gridLayout->addItem(
                this->suggestionItem,
                SUGGESTION_ROW, SUGGESTION_COL,
                SUGGESTION_ROWSPAN);
    this->gridLayout->addWidget(
                this->replacePB, REPLACE_ROW, BUTTONS_COL);
    this->gridLayout->addWidget(
                this->replaceAllPB, REPLACE_ALL_ROW, BUTTONS_COL);
    this->gridLayout->addWidget(
                this->addToDictPB, ADD_TO_DICT_ROW, BUTTONS_COL);
    this->gridLayout->addWidget(
                this->ignorePB, IGNORE_ROW, BUTTONS_COL);


}

void Suggestion::createSuggestion(QString typed)
{

    vector<string> suggestions =
            this->sAnalizer->closestThan(
                typed, BASE_SIMILARITY_THRESHOLD);
    if(suggestions.size()<MIN_SUGGESTED_WORD)
        suggestions =
                this->sAnalizer->closestStrings(
                    typed, MIN_SUGGESTED_WORD);

    for(int i = 0; i<suggestions.size(); i++)
    {
        this->suggestionChooser->addItem(
                    QString::fromStdString(suggestions.at(i)));
    }

}

void Suggestion::updateWord(QString newWord)
{
    this->suggestionTitle = new QLabel(
                                    QString("Suggestions for: ")
                                    .append(newWord)
                                    .append("\n"));
    this->titleItem = new QWidgetItem(this->suggestionTitle);

    this->gridLayout->addItem(
                this->titleItem,
                TITLE_ROW, SUGGESTION_COL,
                1, TITLE_WIDHT);

    this->createSuggestions(newWord);
    this->currentSrcWord = newWord;
}



void Suggestion::onSuggestedWordChanged(int row)
{
    this->currentSuggestion = this->suggestionChooser->item(row)->text();
}
void Suggestion::onReplacePBClicked()
{
    emit replace(this->currentSrcWord, this->currentSuggestion);
    emit requestNextMistake();
}
void Suggestion::onReplaceAllPBClicked()
{
    emit replaceAll(this->currentSrcWord, this->currentSuggestion);
    emit requestNextMistake();
}
void Suggestion::onIgnorePBClicked()
{
    emit requestNextMistake();
}
void Suggestion::onAddToDictPBClicked()
{
    emit addToDict(this->currentSrcWord);
    emit requestNextMistake();
}

