#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("update_tool");
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

    getVersionInfoPushButton = new QPushButton("version");
    getUpdatePushButton = new QPushButton("update");
    restartPushButton = new QPushButton("restart");

    getUpdatePushButton->setEnabled(false);
    restartPushButton->hide();

    mainLayout->addWidget(getVersionInfoPushButton,0,0);
    mainLayout->addWidget(getUpdatePushButton,1,0);
    mainLayout->addWidget(restartPushButton,2,0);

    mainLayout->addWidget(update_tool->downloadProgressBar,1,1);

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
    if (update_tool->versionFlag)
    {
        getUpdatePushButton->setEnabled(true);
    }
}

void MainWindow::doUpdate()
{
    update_tool->getUpdate();
    connect(update_tool, SIGNAL(getUpdateFinishedSignal()), this, SLOT(checkUpdateFlag()));
}
void MainWindow::checkUpdateFlag()
{
    if (update_tool->updateFlag)
    {
        restartPushButton->show();
    }
}

void MainWindow::doRestart()
{
    update_tool->restartProj();
}


