#ifndef MENUADMIN_H
#define MENUADMIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MenuAdmin;
}
QT_END_NAMESPACE

class MenuAdmin : public QMainWindow
{
    Q_OBJECT

public:
    MenuAdmin(QWidget *parent = nullptr);
    ~MenuAdmin();

private slots:
    void onBackToLoginClicked();

private:
    Ui::MenuAdmin *ui;
};

#endif // MENUADMIN_H
