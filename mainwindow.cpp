#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include "pqxx/pqxx"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_c(std::make_shared<pqxx::connection>("host=localhost "
                                              "dbname=bugtracker "
                                              "user=postgres "
                                              "password=changeme")) ,
      add(nullptr) {

  ui->setupUi(this);
  /*
  pqxx::work txn{*m_c};
  txn.exec("INSERT INTO bugs(name, priority, comment) VALUES (" +
           txn.quote("test") + ", " + txn.quote("1") + ", 'test');");
  txn.commit();
*/
  // Wypełnij model danymi
  /*
  for (int row = 0; row < 5; ++row) {
    for (int column = 0; column < 3; ++column) {
      QModelIndex index = m_model->index(row, column, QModelIndex());
      m_model->setData(index, QVariant((row + 1) * (column + 1)));
    }
  }
*/
  updateModel(this);
  ui->tableView->setModel(m_model);
  ui->tableView->hideColumn(4);

  ui->splitter->setSizes({800, 200});

         // ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_pushButton_clicked() {
  if (!add){
    add = new Add(this);
  }
  add->show();
  /*
  m_model->insertRow(m_model->rowCount());

  for (int column{0}; column < m_model->columnCount(); ++column) {
    QModelIndex index{m_model->index(m_model->rowCount() - 1, column)};
    m_model->setData(index, QVariant((m_model->rowCount()) * (column + 1)));
  }
*/
}

void MainWindow::on_pushButton_2_clicked() {
  QModelIndex selectedIndex = ui->tableView->currentIndex();
  if (selectedIndex.isValid()) {
    m_model->removeRow(selectedIndex.row());
  } else
    m_model->removeRows(m_model->rowCount() - 1, 1);
}

void MainWindow::on_tableView_clicked(const QModelIndex& index) {
  QString col1{m_model->data(m_model->index(index.row(), 1)).toString()};
  ui->label->setText(col1);

  QString col2{m_model->data(m_model->index(index.row(), 2)).toString()};
  ui->label_2->setText(col2);

  QString col3{m_model->data(m_model->index(index.row(), 3)).toString()};
  ui->label_3->setText(col3);

  QString comment{m_model->data(m_model->index(index.row(), 4)).toString()};
  ui->mCommentEdit->setText(comment);
}

void updateModel(MainWindow* w){
  pqxx::work txn{*w->m_c};
  pqxx::result result{txn.exec("SELECT id, name, priority, time, comment FROM bugs")};
  w->m_model->clear();
  for (const auto& row : result) {
    QList<QStandardItem*> rowData;
    for (const auto& field : row) {
      QString value = QString::fromStdString(field.c_str());
      rowData.append(new QStandardItem(value));
    }
    w->m_model->appendRow(rowData);
  }
}

/*
void MainWindow::on_pushButton_3_clicked()
{
  pqxx::work txn{c};
  txn.exec("INSERT INTO Messages(username, message) VALUES ( hej, siemasz);");
  txn.commit();
}
*/
