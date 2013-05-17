#ifndef HASHCALCULATOR_H
#define HASHCALCULATOR_H

#include <QObject>

class QCryptographicHash;
class HashCalculator : public QObject
{
    Q_OBJECT
public:
    explicit HashCalculator(QObject *parent = 0);
    
    void addData (const QByteArray &data);
    QString result();

signals:

private:
    QCryptographicHash *m_hash;
};

#endif // HASHCALCULATOR_H
