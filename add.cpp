#include "add.h"
#include "ui_add.h"
#include "mainwindow.h"

Add::Add(QWidget *parent) : QDialog(parent), ui(new Ui::Add){
  ui->setupUi(this);
  ui->nameEdit->setPlaceholderText("Name");
  ui->commentEdit->setPlaceholderText("Comment goes here");
}

Add::~Add() { delete ui; }

void Add::on_buttonBox_accepted()
{
  MainWindow* parentWindow{qobject_cast<MainWindow *>(parent())};
  pqxx::work txn{*parentWindow->getConnection()};
  txn.exec("INSERT INTO bugs(name, priority, comment) VALUES (" + txn.quote(ui->nameEdit->text().toUtf8().constData()) +
           ", " + txn.quote(ui->spinBox->text().toUtf8().constData()) + ", " + txn.quote(ui->commentEdit->toPlainText().toUtf8().constData())+ ");");
  txn.commit();
  updateModel(parentWindow);
}
