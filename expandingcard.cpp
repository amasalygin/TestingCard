#include "expandingcard.h"
#include "ui_expandingcard.h"




ExpandingCard::ExpandingCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExpandingCard)
{
    ui->setupUi(this);

    btn = new ExpandButton(QPixmap(":/drop-down.png"));
    this->layout()->addWidget(btn);

    connect(btn, &QPushButton::clicked, this, &ExpandingCard::toggle);

    _previewHeight= this->sizeHint().height();
    _expandedHeight = this->sizeHint().height() + ui->scrollArea->sizeHint().height();
}

ExpandingCard::~ExpandingCard()
{
    delete ui;
}

void ExpandingCard::toggle()
{
    static bool expanded = false;

    QPropertyAnimation *anim = new QPropertyAnimation(this, "geometry");
    anim->setStartValue(this->geometry());
    QRect endRect = this->geometry();
    endRect.setHeight(expanded ? _previewHeight : _expandedHeight);
    anim->setEndValue(endRect);
    anim->setDuration(300);

    anim->start();
    expanded = !expanded;
}

/*void ExpandingCard::on_pushButton_clicked()

{

}*/
