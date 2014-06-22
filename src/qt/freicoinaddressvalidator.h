#ifndef TESTKOJNADDRESSVALIDATOR_H
#define TESTKOJNADDRESSVALIDATOR_H

#include <QRegExpValidator>

/** Base48 entry widget validator.
   Corrects near-miss characters and refuses characters that are no part of base48.
 */
class TestkojnAddressValidator : public QValidator
{
    Q_OBJECT
public:
    explicit TestkojnAddressValidator(QObject *parent = 0);

    State validate(QString &input, int &pos) const;

    static const int MaxAddressLength = 35;
signals:

public slots:

};

#endif // TESTKOJNADDRESSVALIDATOR_H
