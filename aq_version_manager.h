#ifndef AQVERSIONMANAGER_H
#define AQVERSIONMANAGER_H

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

#include <QByteArray>
#include <QTextStream>
#include <QDebug>
#include <QApplication>
#include <QTimer>

#include "rapidjson/document.h"
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#define TEMP_DIR "/Users/zkxin/Desktop/project/update_tool/download_file/"
namespace aq{
class versionManager : public QObject
{
    Q_OBJECT

public:
    versionManager(QMainWindow* amainWindow);
    ~versionManager();

    void getVersionInfo();
    void getUpdate();
    void restartProj();

    bool getVersionFlag();
    bool getUpdateFlag();

    QNetworkReply * getUpdateUrlReply();


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

    bool versionFlag;
    bool updateFlag;

private slots:
    void getVersionInfoFinished(QNetworkReply *);
    void generateSecretFinished(QNetworkReply *);
    void getUpdateFinished(QNetworkReply *);

private:
    void updateProj();
    void runShell();
    void getUpdateJson();
signals:
    void getVersionInfoFinishedSignal();
    void getUpdateFinishedSignal();
};
}

#endif // AQVERSIONMANAGER_H
