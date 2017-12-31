#include "verifier.h"

Verifier::Verifier(QWidget *parent) :
    QWidget(parent)
{
    this->initializeGridLayout();
    this->createWidgets();
    this->connectHandlers();
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

void Verifier::on_text_changed()
{
    this->currentText = this->textView->toPlainText();
    QStringList newWords = this->getWords();

    if(this->autoVerify)
        //not yet implemented
    {}

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

    std::cout<<"Verify Not yet implemented"<<endl;
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


QStringList Verifier::getWords()
{
    QRegExp sep("[\\W_]");
    QStringList strList = this->currentText.split(sep);
    return strList;
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
