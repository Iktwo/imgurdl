#include "downloadercomponent.h"

#include "downloader.h"

#include <QDebug>

DownloaderComponent::DownloaderComponent(QObject *parent) :
    QObject(parent)
{
    m_downloader = new Downloader();

    connect(m_downloader, SIGNAL(imageFound(QString, QString, QString, QString, QDateTime, bool)),
            this, SLOT(imageFound(QString, QString, QString, QString, QDateTime, bool)));
}

DownloaderComponent::~DownloaderComponent()
{
    delete m_downloader;
}

void DownloaderComponent::download(const QString &url, const bool getNsfw, int pages)
{
    m_downloader->downloadSubreddit(url, getNsfw, pages);
}

void DownloaderComponent::imageFound(const QString &hash, const QString &extension,
                                     const QString &author, const QString &title,
                                     const QDateTime &date, bool nsfw)
{
    /// TODO: store in model to display

    m_downloader->download(QString(Downloader::ImageUrl + hash + extension));
//    m_files.append(QString(Downloader::ImageUrl + hash + extension));
//    emit filesChanged();
}

QStringList DownloaderComponent::files()
{
    return m_files;
}
