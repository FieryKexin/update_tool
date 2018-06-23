#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "aq_version_manager.h"

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
#include <QMessageBox>
#include <QDebug>
#include <QEventLoop>

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

    aq::versionManager *version_manager;
    QProgressBar *downloadProgressBar;


private slots:
    void doVersionInfo();
    void doUpdate();
    void doRestart();

    void checkVersionFlag();
    void checkUpdateFlag();
    void updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);
};

#endif // MAINWINDOW_H
