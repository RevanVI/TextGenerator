#ifndef GENERATE_H
#define GENERATE_H

#include <QList>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QHash>
#include <QVector>
#include <ctime>

typedef QList<QString> Prefix;
typedef QHash<Prefix, QVector<QString>> Hash;

void buildHash(Hash& hash, Prefix& prefix, QTextStream& in, int prefLen);
void add(Hash& hash, Prefix& prefix, QString& str, int prefLen);
void generate(Hash& hash, QTextStream& out, int textLen, int prefLen, QString& stopWord);

#endif // GENERATE_H
