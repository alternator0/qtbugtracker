#include "mainwindow.h"
#include "./ui_mainwindow.h"
//#include"pqxx/pqxx"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
 // 5 wierszy i 3 kolumny

         // Wypełnij model danymi
  for (int row = 0; row < 5; ++row) {
    for (int column = 0; column < 3; ++column) {
      QModelIndex index = m_model->index(row, column, QModelIndex());
      m_model->setData(index, QVariant((row+1) * (column+1)));
    }
  }

  ui->tableView->setModel(m_model);

  ui->splitter->setSizes({800,200});

  //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked()
{
  m_model->insertRow(m_model->rowCount());
  for (int column {0}; column < m_model->columnCount(); ++column) {
    QModelIndex index {m_model->index(m_model->rowCount() - 1, column)};
    m_model->setData(index ,QVariant((m_model->rowCount()) * (column+1)));
  }

}


void MainWindow::on_pushButton_2_clicked()
{
  QModelIndex selectedIndex = ui->tableView->currentIndex();
  if (selectedIndex.isValid()) {
    m_model->removeRow(selectedIndex.row());
  } else m_model->removeRows(m_model->rowCount()-1,1);
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
  QString col1 {m_model->data(m_model->index(index.row(), 0)).toString()};
  ui->label->setText(col1);

  QString col2 {m_model->data(m_model->index(index.row(), 1)).toString()};
  ui->label_2->setText(col2);

  QString col3 {m_model->data(m_model->index(index.row(), 2)).toString()};
  ui->label_3->setText(col3);

  ui->lineEdit->setText("tset");


}

/*
void MainWindow::on_pushButton_3_clicked()
{
  pqxx::work txn{c};
  txn.exec("INSERT INTO Messages(username, message) VALUES ( hej, siemasz);");
  txn.commit();
}
*/

