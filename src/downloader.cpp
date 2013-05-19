#include "downloader.h"

#include <QDebug>
#include <QtNetwork>
#include <QtXml>
#include <QDir>
#include <QFile>

#define IMGUR_URL "http://imgur.com/r/"

QString Downloader::ImageUrl("http://i.imgur.com/");

Downloader::Downloader(QObject *parent) :
    QObject(parent)
{
    m_netAccess = new QNetworkAccessManager(this);

    connect(m_netAccess, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(downloadFinished(QNetworkReply*)));
}

Downloader::~Downloader()
{
    delete m_netAccess;
}

void Downloader::downloadSubreddit(const QString &name, const bool getNsfw, const int pages)
{
    // if pages == -1 download until there are two equal hashes
    // else iterate trough *pages*
    if (pages == 0)
        return;

    if (pages != -1)
        for (int i = 0; i < pages; ++i) {
            QString url(IMGUR_URL + name + "/page/" + QString::number(i) + ".xml");
            m_getNsfw.insert(url, getNsfw);
            download(QString(IMGUR_URL + name + "/page/" + QString::number(i) + ".xml"));
        }
    else
        qDebug() << "TODO: get 'em all"; /// TODO: download until two sequential hashes are equal
}

void Downloader::download(QString urlString)
{
    QUrl url(urlString);
    QNetworkRequest request(url);
    m_netAccess->get(request);
}

void Downloader::downloadFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << Q_FUNC_INFO << " error downloading "
                 << reply->url().toString() << ":" << reply->errorString();

        reply->deleteLater();
        return;
    }

    //    qDebug() << reply->url().toString() << " has been dowloaded";

    QVariant redir = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    if (redir.isValid()) {
        QUrl url = redir.toUrl();
        qDebug() << reply->url().toString() << " was redirected to:" << url.toString();

        if (url.isRelative()) {
            url.setScheme(reply->url().scheme());
            url.setEncodedHost(reply->url().encodedHost());
        }

        download(url.toString());
        return;
    }

    QString mimeType(reply->header(QNetworkRequest::ContentTypeHeader).toString());

    if (mimeType == "text/xml") {
        parseXML(reply->readAll(), reply->url().toString());
    } else if (mimeType.contains("image/")) {
        saveImageToDisk(reply->readAll(), reply->url().path().mid(1));
    } else
        qDebug() << reply->url().toString()
                 << " type is:" << mimeType;

    reply->deleteLater();
}

void Downloader::parseXML(const QByteArray &data, const QString &url)
{
    QDomDocument xml;
    xml.setContent(data);

    QDomElement domElement = xml.documentElement();
    QDomNode node = domElement.firstChild();

    while(!node.isNull()) {
        //        qDebug() << "===================";
        //        qDebug() << "checking child node";
        //        qDebug() << "===================";

        if (node.firstChild().hasChildNodes()) {
            QDomNode childNode = node.firstChild();

            QString hash;
            QString extension;
            QString author;
            QString title;
            QDateTime date;
            bool nsfw(false);
            QString subreddit;

            while(!childNode.isNull()) {
                QDomElement element = childNode.toElement();

                if (element.tagName() == "hash")
                    hash = element.text();
                else if (element.tagName() == "ext")
                    extension = element.text();
                else if (element.tagName() == "author")
                    author = element.text();
                else if (element.tagName() == "title")
                    title = element.text();
                else if (element.tagName() == "datetime") {
                    date.setDate(QDate::fromString(element.text().mid(0,10), "yyyy-MM-dd"));
                    date.setTime(QTime::fromString(element.text().mid(11), "hh:mm:ss"));
                } else if (element.tagName() == "nsfw") {
                    if (element.text() == "true")
                        nsfw = true;
                } else if (element.tagName() == "subreddit")
                    subreddit = element.text();
                // else
                // qDebug() << element.tagName() << element.text();

                childNode = childNode.nextSibling();
            }

            if (!hash.simplified().isEmpty()) {
                m_subdirs.insert(QString(hash + extension), subreddit);
                if (!nsfw || (nsfw && m_getNsfw[url]))
                    emit imageFound(hash, extension, author, title, date, nsfw);
                else {
                    qDebug() << "skipping NSFW content from: " << url;
                }
            }
        }

        node = node.nextSibling();
    }

    m_getNsfw.remove(url);
}

void Downloader::saveImageToDisk(const QByteArray &data, const QString &fileName)
{
    QString subreddit(m_subdirs.take(fileName));
    QDir subDir(subreddit);
    if (!subDir.exists())
        subDir.mkdir(subDir.absolutePath());

    QFile file(subreddit + "/" + fileName);
    if (file.exists())
        return;

    if (!file.open(QIODevice::WriteOnly))
        return;

    file.write(data);
    file.close();
}
