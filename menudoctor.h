// menuadoctor.h
#ifndef MENUDOCTOR_H
#define MENUDOCTOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MenuDoctor;
}
QT_END_NAMESPACE

class MenuDoctor : public QMainWindow
{
    Q_OBJECT

public:
    MenuDoctor(QWidget *parent = nullptr);
    ~MenuDoctor();

private slots:
    void onBackToLoginClicked();

private:
    Ui::MenuDoctor *ui;
};

#endif // MENUADOCTOR_H
