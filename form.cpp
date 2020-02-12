#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *c, QWidget *parent) :
    OverlayWidget(c,parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    _expanded = false;
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    resize(this->width(), this->height() + (_expanded ? - 50 : + 50));
    _expanded = !_expanded;
    raise();
}
