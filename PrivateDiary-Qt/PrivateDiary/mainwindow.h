#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include "View/loginpage.h"
#include "View/mainpage.h"

#include "Model/DataStructure/appdata.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    enum Pages {
        Login,
        Main,
        None
    };

    LoginPage *loginPage;
    MainPage *mainPage;
    std::shared_ptr<AppData> appData;

    void setupMainPage();


private slots:
    void registration();
    void auth();

};

#endif // MAINWINDOW_H
