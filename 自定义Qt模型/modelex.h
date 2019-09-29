#ifndef MODELEX_H
#define MODELEX_H

#include <QWidget>
#include <QAbstractTableModel>
#include <QVector>
#include <QMap>
#include <QStringList>

class ModelEx : public QAbstractTableModel
{
    Q_OBJECT

public:
    ModelEx(QWidget *parent = 0);
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    ~ModelEx();
signals:
public slots:
private:
    QVector<short> army;
    QVector<short> weaponType;
    QMap<short,QString> armyMap;
    QMap<short,QString> weaponTypeMap;
    QStringList weapon;
    QStringList header;
    void populateModel();
};

#endif // MODELEX_H
