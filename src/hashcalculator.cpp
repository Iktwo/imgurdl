#include "hashcalculator.h"
#include <QCryptographicHash>

HashCalculator::HashCalculator(QObject *parent) :
    QObject(parent)
{
    m_hash = new QCryptographicHash(QCryptographicHash::Md5);
}

void HashCalculator::addData(const QByteArray &data)
{
    m_hash->addData(data);
}

QString HashCalculator::result()
{
    QString hash(m_hash->result().toHex());
    m_hash->reset();
    return hash;
}
