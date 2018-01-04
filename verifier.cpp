#include "verifier.h"

Verifier::Verifier(QWidget *parent) :
    QWidget(parent)
{
    this->initializeGridLayout();
    this->createWidgets();
    this->connectHandlers();
    this->sAnalizer = new SimilarityAnalizer("testDict.txt");
    this->setLayout(this->gridLayout);
    this->show();
}

void Verifier::createWidgets()
{

    createFileManagWidgets();
    createLanguageChooser();
    createVerifyWidgets();
    createTextView();
}
void Verifier::createFileManagWidgets()
{
    this->loadPB = new QPushButton("Load File");
    this->savePB = new QPushButton("Save File");
    this->gridLayout->addWidget(
                loadPB, LOAD_BUTTON_ROW, COMMANDS_COL);
    this->gridLayout->addWidget(
                this->savePB, SAVE_BUTTON_ROW, COMMANDS_COL);
}
void Verifier::createLanguageChooser()
{
    this->languageCB = new QComboBox();

    //add languages using addItem and include proper handling

    this->languageLB = new QLabel("Choose Language");
    this->gridLayout->addWidget(
                this->languageLB, LANG_LABEL_ROW, COMMANDS_COL);
    this->gridLayout->addWidget(
                this->languageCB, LANG_COMBOBOX_ROW, COMMANDS_COL);


}
void Verifier::createVerifyWidgets()
{
    this->autoVerificationCHB = new QCheckBox("Auto verify");
    this->verifyPB = new QPushButton("Verify");
    this->verifyPB->setFixedSize(C2_MIN_WIDTH, ROWS_MIN_HEIGHT * 2 + DEFAULT_SPACING);
    this->verifyPBItem = new QWidgetItem(this->verifyPB);
    this->gridLayout->addItem(
                this->verifyPBItem, VERIFY_BUTTON_ROW, COMMANDS_COL, 2);//uses 2 rows
    this->gridLayout->addWidget(
                this->autoVerificationCHB, AUTOVERIFY_CHB_ROW, COMMANDS_COL);

    this->autoVerify = false;


}
void Verifier::createTextView()
{
    this->textView = new QTextEdit();
    this->textItem = new QWidgetItem(this->textView);
    this->gridLayout->addItem(
                this->textItem, TEXT_ROW, TEXT_COL, LAYOUT_ROWS);
}

void Verifier::initializeGridLayout()
{
    this->gridLayout = new QGridLayout();
    this->gridLayout->setColumnMinimumWidth(TEXT_COL, C1_MIN_WIDTH);
    this->gridLayout->setColumnMinimumWidth(COMMANDS_COL, C2_MIN_WIDTH);
    for (int i = 0; i<LAYOUT_ROWS; i++)
    {
        this->gridLayout->setRowMinimumHeight(i, ROWS_MIN_HEIGHT);
    }
    this->gridLayout->setSpacing(DEFAULT_SPACING);

    //add blank rows that should resize when the window is redimensioned
    this->gridLayout->setRowStretch(0, 1);//first row
    this->gridLayout->setRowStretch(SAVE_BUTTON_ROW + 1, 1);//bellow save buttom
    this->gridLayout->setRowStretch(LANG_COMBOBOX_ROW + 1, 1);//bellow combo box
    this->gridLayout->setRowStretch(AUTOVERIFY_CHB_ROW + 1, 1);//bellow check box

    //sets the first collumn (of the text view) to resize when the window is
    //redimentioned
    this->gridLayout->setColumnStretch(TEXT_COL, 1);
}

void Verifier::connectHandlers()
{
    connect(
       this->loadPB, SIGNAL(clicked(bool)),
       this, SLOT(on_load_button_clicked()));
    connect(
       this->savePB, SIGNAL(clicked(bool)),
       this, SLOT(on_save_button_clicked()));
    connect(
       this->languageCB, SIGNAL(currentIndexChanged(int)),
       this, SLOT(on_language_cb_modified()));
    connect(
       this->verifyPB, SIGNAL(clicked(bool)),
       this, SLOT(on_verify_button_clicked()));
    connect(
       this->autoVerificationCHB, SIGNAL(toggled(bool)),
       this, SLOT(on_auto_verify_changed()));
    connect(
       this->textView, SIGNAL(textChanged()),
       this, SLOT(on_text_changed()));


}
void Verifier::connectSuggestionHandlers()
{
    connect(
       this->sug, SIGNAL(addToDict(QString)),
       this, SLOT(on_suggest_addToDict(QString)));
    connect(
       this->sug, SIGNAL(replace(QString,QString)),
       this, SLOT(on_suggest_replace(QString,QString)));
    connect(
       this->sug, SIGNAL(replaceAll(QString,QString)),
       this, SLOT(on_suggest_replace_all(QString,QString)));
    connect(
       this->sug, SIGNAL(requestNextMistake()),
       this, SLOT(on_suggest_requiredNext()));
    connect(
       this->sug, SIGNAL(closing()),
       this, SLOT(on_suggest_close()));

}


