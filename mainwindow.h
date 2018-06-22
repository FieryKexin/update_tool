#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "updatetool.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QWidget>
#include <QStatusBar>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>

#include <QDebug>


#define TEMP_DIR "/Users/zkxin/Desktop/project/update_tool/download_file/"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QMenuBar *menuBar;
    QToolBar *toolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    QGridLayout *mainLayout;

    QPushButton *getVersionInfoPushButton;
    QPushButton *getUpdatePushButton;
    QPushButton *restartPushButton;

    updateTool *update_tool;



private slots:
    void doVersionInfo();
    void doUpdate();
    void doRestart();

    void checkVersionFlag();
    void checkUpdateFlag();
};

#endif // MAINWINDOW_H
