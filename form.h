#ifndef FORM_H
#define FORM_H

#include <QWidget>

#include "card.h"

namespace Ui {
class Form;
}

class Form : public OverlayWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *c, QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Form *ui;

    bool _expanded;
};

#endif // FORM_H