void Verifier::on_text_changed()
{
    this->currentText = this->textView->toPlainText();
    QStringList newWords = this->getWordsFromText();

    if(this->autoVerify)
    {

    }

}
void Verifier::on_language_cb_modified()
{
    std::cout<<"Lang Not yet implemented"<<endl;
}
void Verifier::on_auto_verify_changed()
{
    this->autoVerify = this->autoVerificationCHB->isChecked();
}
void Verifier::on_verify_button_clicked()
{
    this->words = this->getWordsFromText();
    this->wrongWordsIndex = this->getWrongWords();

    QString results = this->buildVerificationAns(this->wrongWordsIndex);
    QString title = QString("Results");

    if(this->wrongWordsIndex.size()>0)
    {
        QMessageBox dialog(title, results,
                           QMessageBox::Question,
                           QMessageBox::Yes | QMessageBox::Default,
                           QMessageBox::No | QMessageBox::Escape,
                           QMessageBox::NoButton);

        if(dialog.exec() == QMessageBox::Yes)
        {
            this->sug = new Suggestion(
                        this->words[this->wrongWordsIndex[0]],
                        this->getWordContext(this->wrongWordsIndex[0]),
                        this->sAnalizer);
            this->connectSuggestionHandlers();
        }

    }
    else
    {
        QMessageBox dialog(title, results,
                           QMessageBox::Information,
                           QMessageBox::Ok | QMessageBox::Default,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton
                           );
        dialog.exec();

    }

}
void Verifier::on_load_button_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Choose File"), "",
            tr("TXT file (*.txt)"));
    ifstream file;
    try
    {
        file.open(fileName.toStdString());
        std::stringstream textBuff;
        textBuff<<file.rdbuf();
        this->textView->setText(QString::fromStdString(textBuff.str()));

    }catch(exception ex)
    {
        this->generateError("Failed to load the file");
        cout<<ex.what();
    }

}
void Verifier::on_save_button_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Text"), "",
            tr("TXT file (*.txt);;All Files (*)"));
    ofstream file;
    try{
        file.open(fileName.toStdString());
        file<<this->currentText.toStdString();
    }
    catch(exception ex)
    {
        this->generateError(tr("Failed to save the text"));
        cout<<ex.what();
    }
}


void Verifier::generateError(QString message)
{
    QMessageBox errorBox;
    errorBox.critical(this, "Error", message);
}


QStringList Verifier::getWordsFromText()
{
    QRegExp sep("[\\W_]");
    QStringList strList = this->currentText.split(sep);
    strList.removeAll(QString(""));
    return strList;
}

vector<int> Verifier::getWrongWords()
{

    vector<int> answer;
    for(int i = 0; i<this->words.size(); i++)
    {
        QString currentWords = words.at(i);
        if(!this->sAnalizer->containsReferenceTo(currentWords.toStdString()))
        {
            answer.push_back(i);
        }
    }
    return answer;
}

QString Verifier::buildVerificationAns(vector<int> mistakes)
{
    int n = mistakes.size();
    if(n == 0)
        return QString("Nothing to correct");
    else
    {
        QString results("There was ");
        results.append(QString::number(n)).append(" mistakes\n Click YES to open Suggestions or NO to ignore");

        return results;

    }
}

