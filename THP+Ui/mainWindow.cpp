#include "mainWindow.h"
#include "ui_mainWindow.h"
#include "Encoding.h"
#include "Decoding.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_compressButton_clicked()
{
    QString ioFileName[2];
    ioFileName[0] = ui->lineEdit->text();
    ioFileName[1] = "oName";
    encoding(ioFileName);
}

void MainWindow::on_decompressButton_clicked()
{
    QString ioFileName[2];
    ioFileName[0] = ui->lineEdit->text();
    ioFileName[1] = "oName";
    decoding(ioFileName);
}

void MainWindow::on_exitButton_clicked()
{
    this->close();
}
