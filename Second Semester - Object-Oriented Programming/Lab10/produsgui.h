#pragma once
#ifndef PRODUSGUI_H
#define PRODUSGUI_H

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qtablewidget.h>
#include <qlistview.h>
#include "domain.h"
#include "service.h"
#include "cosgui.h"
#include <vector>
#include <qlabel.h>
#include "observer.h"
#include "coscump.h"
#include "mytable.h"

class GUICos;

class GUI : public QWidget {
	friend class GUICos;
private:
	ServiceProdus& srv;
	Cos& coscump;
	vector<QPushButton*> vectorbutoane;

	QHBoxLayout* lyMain = new QHBoxLayout;

	QPushButton* btnAdauga;
	QPushButton* btnSterge;
	QPushButton* btnModifica;
	QPushButton* btnCauta;
	QPushButton* btnSortareNume;
	QPushButton* btnSortarePret;
	QPushButton* btnSortareNumeTip;
	QPushButton* btnFiltrarePretMaiMare;
	QPushButton* btnFiltrareNume;
	QPushButton* btnFiltrareProducator;
	QPushButton* btnRaport;
	QPushButton* btnUndo;
	QPushButton* btnExit;
	QPushButton* btnLoad;
	QPushButton* btnAdCos;
	QPushButton* btnAdRandom;
	QPushButton* btnStCos;
	QPushButton* btnSalvHtml;
	QPushButton* btnCos;
	QPushButton* btnReadOnlyCos;

	QLineEdit* txtId = new QLineEdit();
	QLineEdit* txtNume = new QLineEdit();
	QLineEdit* txtTip = new QLineEdit();
	QLineEdit* txtPret = new QLineEdit();
	QLineEdit* txtProducator = new QLineEdit();
	QLineEdit* txtAdRandom = new QLineEdit();
	QLineEdit* txtSalvHtml = new QLineEdit();

	QListWidget* listaProduse = new QListWidget();
	QListWidget* listaCos = new QListWidget();
	QListWidget* listaRez = new QListWidget();
	QTableView* tabelProduse = new QTableView();
	MyTableModel* model;

	QVBoxLayout* butoaneRaport = new QVBoxLayout;

	void curatareCampuriText();

	void butoaneraportgui();

	//initializare fereastra
	void initGUI();
	//incarca datele
	void load();
	//conecteaza butoanele
	void connectSignals();

	void adgui();
	void stergui();
	void cautgui();
	void modifgui();
	void sortnumegui();
	void sortpretgui();
	void sortnumetipgui();
	void filtpretgui();
	void filtnumegui();
	void filtproducatorgui();
	void raportgui();
	void undogui();
	void detaliiTabel(const QModelIndex& ind);
	void detalii();
	void adcos();
	void adRandom();
	void stCos();
	void salveazaHtml();
public:
	GUI(ServiceProdus& srv, Cos& coscump);
};

#endif // !PRODUSGUI_H