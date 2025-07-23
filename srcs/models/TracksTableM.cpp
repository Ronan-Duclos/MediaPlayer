#include "TracksTableM.hpp"

#include <QSize>

TracksTableM::TracksTableM(QObject *parent) :
    QAbstractTableModel(parent), m_headers{"Title", "Artist", "Album", "Duration"}
{

}

int TracksTableM::rowCount(const QModelIndex &parent) const
{
    return m_table.size();
}

int TracksTableM::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant TracksTableM::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int column = index.column();

    if (row < m_table.size() && column < 4 && role == Qt::DisplayRole)
        return QVariant(m_table.at(row).at(column));
    return QVariant();
}

QVariant TracksTableM::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Vertical)
            return QVariant(section + 1);
        else
            return QVariant(m_headers.at(section));
    }
    if (role == Qt::SizeHintRole)
        return QSize(25, 22);
    return QVariant();
}

void TracksTableM::insertRows(const QStringList row)
{
    if (row.size() == 4) {
        beginInsertRows(QModelIndex(), m_table.size(), m_table.size());
        m_table.push_back(row);
        endInsertRows();
    }
}

void TracksTableM::removeRow(const int row)
{
    qDebug() << "remove TracksTableM track:" << m_table.at(row).at(1);
    beginRemoveRows(QModelIndex(), row, row);
    m_table.remove(row);
    endRemoveRows();
}
