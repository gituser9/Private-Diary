#include "mainpage.h"
#include <QDebug>
#include <QDateTime>

MainPage::MainPage(QObject *parent) : QObject(parent)
{
    postPresenter = new PostPresenter(this);
    postModel = new PostModel(this);
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::setUi(Ui::MainWindow *ui)
{
    this->ui = ui;
}

void MainPage::setupToolbar()
{
    ui->mainToolBar->show();
    ui->actionBold->setCheckable(true);
    ui->actionItalic->setCheckable(true);
    ui->actionUnderline->setCheckable(true);
    ui->actionTextLeft->setCheckable(true);
    ui->actionTextCenter->setCheckable(true);
    ui->actionTextRight->setCheckable(true);
    ui->actionTextJustify->setCheckable(true);
}

void MainPage::setupPage(std::shared_ptr<AppData> appData)
{
    this->appData = appData;
    postPresenter->setAppData(appData);

    setupToolbar();
    setupTextActions();

    ui->menuBar->show();

    ui->btnAddPost->setIcon(QIcon(":/Images/add.png"));
    ui->btnAddPost->setIconSize(QSize(20, 20));

    ui->btnDeletePost->setIcon(QIcon(":/Images/delete.png"));
    ui->btnDeletePost->setIconSize(QSize(20, 20));
    ui->btnDeletePost->setEnabled(false);

    ui->leTitle->hide();
    ui->textEdit->hide();
    ui->splitter->setStretchFactor(1,1);

    postModel->resetData(postPresenter->getAll());

    ui->lvTitleList->setModel(postModel);
    ui->lvTitleList->setDragDropMode(QAbstractItemView::InternalMove);

}

void MainPage::setupTextActions()
{
    connect(ui->textEdit, &QTextEdit::currentCharFormatChanged, this, &MainPage::currentCharFormatChanged);
    connect(ui->textEdit, &QTextEdit::cursorPositionChanged, this, &MainPage::cursorPositionChanged);

    connect(ui->actionBold, &QAction::triggered, this, &MainPage::textBold);
    connect(ui->actionItalic, &QAction::triggered, this, &MainPage::textItalic);
    connect(ui->actionUnderline, &QAction::triggered, this, &MainPage::textUnderline);

    connect(ui->lvTitleList, &QListView::clicked, this, &MainPage::feedClicked);
    connect(ui->btnAddPost, &QPushButton::clicked, this, &MainPage::addPost);
    connect(ui->btnDeletePost, &QPushButton::clicked, this, &MainPage::deletePost);
    connect(ui->textEdit, &QTextEdit::textChanged, this, &MainPage::updatePost);
    connect(ui->leTitle, &QLineEdit::textChanged, this, &MainPage::updatePost);

    auto *alignGroup = new QActionGroup(this);
    alignGroup->addAction(ui->actionTextLeft);
    alignGroup->addAction(ui->actionTextCenter);
    alignGroup->addAction(ui->actionTextRight);
    connect(alignGroup, &QActionGroup::triggered, this, &MainPage::textAlign);
}

void MainPage::refresh()
{
    postModel->resetData(postPresenter->getAll());
}

void MainPage::textBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(ui->actionBold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
}

void MainPage::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(ui->actionItalic->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void MainPage::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(ui->actionUnderline->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void MainPage::textAlign(QAction *a)
{
    if (a == ui->actionTextLeft) {
        ui->textEdit->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    }
    else if (a == ui->actionTextCenter) {
        ui->textEdit->setAlignment(Qt::AlignHCenter);
    }
    else if (a == ui->actionTextRight) {
        ui->textEdit->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    }
    else if (a == ui->actionTextJustify) {
        ui->textEdit->setAlignment(Qt::AlignJustify);
    }
}

void MainPage::cursorPositionChanged()
{
    alignmentChanged(ui->textEdit->alignment());
}

void MainPage::currentCharFormatChanged(const QTextCharFormat &format)
{
    fontChanged(format.font());
    colorChanged(format.foreground().color());
}

void MainPage::feedClicked(const QModelIndex &index)
{
    ui->btnDeletePost->setEnabled(true);

    currentIndex = index;
    currentPost = postModel->getItem(index);
    Post post = postPresenter->getPost(currentPost.id);

    ui->leTitle->show();
    ui->leTitle->setText(post.title);
    ui->textEdit->show();

    if (post.body.isEmpty()) {
        ui->textEdit->clear();
    } else {
        ui->textEdit->setText(post.body);
    }

}

void MainPage::addPost()
{
    if (postPresenter->createPost(Constant::defaultTitle, QString())) {
        postModel->resetData(postPresenter->getAll());
    }
}

void MainPage::updatePost()
{
    usleep(1000);
    postPresenter->updatePost(ui->leTitle->text(), ui->textEdit->toHtml(), currentPost.id);

    if (ui->leTitle->text() != currentPost.title) {
        currentPost.title = ui->leTitle->text();
        postModel->updateTitle(currentPost.id, ui->leTitle->text(), currentIndex);
    }
}

void MainPage::deletePost()
{
    if (postPresenter->deletePost(currentPost.id)) {
        postModel->resetData(postPresenter->getAll());
        ui->btnDeletePost->setEnabled(false);
    }
}

void MainPage::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
}

void MainPage::alignmentChanged(Qt::Alignment a)
{
    if (a & Qt::AlignLeft) {
        ui->actionTextLeft->setChecked(true);
    }
    else if (a & Qt::AlignHCenter) {
        ui->actionTextCenter->setChecked(true);
    }
    else if (a & Qt::AlignRight) {
        ui->actionTextRight->setChecked(true);
    }
    else if (a & Qt::AlignJustify) {
        ui->actionTextJustify->setChecked(true);
    }
}

void MainPage::fontChanged(const QFont &f)
{
    ui->actionBold->setChecked(f.bold());
    ui->actionItalic->setChecked(f.italic());
    ui->actionUnderline->setChecked(f.underline());
}

void MainPage::colorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    pix.fill(c);
}

