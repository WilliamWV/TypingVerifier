#ifndef VERIFIER_H
#define VERIFIER_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QWidgetItem>

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


class Verifier : public QWidget
{
    Q_OBJECT

public:
    explicit Verifier(QWidget *parent = 0);
    ~Verifier();

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
    void createWidgets();
    void createFileManagWidgets();
    void createLanguageChooser();
    void createVerifyWidgets();
    void createTextView();
    void initializeGridLayout();
};


#endif // VERIFIER_H
