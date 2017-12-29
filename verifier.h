#ifndef VERIFIER_H
#define VERIFIER_H

#include <QMainWindow>

namespace Ui {
class Verifier;
}

class Verifier : public QMainWindow
{
    Q_OBJECT

public:
    explicit Verifier(QWidget *parent = 0);
    ~Verifier();

private:
    Ui::Verifier *ui;
};

#endif // VERIFIER_H
