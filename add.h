#ifndef ADD_H
#define ADD_H

#include <QDialog>
#include "pqxx/pqxx"

namespace Ui {
class Add;
}

class Add : public QDialog {
  Q_OBJECT

public:
  explicit Add(QWidget *parent = nullptr);
  ~Add();

private slots:
  void on_buttonBox_accepted();

private:
  Ui::Add *ui;
};

#endif // ADD_H
