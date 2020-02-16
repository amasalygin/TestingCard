#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "card.h"
#include "form.h"
#include "expandingcard.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ExpandingCard *card = new ExpandingCard();
    ui->gridLayout->addWidget(card);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}
