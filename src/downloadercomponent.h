#ifndef DOWNLOADERCOMPONENT_H
#define DOWNLOADERCOMPONENT_H

#include <QObject>
#include <QDateTime>

class Downloader;
class DownloaderComponent : public QObject
{
    Q_OBJECT
public:
    explicit DownloaderComponent(QObject *parent = 0);
    ~DownloaderComponent();

    Q_INVOKABLE void download(const QString &url, int pages);
    
private:
    Downloader *m_downloader;

private slots:
    void imageFound(const QString &hash, const QString &extension, const QString &author,
                    const QString &title, const QDateTime &date, bool nsfw);
    
};

#endif // DOWNLOADERCOMPONENT_H
