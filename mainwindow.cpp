#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("更新工具"));
    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    toolBar = new QToolBar(this);
    addToolBar(toolBar);
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    mainLayout = new QGridLayout(centralWidget);

    update_tool = new updateTool(this);

    getVersionInfoPushButton = new QPushButton(tr("校验版本"));
    getUpdatePushButton = new QPushButton(tr("更新程序"));
    restartPushButton = new QPushButton(tr("重启程序"));

    getUpdatePushButton->setEnabled(false);
    restartPushButton->hide();

    downloadProgressBar = new QProgressBar;
    downloadProgressBar->hide();


//    QMessageBox restartBox = new QMessageBox;

    mainLayout->addWidget(getVersionInfoPushButton,0,0);
    mainLayout->addWidget(getUpdatePushButton,1,0);
    mainLayout->addWidget(restartPushButton,2,0);

    mainLayout->addWidget(downloadProgressBar,1,1);

    connect(getVersionInfoPushButton, SIGNAL(clicked()), this, SLOT(doVersionInfo()));
    connect(getUpdatePushButton, SIGNAL(clicked()), this, SLOT(doUpdate()));
    connect(restartPushButton, SIGNAL(clicked()), this, SLOT(doRestart()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::doVersionInfo()
{
    update_tool->getVersionInfo();
    connect(update_tool, SIGNAL(getVersionInfoFinishedSignal()), this, SLOT(checkVersionFlag()));
}

void MainWindow::checkVersionFlag()
{
    if (update_tool->getVersionFlag())
    {
        getUpdatePushButton->setEnabled(true);
    }
}

void MainWindow::doUpdate()
{
    downloadProgressBar->setValue(0);
    downloadProgressBar->show();
    update_tool->getUpdate();
    connect(update_tool->getUpdateUrlReply(), SIGNAL(downloadProgress(qint64, qint64)),
     this, SLOT(updateDataReadProgress(qint64, qint64)));
    connect(update_tool, SIGNAL(getUpdateFinishedSignal()), this, SLOT(checkUpdateFlag()));

}
void MainWindow::checkUpdateFlag()
{
    if (update_tool->getUpdateFlag())
    {
        downloadProgressBar->hide();
        restartPushButton->show();
        update_tool->restartProj();
    }
}

void MainWindow::doRestart()
{
    update_tool->restartProj();
}

void MainWindow::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    downloadProgressBar->setMaximum(totalBytes);
    downloadProgressBar->setValue(bytesRead);
}
