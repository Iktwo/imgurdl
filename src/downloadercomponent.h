#ifndef DOWNLOADERCOMPONENT_H
#define DOWNLOADERCOMPONENT_H

#include <QObject>
#include <QDateTime>
#include <QStringList>

class Downloader;
class DownloaderComponent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList files READ files NOTIFY filesChanged)
public:
    explicit DownloaderComponent(QObject *parent = 0);
    ~DownloaderComponent();

    Q_INVOKABLE void download(const QString &url, const bool getNsfw, int pages);

    QStringList files();
    
signals:
    void filesChanged();

private:
    Downloader *m_downloader;
    QStringList m_files;

private slots:
    void imageFound(const QString &hash, const QString &extension, const QString &author,
                    const QString &title, const QDateTime &date, bool nsfw);
    
};

#endif // DOWNLOADERCOMPONENT_H
