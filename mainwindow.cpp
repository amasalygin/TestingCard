#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "card.h"
#include "form.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    for(int i =0; i<3; i++)
        for(int j = 0; j < 3; j++)
    {
        ContainerWidget *base = new ContainerWidget;
        base->setGraphicsEffect(new QGraphicsBlurEffect);
        Form *overlay = new Form(base, this);
        overlay->setObjectName(QString("Card %1 %2").arg(i).arg(j));
        ui->gridLayout->addWidget(base, i,j );
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
