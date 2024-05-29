#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
//#include "pqxx/pqxx"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

  void on_tableView_clicked(const QModelIndex &index);

  //void on_pushButton_3_clicked();

private:
  Ui::MainWindow *ui;
  QStandardItemModel *m_model = new QStandardItemModel(5, 3);
  /*
  pqxx::connection c{
                     "host=localhost "
                     "dbname=chat "
                     "user=admin "
                     "password=changeme"};
*/
};
#endif // MAINWINDOW_H
