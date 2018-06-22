#include "updatetool.h"

updateTool::updateTool(QMainWindow* amainWindow)
{
    updateVersion = "";
    mainWindow = amainWindow;
    downloadProgressBar = new QProgressBar;
    downloadProgressBar->hide();
    versionFlag = false;
    updateFlag = false;
    versionInfoValue = "";
    downloadValue = false;
    setupValue = false;
    restartedValue = false;
}

updateTool::~updateTool()
{

}

void updateTool::getVersionInfo()
{
    localVersion = "2.0.1build1";
    versionUrl = "http://47.104.73.107:8880/api/v1/get_latest_version?version=" + localVersion;
    qDebug() << versionUrl;
    versionUrlInfo = versionUrl.path();
    versionUrlFileName = versionUrlInfo.fileName();
    if (versionUrlFileName.isEmpty()) versionUrlFileName = "get_latest_version";
    versionUrlFile = new QFile(TEMP_DIR + versionUrlFileName);
    versionUrlManager = new QNetworkAccessManager(mainWindow);
    versionUrlRequest.setUrl(versionUrl);
    versionUrlReply = versionUrlManager->get(versionUrlRequest);
    connect(versionUrlManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(getVersionInfoFinished(QNetworkReply *)));
}

void updateTool::getVersionInfoFinished(QNetworkReply *)
{
    if(!versionUrlFile->open(QIODevice::WriteOnly))
    {
        qDebug() << "versionUrlFile open error";
        delete versionUrlFile;
        versionUrlFile = 0;
        return;
     }
    if (versionUrlFile)
    {
        qDebug() << "versionUrlFile is writing";
        versionUrlFile->write(versionUrlReply->readAll());
    }
    qDebug() << "versionUrlFile is finished";
    versionUrlFile->flush();
    versionUrlFile->close();
    versionUrlReply->deleteLater();
    versionUrlReply = 0;

    if(!versionUrlFile->open(QIODevice::ReadOnly))
    {
        qDebug() << "could't open json versionUrlFile";
        return;
    }

    rapidjson::Document versionInfoJsonDoc;
    versionInfoJsonDoc.Parse(versionUrlFile->readAll().data());
    if (versionInfoJsonDoc.HasParseError())
    {
        qDebug() << "get versionInfoJsonDoc error";
        return;
    }
    versionUrlFile->close();

    if(versionInfoJsonDoc.HasMember("data"))
    {
        qDebug() << "need_update is " << versionInfoJsonDoc["data"]["need_update"].GetBool();

        if(versionInfoJsonDoc["data"]["need_update"].GetBool() == true && versionInfoJsonDoc["data"]["latest_version"].GetString() != localVersion)
        {
            qDebug() << "latest_version is " << versionInfoJsonDoc["data"]["latest_version"].GetString();
            updateVersion = versionInfoJsonDoc["data"]["latest_version"].GetString();
            qDebug() << (tr("当前不是最新版本， 最新版本号为") + updateVersion);
            versionInfoValue = updateVersion;
            versionFlag = true;
        }
        else
        {
            qDebug() << (tr("当前已是最新版本， 版本号为") + localVersion);
            versionInfoValue = localVersion;
            versionFlag = false;
        }
        getUpdateJson();
        emit getVersionInfoFinishedSignal();
    }
}

void updateTool::getUpdate()
{
    secretUrl = "http://47.104.73.107:8880/api/v1/generate_secret";
    qDebug() << secretUrl;
    secretUrlInfo = secretUrl.path();
    secretUrlFileName = secretUrlInfo.fileName();
    if (secretUrlFileName.isEmpty()) secretUrlFileName = "generate_secret";

    secretUrlFile = new QFile(TEMP_DIR + secretUrlFileName);
    secretUrlManager = new QNetworkAccessManager(mainWindow);

    secretUrlRequest.setUrl(secretUrl);
    secretUrlReply = secretUrlManager->post(secretUrlRequest, "sk=aqrose");

    connect(secretUrlManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(generateSecretFinished(QNetworkReply *)));
    loop.exec();

    updateUrl = "http://47.104.73.107:8880/api/v1/download_latest_version?secret=" + secret;
    qDebug() << updateUrl;
    updateUrlInfo = updateUrl.path();
    updateUrlFileName = updateUrlInfo.fileName() + ".zip";
    if (updateUrlFileName.isEmpty()) updateUrlFileName = "download_latest_version.zip";

    updateUrlFile = new QFile(TEMP_DIR + updateUrlFileName);
    updateUrlManager = new QNetworkAccessManager(mainWindow);

    updateUrlRequest.setUrl(updateUrl);
    updateUrlReply = updateUrlManager->get(updateUrlRequest);
    downloadProgressBar->setValue(0);
    downloadProgressBar->show();

    connect(updateUrlReply, SIGNAL(downloadProgress(qint64, qint64)),
     this, SLOT(updateDataReadProgress(qint64, qint64)));
    connect(updateUrlManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(getUpdateFinished(QNetworkReply *)));
}

