#ifndef CARD_H
#define CARD_H


#include <QtGui>
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
#include <QtWidgets>
#endif
#include <QDebug>
#include <QPaintEvent>

class OverlayWidget : public QWidget {
   void newParent() {
      if (!_container) return;
      _container->installEventFilter(this);
      raise();
   }
public:
   explicit OverlayWidget(QWidget *container, QWidget *parent) : QWidget(parent) {
      _container = container;
      newParent();
   }

protected:
   QWidget *_container;
   //! Catches resize and child events from the parent widget
   bool eventFilter(QObject *obj, QEvent *ev) override {
      if (obj == _container) {
         if (ev->type() == QEvent::Resize)
         {
             this->setGeometry(_container->pos().x(), _container->pos().y(), _container->width(), _container->height());
         }
         else if (ev->type() == QEvent::ChildAdded)
         {
            raise();
         }

      }

      QWidget::eventFilter(obj, ev);
   }
};

class ContainerWidget : public QWidget
{
public:
   explicit ContainerWidget(QWidget *parent = {}) : QWidget(parent) { setStyleSheet("background-color: rgba(0,0,0,50)");}
   void setSize(QObject *obj) {
      if (obj->isWidgetType()) static_cast<QWidget*>(obj)->setGeometry(rect());
   }
protected:
   //! Resizes children to fill the extent of this widget
   bool event(QEvent *ev) override {
      if (ev->type() == QEvent::ChildAdded) {
         setSize(static_cast<QChildEvent*>(ev)->child());
      }
      return QWidget::event(ev);
   }
   //! Keeps the children appropriately sized
   void resizeEvent(QResizeEvent *) override {
      for(auto obj : children()) setSize(obj);
   }
};

class LoadingOverlay : public OverlayWidget
{
public:
   LoadingOverlay(QWidget *container, QWidget *parent = {}) : OverlayWidget{container, parent} {
      setAttribute(Qt::WA_TranslucentBackground);
   }
};

#endif // CARD_H
