#ifndef MENURECEPCIONISTA_H
#define MENURECEPCIONISTA_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MenuRecepcionista;
}
QT_END_NAMESPACE

class MenuRecepcionista : public QMainWindow
{
    Q_OBJECT

public:
    MenuRecepcionista(QWidget *parent = nullptr);
    ~MenuRecepcionista();

private slots:
    void onBackToLoginClicked();

private:
    Ui::MenuRecepcionista *ui;
};

#endif // MENURECEPCIONISTA_H
