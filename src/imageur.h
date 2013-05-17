#ifndef IMAGEUR_H
#define IMAGEUR_H

#include <QObject>
#include <QDateTime>

class Imageur : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString hash READ hash NOTIFY hashChanged)
    Q_PROPERTY(QString extension READ hash NOTIFY extensionChanged)
    Q_PROPERTY(QString author READ author NOTIFY authorChanged)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QDateTime date READ date NOTIFY dateChanged)
    Q_PROPERTY(bool nsfw READ nsfw NOTIFY nsfwChanged)
public:
    explicit Imageur(QObject *parent = 0);
    Imageur(QString hash, QString extension, QObject *parent = 0);
    Imageur(QString hash, QString extension, QString author, QString title,
            QDateTime date, bool nsfw, QObject *parent = 0);
    
    QString hash();
    QString extension();
    QString author();
    QString title();
    QDateTime date();
    bool nsfw();

    void setHash(QString hash);
    void setExtension(QString extension);
    void setAuthor(QString author);
    void setTitle(QString title);
    void setDate(QDateTime date);
    void setNsfw(bool nsfw);

signals:
    void hashChanged();
    void extensionChanged();
    void authorChanged();
    void titleChanged();
    void dateChanged();
    void nsfwChanged();

private:
    QString m_hash;
    QString m_extension;
    QString m_author;
    QString m_title;
    QDateTime m_date;
    bool m_nsfw;
    
};

#endif // IMAGEUR_H
