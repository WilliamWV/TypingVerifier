#include "suggestion.h"

/**
    Class constructor
    Suggestion::Suggestion(QString typed, QString context, SimilarityAnalizer *refAnalizer, QWidget *parent)
    @brief initialize the suggestion window with the first word and its context,
    this will initialize the basic structure of the object and will be ready to
    retrieve suggestions and change current word
    @param typed : string found in the text that should be wrong
    @param context: string with the word highlighted and its sorrounding
    @param refAnalizer: instance of class SimilarityAnalizer previously created
    with some reference dictionary
    @param parent: widget that is the owner, of this class


*/
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

/**
    void Suggestion::initializeGridLayout()
    @brief initialize properties of the window layout as cells size and
    spacing, this also sets the general size of the window as fixed to
    a good visualization of the results

*/
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
/**
    void Suggestion::connectHandlers()
    @brief connect usefull signals from widgets of this class
    with the corresponding handler function
*/
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
/**
    void Suggestion::createWidgets(QString typed, QString context)
    @brief create the widgets of this class and also allocate them
    to the reserved position on the grid layout

    @param typed: initial string passed from constructor
    @param context: sorrounding of the string as passed to the constructor

*/
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

/**
    void Suggestion::createSuggestion(QString typed)
    @brief using the reference instance of SimilarityAnalizer
    class create some suggestions for the typed word based on
    the similarity of them.
        If it found some suggestions it places it on the word
    chooser widget, otherwise it disable the buttons of replace
    and replace all once there is no suggestion, so the user can
    handly modificate the text, ignore the mistake or add the
    string to the reference dictionary.

    @param typed: string to which suggestions should be created
*/
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

/**
    void Suggestion::updateWord(QString newWord, QString context)
    @brief changes the current analized word, if the passed word
    is empty it closes the suggestion window assuming that the
    verification is complete

    @param newWord: new word to be analized
    @param context: sorrounding of the new word

*/
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

/**
   void Suggestion::onSuggestedWordChanged(int row)
   @brief handler called when the user changes the highlighted
   word of the word chooser, this function changes the current
   suggestion accordingly with the user choose if it was valid

*/
void Suggestion::onSuggestedWordChanged(int row)
{
    if(row>0 && row<this->suggestionChooser->count())
        this->currentSuggestion = this->suggestionChooser->item(row)->text();
}
/**
    void Suggestion::onReplacePBClicked()
    @brief handler to clicks on button Replace, this
    emit signals that should be handled by the class
    that constrols the main text and ask it to change
    the references of the word that should be replaced
    and request that it sends back the new word to
    continue the verification

*/
void Suggestion::onReplacePBClicked()
{
    emit replace(this->currentSrcWord, this->currentSuggestion);
    emit requestNextMistake();
}

/**
    void Suggestion::onReplaceAllPBClicked()
    @brief handler to replace all button, interacts with the class
    that controls the main text reporting what should be changed and
    request the new word to continue verification

*/
void Suggestion::onReplaceAllPBClicked()
{
    emit replaceAll(this->currentSrcWord, this->currentSuggestion);
    emit requestNextMistake();
}
/**
    void Suggestion::onIgnorePBClicked()
    @brief handles the ignore button, this only request the next word
    from the class that control the main text.
*/
void Suggestion::onIgnorePBClicked()
{
    emit requestNextMistake();
}
/**
    void Suggestion::onAddToDictPBClicked()
    @brief handles the add to dict button and ask the class that can
    modifies the references to insert the new string, this also request
    the next word to continue the verifications.
*/
void Suggestion::onAddToDictPBClicked()
{
    emit addToDict(this->currentSrcWord);
    emit requestNextMistake();
}

/**
   void Suggestion::onApplyPBClicked()
   @brief handles the apply changes button, used when the user modifies
   the text through the suggestion window, this reports the changes to
   the class that controlls the main text, also request the next word
   to continue the verification

*/
void Suggestion::onApplyPBClicked()
{
    emit contextTextChanged(this->editableContext->toPlainText());
    emit requestNextMistake();
}

/**
  void Suggestion::onContextTextChanged()
  @brief handle changes by user on the suggestion editable text
  showing the word and its sorroundings. This enables the apply
  button, so that the user can request to replace what was in the
  text with the new edited content
*/
void Suggestion::onContextTextChanged()
{
    this->applyPB->setEnabled(true);
}
