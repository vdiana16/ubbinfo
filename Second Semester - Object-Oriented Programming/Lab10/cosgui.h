#pragma once
#ifndef  COSGUI_H
#define COSGUI_H

#include <QtWidgets>
#include <qboxlayout.h>
#include <qlistwidget.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <qpainter.h>
#include <qdrawutil.h>
#include <qsplitter.h>
#include "coscump.h"
#include "produsgui.h"
#include "service.h"
#include "exceptions.h"
#include "observer.h"

class GUICosReadOnly;
class GUI;

class GUICos : public QWidget, public Observer{
	friend class GUI;

private:
	Cos& coscump;
	ServiceProdus& srv;

	QHBoxLayout* mainLy = new QHBoxLayout();
	QPushButton* btnAdaugaRandom;
	QPushButton* btnStergeCos;
	QPushButton* btnRefreshCos;
	QPushButton* btnExitCos;

	QLineEdit* txtAdaugaRandom = new QLineEdit();
	
	QListWidget* listaProduseCos = new QListWidget();
	
	void curatareCampuriText();

	void adcosgui();

	//Adauga medicamente random
	void adaugaRandom();

	//Goleste cosul de cumparaturi
	void stergeCos();

	//Exporta in fisier
	void salveazaHtml();

	void initGUICos();

	void conncetGUICos();

	void loadGUICos();


public:
	GUICos(ServiceProdus& srv, Cos& coscump);

	void update() override {
		loadGUICos();
	}

};

class GUICosReadOnly : public QWidget, public Observer {
	friend class GUICos;
private:
	Cos& coscump;
	QListWidget* listaProduseCos = new QListWidget();
	void connect();
public:
	GUICosReadOnly(Cos& coscump);

	void initGUICosReadOnly() {
		setWindowTitle("Set Cos");
		listaProduseCos = new QListWidget();
		QHBoxLayout* lyMainCos = new QHBoxLayout;
		lyMainCos->addWidget(listaProduseCos);
		this->setLayout(lyMainCos);
	}
	void update() override{
		this->repaint();
	}
	void loadGUICosReadOnly() {
		listaProduseCos->clear();
		for (const auto& elem : coscump.getComponente()) {
			listaProduseCos->addItem(QString::fromStdString(elem.getNume()) + ' ' + QString::fromStdString(elem.getTip()) + ' ' + QString::number(elem.getPret()) + ' ' + QString::fromStdString(elem.getProducator()));
		}
	}
	void paintEvent(QPaintEvent* e)override {
		QPainter p(this);
		int x = 10;
		int lg=coscump.getComponente().size();
		p.drawImage(0,0,QImage("img.jpg"));
		for (int i = 0; i < lg; i++) {
			p.drawRect(x, 30, 20, 30);
			x += 20;
		}
	}
};

#endif // ! COSGUI_H
