#include "menudoctor.h"
#include "menudoctor.h"
#include "mainmenu.h"


MenuDoctor::~MenuDoctor()
{
    delete ui;
}

void MenuDoctor::onBackToLoginClicked()
{
    MainMenu *loginWindow = new MainMenu();
    loginWindow->show();
    this->close();
}
