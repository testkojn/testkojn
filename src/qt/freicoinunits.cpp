#include "testkojnunits.h"

#include <QStringList>

TestkojnUnits::TestkojnUnits(QObject *parent):
        QAbstractListModel(parent),
        unitlist(availableUnits())
{
}

QList<TestkojnUnits::Unit> TestkojnUnits::availableUnits()
{
    QList<TestkojnUnits::Unit> unitlist;
    unitlist.append(TSK);
    unitlist.append(mTSK);
    unitlist.append(uTSK);
    return unitlist;
}

bool TestkojnUnits::valid(int unit)
{
    switch(unit)
    {
    case TSK:
    case mTSK:
    case uTSK:
        return true;
    default:
        return false;
    }
}

QString TestkojnUnits::name(int unit)
{
    switch(unit)
    {
    case TSK: return QString("TSK");
    case mTSK: return QString("mTSK");
    case uTSK: return QString::fromUtf8("μTSK");
    default: return QString("???");
    }
}

QString TestkojnUnits::description(int unit)
{
    switch(unit)
    {
    case TSK: return QString("Testkojns");
    case mTSK: return QString("Milli-Testkojns (1 / 1,000)");
    case uTSK: return QString("Micro-Testkojns (1 / 1,000,000)");
    default: return QString("???");
    }
}

mpq TestkojnUnits::factor(int unit)
{
    switch(unit)
    {
    case uTSK: return mpq("100/1");
    case mTSK: return mpq("100000/1");
    default:
    case TSK:  return mpq("100000000/1");
    }
}

int TestkojnUnits::amountDigits(int unit)
{
    switch(unit)
    {
    case TSK: return 8; // <100,000,000 (# digits, without commas)
    case mTSK: return 11; // <100,000,000,000
    case uTSK: return 14; // <100,000,000,000,000
    default: return 0;
    }
}

int TestkojnUnits::decimals(int unit)
{
    switch(unit)
    {
    case TSK: return 8;
    case mTSK: return 5;
    case uTSK: return 2;
    default: return 0;
    }
}

QString TestkojnUnits::format(int unit, const mpq& n, bool fPlus)
{
    // Note: not using straight sprintf here because we do NOT want
    // localized number formatting.
    if(!valid(unit))
        return QString(); // Refuse to format invalid unit
    mpq q = n * COIN / factor(unit);
    std::string str = FormatMoney(q, fPlus);
    int diff = 8 - decimals(unit);
    if(diff > 0)
        str.erase(str.length() - diff, diff);
    return QString::fromStdString(str);
}

QString TestkojnUnits::formatWithUnit(int unit, const mpq& amount, bool plussign)
{
    return format(unit, amount, plussign) + QString(" ") + name(unit);
}

bool TestkojnUnits::parse(int unit, const QString &value, mpq *val_out)
{
    mpq ret_value;
    if (!ParseMoney(value.toStdString(), ret_value))
        return false;
    if(val_out)
    {
        *val_out = ret_value * factor(unit) / COIN;
    }
    return true;
}

int TestkojnUnits::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return unitlist.size();
}

QVariant TestkojnUnits::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row >= 0 && row < unitlist.size())
    {
        Unit unit = unitlist.at(row);
        switch(role)
        {
        case Qt::EditRole:
        case Qt::DisplayRole:
            return QVariant(name(unit));
        case Qt::ToolTipRole:
            return QVariant(description(unit));
        case UnitRole:
            return QVariant(static_cast<int>(unit));
        }
    }
    return QVariant();
}
