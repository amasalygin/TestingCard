#ifndef EXPANDINGCARD_H
#define EXPANDINGCARD_H

#include <QWidget>
#include <QPushButton>
#include <QtGui>
#include <QDebug>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QVariantAnimation>
#include <QPainter>
#include <QTimer>

class ExpandButton : public QPushButton{
    Q_OBJECT
public:
    friend class ExpandingCard;

    explicit ExpandButton(QPixmap p, QWidget *parent = nullptr) : QPushButton(parent) {
        pixmap = p.scaled(iconSize(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        orig = p.scaled(iconSize(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        setText("");
        expanded = false;

        anim = new QVariantAnimation(this);
        anim->setDuration(300);
        anim->setEasingCurve(QEasingCurve::OutExpo);
        connect(anim, &QVariantAnimation::valueChanged, this, [=] (const QVariant &value){
            QMatrix rm;
            rm.rotate(value.toReal());
            pixmap = orig.transformed(rm).scaled(iconSize(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            update();
        });

        connect(this, &QPushButton::clicked, this, [=] (){
            expanded = !expanded;
            anim->setStartValue(expanded ? 0.0f : 180.0f);
            anim->setEndValue(expanded ? 180.0f : 0.0f);
            anim->start();
        });


    }
protected:


    void paintEvent(QPaintEvent *ev) override
    {
        QPushButton::paintEvent(ev);
        QPainter painter(this);

        //QPainter icon(&pixmap);
        //icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
        //icon.fillRect(pixmap.rect(), isEnabled() ? color() : disabledColor());

        QRect r(rect());
        const qreal w = pixmap.width();
        const qreal h = pixmap.height();
        painter.drawPixmap(QRect((r.width()-w)/2, (r.height()-h)/2, w, h), pixmap);
    }

private:
    QPixmap orig;
    QPixmap pixmap;
    QVariantAnimation *anim;
    bool expanded;
};

namespace Ui {
class ExpandingCard;
}

class ExpandingCard : public QWidget
{
    Q_OBJECT

public:
    explicit ExpandingCard(QWidget *parent = nullptr);
    ~ExpandingCard();

private slots:
    //void on_pushButton_clicked();

private:
    Ui::ExpandingCard *ui;

    ExpandButton *btn;

    void toggle();

    int _previewHeight;
    int _expandedHeight;
};

#endif // EXPANDINGCARD_H
