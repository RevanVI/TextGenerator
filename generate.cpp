#include "generate.h"


void add(Hash& hash, Prefix& prefix, QString& str, int prefLen)
{
    if (prefix.length() == prefLen)
    {
        hash[prefix].push_back(str);
        prefix.pop_front();
    }
    prefix.push_back(str);
}

void buildHash(Hash& hash, Prefix& prefix, QTextStream& in, int prefLen)
{
    QString buf;
    while (!in.atEnd())
    {
        in >> buf;
        add(hash, prefix, buf, prefLen);
    }
}

void generate(Hash& hash, QTextStream& out, int textLen, int prefLen, QString& stopWord)
{
    srand(time(NULL));
    Prefix prefix;
    for (int i = 0; i < prefLen; ++i)
        add(hash, prefix, stopWord, prefLen);
    for (int i = 0; i < textLen; ++i)
    {
        QVector<QString>& suffix = hash[prefix];
        QString& chosenSuffix = suffix[ rand() % suffix.size()];
        if (chosenSuffix == stopWord)
            break;
        out << chosenSuffix << " ";
        prefix.pop_front();
        prefix.push_back(chosenSuffix);
    }
}

