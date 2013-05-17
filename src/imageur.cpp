#include "imageur.h"

Imageur::Imageur(QObject *parent) :
    QObject(parent)
{
}

Imageur::Imageur(QString hash, QString extension, QObject *parent) :
    QObject(parent),
    m_hash(hash),
    m_extension(extension)
{

}

Imageur::Imageur(QString hash, QString extension, QString author, QString title,
                 QDateTime date, bool nsfw, QObject *parent) :
    QObject(parent),
    m_hash(hash),
    m_extension(extension),
    m_author(author),
    m_title(title),
    m_date(date),
    m_nsfw(nsfw)
{

}

QString Imageur::hash()
{
    return m_hash;
}

void Imageur::setHash(QString hash)
{
    if (hash == m_hash)
        return;

    m_hash = hash;
    emit hashChanged();
}

QString Imageur::extension()
{
    return m_extension;
}

void Imageur::setExtension(QString extension)
{
    if (extension == m_extension)
        return;

    m_extension = extension;
    emit extensionChanged();
}

QString Imageur::author()
{
    return m_author;
}

void Imageur::setAuthor(QString author)
{
    if (author == m_author)
        return;

    m_author = author;
    emit authorChanged();
}

QString Imageur::title()
{
    return m_title;
}

void Imageur::setTitle(QString title)
{
    if (title == m_title)
        return;

    m_title = title;
    emit titleChanged();
}

QDateTime Imageur::date()
{
    return m_date;
}

void Imageur::setDate(QDateTime date)
{
    if (date == m_date)
        return;

    m_date = date;
    emit dateChanged();
}

bool Imageur::nsfw()
{
    return m_nsfw;
}

void Imageur::setNsfw(bool nsfw)
{
    if (nsfw == m_nsfw)
        return;

    m_nsfw = nsfw;
    emit nsfwChanged();
}
