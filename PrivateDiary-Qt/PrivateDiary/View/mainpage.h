#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <memory>
#include <QObject>
#include <QTextCharFormat>
#include <QAction>
#include <QTextEdit>
#include <QWidget>
#include <QModelIndex>
#include <QIcon>

#include "ui_mainwindow.h"

#include "Model/DataStructure/appdata.h"
#include "Model/DataStructure/post.h"
#include "Model/DataStructure/constant.h"
#include "Presenter/postpresenter.h"
#include "View/ViewModel/postmodel.h"
#include "Util/crypter.h"



class MainPage : public QObject
{
    Q_OBJECT
public:
    explicit MainPage(QObject *parent = nullptr);
    ~MainPage();
    void setUi(Ui::MainWindow *ui);
    void setupToolbar();
    void setupPage(std::shared_ptr<AppData> appData);
    void setupTextActions();

private:
    Ui::MainWindow *ui;
    PostPresenter *postPresenter;
    PostModel *postModel;
    std::shared_ptr<AppData> appData;
    Post currentPost;
    QModelIndex currentIndex;

    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
    void alignmentChanged(Qt::Alignment a);
    void fontChanged(const QFont &f);
    void colorChanged(const QColor &c);

private slots:
    // text formatters
    void textBold();
    void textItalic();
    void textUnderline();
    void textAlign(QAction *a);

    void cursorPositionChanged();
    void currentCharFormatChanged(const QTextCharFormat &format);

    // model
    void feedClicked(const QModelIndex &index);
    void addPost();
    void updatePost();
};

#endif // MAINPAGE_H
