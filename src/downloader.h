#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QDateTime>
#include <QMap>

class QNetworkReply;
class QNetworkAccessManager;
class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);
    ~Downloader();

    static QString ImageUrl;

public slots:
    void downloadSubreddit(const QString &name, const bool getNsfw, const int pages = -1);
    void download(QString urlString);
    void downloadFinished(QNetworkReply *reply);

signals:
    void imageFound(const QString &hash, const QString &extension, const QString &author,
                    const QString &title, const QDateTime &date, bool nsfw);

private:
    QNetworkAccessManager *m_netAccess;
    QMap<QString, QString> m_subdirs;
    QMap<QString, bool> m_getNsfw;

private slots:
    void parseXML(const QByteArray &data, const QString &url);
    void saveImageToDisk(const QByteArray &data, const QString &fileName);
};

#endif // DOWNLOADER_H
