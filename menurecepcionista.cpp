#include "menurecepcionista.h"
#include "menurecepcionista.h"
#include "mainmenu.h"


MenuRecepcionista::~MenuRecepcionista()
{
    delete ui;
}

void MenuRecepcionista::onBackToLoginClicked()
{
    MainMenu *loginWindow = new MainMenu();
    loginWindow->show();
    this->close();
}
