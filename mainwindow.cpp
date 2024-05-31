#include <string>
#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include "pqxx/pqxx"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_c(std::make_shared<pqxx::connection>("host=localhost "
                                             "dbname=bugtracker "
                                             "user=postgres "
                                             "password=changeme")),
      add(nullptr) {
  ui->setupUi(this);

  setWindowTitle("Bugtracker");

  ui->tableView->setModel(m_model);
  updateModel(this);

  ui->splitter->setSizes({800, 200});
}

const int MainWindow::getIndexOfSelectedBug() {
  QModelIndex selectedIndex = ui->tableView->currentIndex();
  return m_model->data(selectedIndex.sibling(selectedIndex.row(), 0)).toInt();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_pushButton_clicked() {
  if (!add) {
    add = new Add(this);
  }
  add->show();
}

void MainWindow::on_pushButton_2_clicked() {
  QModelIndex selectedIndex = ui->tableView->currentIndex();
  if (selectedIndex.isValid()) {
    pqxx::work txn{*m_c};
    txn.exec("DELETE FROM bugs WHERE id = " +
             txn.quote(getIndexOfSelectedBug()) + ";");
    m_model->removeRow(selectedIndex.row());
    txn.commit();
  }
}

void MainWindow::on_tableView_clicked(const QModelIndex& index) {
  QString name{m_model->data(m_model->index(index.row(), 1)).toString()};
  ui->label->setText(name);

  QString time{m_model->data(m_model->index(index.row(), 3)).toString()};
  ui->label_2->setText(time);

  int priority{m_model->data(m_model->index(index.row(), 2)).toInt()};
  ui->spinBox->setValue(priority);

  QString comment{m_model->data(m_model->index(index.row(), 4)).toString()};
  ui->mCommentEdit->setText(comment);
}

void updateModel(MainWindow* w) {
  pqxx::work txn{*w->m_c};
  pqxx::result result{
                      txn.exec("SELECT id, name, priority, time, comment FROM bugs")};
  w->m_model->clear();

         // filling model with data from database
  for (const auto& row : result) {
    QList<QStandardItem*> rowData;
    for (const auto& field : row) {
      QString value = QString::fromStdString(field.c_str());
      rowData.append(new QStandardItem(value));
    }
    w->m_model->appendRow(rowData);
  }
  // hiding comment column
  w->ui->tableView->hideColumn(4);

  w->ui->tableView->setColumnWidth(0, 20);
  w->ui->tableView->setColumnWidth(1, 570);
  w->ui->tableView->setColumnWidth(2, 50);
  w->m_model->setHeaderData(0, Qt::Horizontal, "ID");
  w->m_model->setHeaderData(1, Qt::Horizontal, "Name");
  w->m_model->setHeaderData(2, Qt::Horizontal, "Priority");
  w->m_model->setHeaderData(3, Qt::Horizontal, "Time");
}

void MainWindow::on_actionUpdate_triggered() {
  updateModel(this);
}

void MainWindow::on_pushButton_3_clicked() {
  pqxx::work txn{*m_c};
  txn.exec(
      "UPDATE bugs SET name =" + txn.quote(ui->label->text().toStdString()) +
      ", priority = " + txn.quote(ui->spinBox->value()) + ", comment = " +
      txn.quote(ui->mCommentEdit->toPlainText().toStdString()) +
      " WHERE id = " + txn.quote(getIndexOfSelectedBug()) + ";");
  txn.commit();
  updateModel(this);
}

void MainWindow::on_actionExit_triggered() {
  close();
}