void Verifier::on_suggest_replace(QString srcString, QString suggestion)
{
    int wordIndex = this->wrongWordsIndex[0];
    this->words.replace(wordIndex, suggestion);
    this->updateText(wordIndex, srcString, suggestion);

}
void Verifier::on_suggest_replace_all(QString srcString, QString suggestion)
{
    for(unsigned int i = 0; i<this->wrongWordsIndex.size(); i++)
    {
        QString onText = this->words[this->wrongWordsIndex[i]];
        if(onText == srcString)
        {
            this->words.replace(this->wrongWordsIndex[i], suggestion);
            this->updateText(this->wrongWordsIndex[i], srcString, suggestion);
        }
    }
    this->update();
}
void Verifier::on_suggest_addToDict(QString srcString)
{
    vector<string> currentReferences = this->sAnalizer->getReferences();
    string adding = srcString.toStdString();
    cout<<0;
    for(unsigned int i = 0; i<currentReferences.size(); i++)
    {
        if(currentReferences[i].compare(adding)>0)
        {
            currentReferences.insert(
                        currentReferences.begin() + i, adding);
            break;
        }
    }

    this->modifyReferenceFile(currentReferences);
    this->sAnalizer->setReferences(currentReferences);

}

void Verifier::modifyReferenceFile(vector<string> refWords)
{
    string fileName = this->sAnalizer->getRefFileName();

    ofstream fileHandler;
    fileHandler.open(fileName);

    for(unsigned int i = 0; i<refWords.size(); i++)
    {
        fileHandler<<refWords[i]<<endl;
    }

}

void Verifier::on_suggest_requiredNext()
{
    QString next = this->getNextMistake();
    QString context;

    if(next.isEmpty())
        context = EMPTY_STRING;
    else
        context = this->getWordContext(this->wrongWordsIndex[0]);
    this->sug->updateWord(next, context);
}

void Verifier::updateText(int wordIndex, QString srcString, QString suggestion)
{
    int initWordCharIndex = this->findInitialWordCharIndex(wordIndex);

    QString onText = this->currentText.mid(initWordCharIndex, srcString.size());

    if (onText != srcString)
    {
        this->generateError("String on text and string found are not the same");
    }
    else
    {
        this->currentText.replace(initWordCharIndex, srcString.size(), suggestion);
        this->textView->setText(this->currentText);
    }

}

int Verifier::findInitialWordCharIndex(int wordIndex)
{
    bool found = false;
    bool inWord = false;

    int index = 0;
    int wordCounter = -1; // -1 because it will be increased when a word is found
    int initWordCharIndex;
    while(! found)
    {
        QChar currentChar = this->currentText[index];
        if(inWord)
        {
            if(currentChar.isPunct() || currentChar.isSpace())
            {
                inWord = false;
            }
        }
        else{
            if(currentChar.isLetterOrNumber())
            {
                inWord = true;
                wordCounter++;
                if(wordCounter == wordIndex)
                {
                    initWordCharIndex = index;
                    found = true;
                }
            }
        }
        index++;
    }
    return initWordCharIndex;
}

void Verifier::on_suggest_close()
{
    QMessageBox dialog (tr("Finished"),
                        tr("Correction complete.\n"),
                        QMessageBox::Information,
                        QMessageBox::Ok,
                        QMessageBox::NoButton,
                        QMessageBox::NoButton);
    dialog.exec();

}
QString Verifier::getNextMistake()
{
    this->wrongWordsIndex.erase(this->wrongWordsIndex.begin());

    if(this->wrongWordsIndex.empty())
        return EMPTY_STRING;

    QString next = this->words[this->wrongWordsIndex[0]];

    return next;
}

QString Verifier::getWordContext(int wordIndex)
{
    QString context = EMPTY_STRING;
    int prevWords = N_OF_WORDS_ON_CONTEXT/2;
    int postWords = N_OF_WORDS_ON_CONTEXT/2;
    if(prevWords>wordIndex)
        prevWords = wordIndex;
    if(postWords + wordIndex>= this->words.size())
    {
        postWords = this->words.size() - wordIndex - 1;
    }
    for(int i = prevWords; i>0; i--)
    {
        context.append(this->words[wordIndex - i]).append(" ");
    }
    context.append(this->words[wordIndex]).append(" ");
    for(int i = 0; i<postWords; i++)
    {
        context.append(this->words[wordIndex + i + 1]).append(" ");
    }

    return context;

}


Verifier::~Verifier()
{
    delete gridLayout;
    delete loadPB;
    delete savePB;
    delete verifyPB;
    delete textView;
    delete languageLB;
    delete languageCB;
    delete autoVerificationCHB;
    delete textItem;
    delete verifyPBItem;
}
