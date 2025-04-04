#pragma once
#include <QAbstractTableModel>
#include <vector>
using std::vector;
#include <QAbstractItemView>
#include <iostream>
#include "service.h"


class MyTableModel :public QAbstractTableModel {
	std::vector<Produs> produse;
public:
	MyTableModel(const vector<Produs>& produse) : produse(produse) {};
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return produse.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			Produs prod = produse[index.row()];
			if (index.column() == 0) {
				return QString::number(prod.getId());
			}
			if (index.column() == 1) {
				return QString::fromStdString(prod.getNume());
			}
			if (index.column() == 2) {
				return QString::fromStdString(prod.getTip());
			}
			if (index.column() == 3) {
				return QString::number(prod.getPret());
			}
			if (index.column() == 4) {
				return QString::fromStdString(prod.getProducator());
			}
		}
		return QVariant{};
	}
	QVariant headerData(int section, Qt::Orientation orientation, int role) const {
		if (orientation == Qt::Horizontal) {
			if (role == Qt::DisplayRole)
				switch (section) {
				case 0:
					return "Id";
					break;
				case 1:
					return "Nume";
					break;
				case 2:
					return "Tip";
					break;
				case 3:
					return "Pret";
					break;
				case 4:
					return "Producator";
					break;
				default:
					return QString("Column %1").arg(section + 1);
					break;
				}
		}
		else if (orientation == Qt::Vertical) {
			if (role == Qt::DisplayRole)
				return section + 1;
		}
		return QVariant();
	}

	Produs getProd(const QModelIndex& index) {
		return produse[index.row()];
	}
	void setProd(const vector<Produs>& prd) {
		this->produse = prd;
		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
		emit layoutChanged();
	}
};