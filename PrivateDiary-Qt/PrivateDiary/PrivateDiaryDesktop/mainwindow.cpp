#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();
    ui->menuBar->hide();

    appData = std::make_shared<AppData>();
    loginPage = new LoginPage(this);
    loginPage->setAppData(appData);

    connect(ui->btnRegistration, &QPushButton::clicked, this, &MainWindow::registration);
    connect(ui->btnAuth, &QPushButton::clicked, this, &MainWindow::auth);

    // menu
    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::showCredentialDialog);
    connect(ui->actionDownload_Database, &QAction::triggered, this, &MainWindow::downloadDatabase);
    connect(ui->actionUpload_Database, &QAction::triggered, this, &MainWindow::uploadDatabase);
    connect(ui->actionLogout, &QAction::triggered, this, &MainWindow::exit);

//    ui->stackedWidget->setCurrentIndex(Pages::Main);
//    setupMainPage();
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

void MainWindow::showCredentialDialog()
{
    CredentialDialog dialog(this);

    if (dialog.exec() != QDialog::Accepted) {
        return;
    }
    if (loginPage->updateCredentioals(dialog.getLogin(), dialog.getPassword())) {
        QMessageBox::information(this, tr("Information"), tr("Restart application please."));
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Update credentials error."));
    }
}

void MainWindow::downloadDatabase()
{
    QString homePath = QDir::homePath();
    QString dir = QFileDialog::getExistingDirectory(this, tr("Directory for save"), homePath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    QFile::copy(Constant::dbPath, dir + "/" + Constant::dbName);
}

void MainWindow::uploadDatabase()
{
    QString homePath = QDir::homePath();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Database for upload"), homePath, "*.dbx");

    QFile::copy(fileName, Constant::dbPath);
    mainPage->refresh();
}

void MainWindow::exit()
{
    ui->leUsername->clear();
    ui->lePassword->clear();
    ui->stackedWidget->setCurrentIndex(Pages::Login);
}

