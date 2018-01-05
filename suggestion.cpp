#include "suggestion.h"

Suggestion::Suggestion(QString typed, QString context, SimilarityAnalizer *refAnalizer, QWidget *parent) :
    QWidget(parent)
{
    this->initializeGridLayout();
    this->createWidgets(typed, context);
    this->sAnalizer = refAnalizer;
    this->connectHandlers();
    this->setLayout(this->gridLayout);
    this->show();
    this->createSuggestion(typed);
    this->currentSrcWord = typed;

}

void Suggestion::initializeGridLayout()
{
    this->gridLayout = new QGridLayout();
    this->gridLayout->setColumnMinimumWidth(SUGGESTION_COL, SUGGESTION_COL_W);
    this->gridLayout->setColumnMinimumWidth(BUTTONS_COL, BUTTONS_COL_W);

    for (int i = 0; i<N_OF_ROWS; i++)
    {
        this->gridLayout->setRowMinimumHeight(i, ROWS_H);
    }
    this->gridLayout->setRowMinimumHeight(CONTEXT_ROW, CONTEXT_ROW_HEIGHT);
    this->gridLayout->setSpacing(SPACING);
    this->setFixedSize(SUGGESTION_WINDOW_WIDTH, SUGGESTION_WINDOW_HEIGHT);
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
        this, SLOT(onSuggestedWordChanged(int)));
    connect(
        this->applyPB, SIGNAL(clicked(bool)),
        this, SLOT(onApplyPBClicked()));
    connect(
        this->editableContext, SIGNAL(textChanged()),
        this, SLOT(onContextTextChanged()));

}
void Suggestion::createWidgets(QString typed, QString context)
{
    this->replacePB = new QPushButton("Replace");
    this->replaceAllPB = new QPushButton("Replace all");
    this->addToDictPB = new QPushButton("Add to Dictionary");
    this->ignorePB = new QPushButton("Ignore");
    this->applyPB = new QPushButton("Apply changes");

    this->suggestionChooser = new QListWidget();
    this->suggestionTitle = new QLabel(
                                    QString("Suggestions for: ")
                                    .append(typed)
                                    .append("\n"));
    this->editableContext = new QTextEdit();
    this->editableContext->setHtml(context);

    this->suggestionItem = new QWidgetItem(this->suggestionChooser);
    this->titleItem = new QWidgetItem(this->suggestionTitle);
    this->contextItem = new QWidgetItem(this->editableContext);


    this->gridLayout->addItem(
                this->titleItem,
                TITLE_ROW, SUGGESTION_COL,
                1, TITLE_WIDHT);
    this->gridLayout->addItem(
                this->suggestionItem,
                SUGGESTION_ROW, SUGGESTION_COL,
                SUGGESTION_ROWSPAN);
    this->gridLayout->addItem(
                this->contextItem,
                CONTEXT_ROW, SUGGESTION_COL,
                1, CONTEXT_WIDHT);

    this->gridLayout->addWidget(
                this->replacePB, REPLACE_ROW, BUTTONS_COL);
    this->gridLayout->addWidget(
                this->replaceAllPB, REPLACE_ALL_ROW, BUTTONS_COL);
    this->gridLayout->addWidget(
                this->addToDictPB, ADD_TO_DICT_ROW, BUTTONS_COL);
    this->gridLayout->addWidget(
                this->ignorePB, IGNORE_ROW, BUTTONS_COL);
    this->gridLayout->addWidget(
                this->applyPB, APPLY_ROW, BUTTONS_COL);
    this->applyPB->setEnabled(false);

}

void Suggestion::createSuggestion(QString typed)
{

    vector<string> suggestions =
            this->sAnalizer->closestThan(
                typed.toStdString(), BASE_SIMILARITY_THRESHOLD);
    if(suggestions.size()<MIN_SUGGESTED_WORD)
        suggestions =
                this->sAnalizer->closestThan(
                    typed.toStdString(), MAX_SIMILARITY_THRESHOLD);
    this->suggestionChooser->clear();
    for(unsigned int i = 0; i<suggestions.size(); i++)
    {
        this->suggestionChooser->addItem(
                    QString::fromStdString(suggestions.at(i)));
    }
    if(this->suggestionChooser->count()>0)
    {
        this->suggestionChooser->setCurrentRow(0);
        this->currentSuggestion = this->suggestionChooser->item(0)->text();
        this->suggestionChooser->setEnabled(true);
        this->replacePB->setEnabled(true);
        this->replaceAllPB->setEnabled(true);
    }
    else
    {
        this->suggestionChooser->setEnabled(false);
        this->replacePB->setEnabled(false);
        this->replaceAllPB->setEnabled(false);
    }

}

void Suggestion::updateWord(QString newWord, QString context)
{

    if(newWord.isEmpty() == false)
    {
        this->suggestionTitle->setText(QString("Suggestions for: ").append(newWord).append("\n"));
        this->createSuggestion(newWord);
        this->currentSrcWord = newWord;
        this->editableContext->setHtml(context);
        this->applyPB->setEnabled(false);
        this->update();

    }
    else
    {
        emit closing();
        this->close();
    }
}

void Suggestion::onSuggestedWordChanged(int row)
{
    if(row>0 && row<this->suggestionChooser->count())
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

void Suggestion::onApplyPBClicked()
{
    emit contextTextChanged(this->editableContext->toPlainText());
    emit requestNextMistake();
}

void Suggestion::onContextTextChanged()
{
    this->applyPB->setEnabled(true);
}
