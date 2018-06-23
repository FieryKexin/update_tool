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

    version_manager = new aq::versionManager(this);

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
    version_manager->getVersionInfo();
    connect(version_manager, SIGNAL(getVersionInfoFinishedSignal()), this, SLOT(checkVersionFlag()));
}

void MainWindow::checkVersionFlag()
{
    if (version_manager->getVersionFlag())
    {
        getUpdatePushButton->setEnabled(true);
    }
}

void MainWindow::doUpdate()
{
    downloadProgressBar->setValue(0);
    downloadProgressBar->show();
    version_manager->getUpdate();
    connect(version_manager->getUpdateUrlReply(), SIGNAL(downloadProgress(qint64, qint64)),
     this, SLOT(updateDataReadProgress(qint64, qint64)));
    connect(version_manager, SIGNAL(getUpdateFinishedSignal()), this, SLOT(checkUpdateFlag()));

}
void MainWindow::checkUpdateFlag()
{
    if (version_manager->getUpdateFlag())
    {
        downloadProgressBar->hide();
        restartPushButton->show();
        version_manager->restartProj();
    }
}

void MainWindow::doRestart()
{
    version_manager->restartProj();
}

void MainWindow::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    downloadProgressBar->setMaximum(totalBytes);
    downloadProgressBar->setValue(bytesRead);
}
