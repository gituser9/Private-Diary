#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();

    appData = std::make_shared<AppData>();
    loginPage = new LoginPage(this);
    loginPage->setAppData(appData);

    connect(ui->btnRegistration, &QPushButton::clicked, this, &MainWindow::registration);
    connect(ui->btnAuth, &QPushButton::clicked, this, &MainWindow::auth);

    ui->stackedWidget->setCurrentIndex(Pages::Main);
    setupMainPage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupMainPage()
{

    appData->setUserPassword(ui->lePassword->text());

    mainPage = new MainPage(this);
    mainPage->setUi(ui);
    mainPage->setupPage(appData);
}

void MainWindow::registration()
{
    if (loginPage->registration(ui->leUsername->text(), ui->lePassword->text())) {
        ui->stackedWidget->setCurrentIndex(Pages::Main);
        setupMainPage();
    }
}

void MainWindow::auth()
{
    if (loginPage->auth(ui->leUsername->text(), ui->lePassword->text())) {
        ui->stackedWidget->setCurrentIndex(Pages::Main);
        setupMainPage();
    }
}

