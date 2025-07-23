#pragma once

#include <QAbstractTableModel>

class TracksTableM : public QAbstractTableModel
{
public:
    explicit TracksTableM(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    void insertRows(const QStringList row);
    void removeRow(const int row);

private:
    QList<QStringList> m_table;
    QStringList m_headers;
};
