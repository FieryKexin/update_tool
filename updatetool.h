#ifndef UPDATETOOL_H
#define UPDATETOOL_H

#include <QMainWindow>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFile>
#include <QUrl>
#include <QFileInfo>
#include <QString>
#include <QStringList>
#include <QProcess>
#include <QMap>

#include <QByteArray>
#include <QTextStream>
#include <QProgressBar>
#include <QDebug>
#include <QApplication>
#include <QTimer>

#include "rapidjson/document.h"
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#define TEMP_DIR "/home/kexin_zhu/workspace/download_file/"

class updateTool : public QObject
{
    Q_OBJECT

public:
    updateTool(QMainWindow* amainWindow);
    ~updateTool();

    void getVersionInfo();
    void getUpdate();
    void restartProj();

    QProgressBar *downloadProgressBar;
    bool versionFlag;
    bool updateFlag;

private:
    QMainWindow *mainWindow;
    QEventLoop loop;

    QUrl versionUrl;
    QFileInfo versionUrlInfo;
    QString versionUrlFileName;
    QFile *versionUrlFile;
    QNetworkAccessManager *versionUrlManager;
    QNetworkReply *versionUrlReply;
    QNetworkRequest versionUrlRequest;
    QString updateVersion;
    QString localVersion;

    QUrl secretUrl;
    QFileInfo secretUrlInfo;
    QString secretUrlFileName;
    QFile *secretUrlFile;
    QNetworkAccessManager *secretUrlManager;
    QNetworkReply *secretUrlReply;
    QNetworkRequest secretUrlRequest;
    QString secret;

    QUrl updateUrl;
    QFileInfo updateUrlInfo;
    QString updateUrlFileName;
    QFile *updateUrlFile;
    QNetworkAccessManager *updateUrlManager;
    QNetworkReply *updateUrlReply;
    QNetworkRequest updateUrlRequest;

    QString versionInfoValue;
    bool downloadValue;
    bool setupValue;
    bool restartedValue;
    QFile *updateInfoJsonDocFile;

private slots:
    void getVersionInfoFinished(QNetworkReply *);
    void generateSecretFinished(QNetworkReply *);
    void getUpdateFinished(QNetworkReply *);
    void updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);
private:
    void updateProj();
    void runShell();
    void getUpdateJson();
signals:
    void getVersionInfoFinishedSignal();
    void getUpdateFinishedSignal();
};

#endif // UPDATETOOL_H