void updateTool::generateSecretFinished(QNetworkReply *)
{
    if(!secretUrlFile->open(QIODevice::WriteOnly))
    {
        qDebug() << "secretUrlFile open error";
        delete secretUrlFile;
        secretUrlFile = 0;
        return;
     }
    if (secretUrlFile)
    {
        qDebug() << "secretUrlFile is writing";
        secretUrlFile->write(secretUrlReply->readAll());
    }
    qDebug() << "secretUrlFile is finished";
    secretUrlFile->flush();
    secretUrlFile->close();
    secretUrlReply->deleteLater();
    secretUrlReply = 0;

    if(!secretUrlFile->open(QIODevice::ReadOnly))
    {
        qDebug() << "could't open json secretUrlFile";
        return;
    }

    rapidjson::Document secretInfoJsonDoc;
    secretInfoJsonDoc.Parse(secretUrlFile->readAll().data());
    if (secretInfoJsonDoc.HasParseError())
    {
        qDebug() << "get secretInfoJsonDoc error";
        return;
    }
    secretUrlFile->close();

    if(secretInfoJsonDoc.HasMember("data"))
    {
        secret = secretInfoJsonDoc["data"]["secret"].GetString();
        qDebug() << "secret: " << secret;
    }
    loop.quit();
}

void updateTool::getUpdateFinished(QNetworkReply *)
{
    if(!updateUrlFile->open(QIODevice::WriteOnly))
    {
        qDebug() << "updateUrlFile open error";
        delete updateUrlFile;
        updateUrlFile = 0;
        return;
     }
    if (updateUrlFile)
    {
        qDebug() << "updateUrlFile is writing";
        updateUrlFile->write(updateUrlReply->readAll());
    }
    qDebug() << "updateUrlFile is finished";

    updateUrlFile->flush();
    updateUrlFile->close();
    updateUrlReply->deleteLater();
    updateUrlReply = 0;
    delete updateUrlFile;
    updateUrlFile = 0;
    downloadProgressBar->hide();
    downloadValue = true;
    getUpdateJson();
    updateFlag = true;
    updateProj();
    getUpdateJson();
    emit getUpdateFinishedSignal();   
}
void updateTool::runShell()
{
    QProcess::execute("sh " + QString(TEMP_DIR) + "../update.sh");
}

void updateTool::updateProj()
{
    runShell();
    setupValue = true;
}

void updateTool::getUpdateJson()
{
    updateInfoJsonDocFile = new QFile(QString(TEMP_DIR) + "../updateInfo.json");
    if(!updateInfoJsonDocFile->open(QIODevice::WriteOnly))
    {
        qDebug() << "updateInfojsonDocFile open error";
        delete updateInfoJsonDocFile;
        updateInfoJsonDocFile = 0;
        return;
    }

    rapidjson::StringBuffer strBuffer;
    rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(strBuffer);

    jsonWriter.StartObject();
    jsonWriter.Key("versionInfo");
    jsonWriter.String(versionInfoValue.toLatin1().data());
    jsonWriter.Key("download");
    jsonWriter.Bool(downloadValue);
    jsonWriter.Key("setup");
    jsonWriter.Bool(setupValue);
    jsonWriter.Key("restarted");
    jsonWriter.Bool(restartedValue);
    jsonWriter.EndObject();

    if (updateInfoJsonDocFile)
    {
        qDebug() << "updateInfojsonDocFile is writing";
        QTextStream outUpdateInfojsonDocFile(updateInfoJsonDocFile);
        outUpdateInfojsonDocFile << strBuffer.GetString();
    }
    qDebug() << "updateInfojsonDoc is finished";
    updateInfoJsonDocFile->close();
}

void updateTool::restartProj()
{
    qDebug() << "Performing application reboot..";
    restartedValue = true;
    getUpdateJson();
    qApp->quit();
    QProcess::startDetached(qApp->applicationFilePath());
}

void updateTool::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    downloadProgressBar->setMaximum(totalBytes);
    downloadProgressBar->setValue(bytesRead);
}
