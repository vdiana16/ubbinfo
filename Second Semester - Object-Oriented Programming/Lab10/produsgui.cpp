#include "produsgui.h"
#include "exceptions.h"
#include <qdebug.h>
#include <qmessagebox.h>

GUI::GUI(ServiceProdus& srv, Cos& coscump) : srv{ srv }, coscump{ coscump } {
	initGUI();
	load();
	connectSignals();
}

void GUI::initGUI() {
	this->setWindowTitle("Produse App");
	QPalette palette = QPalette();
	palette.setColor(QPalette::Window, "#429bf5");
	QFont font("Times New Roman", 12);
	this->setAutoFillBackground(true);
	this->setPalette(palette);
	this->setFont(font);
	setLayout(lyMain);

	lyMain->addWidget(listaProduse);
	lyMain->addWidget(tabelProduse);

	QVBoxLayout* lyStanga = new QVBoxLayout();
	QFormLayout* lyForm = new QFormLayout();
	lyForm->addRow("Id", txtId);
	lyForm->addRow("Nume", txtNume);
	lyForm->addRow("Tip", txtTip);
	lyForm->addRow("Pret", txtPret);
	lyForm->addRow("Producator", txtProducator);
	lyForm->addRow("Nr. de produse", txtAdRandom);
	lyForm->addRow("Nume fisier", txtSalvHtml);
	lyStanga->addLayout(lyForm);
	btnAdauga = new QPushButton("Adauga");
	btnSterge = new QPushButton("Sterge");
	btnModifica = new QPushButton("Modifica");
	btnCauta = new QPushButton("Cauta");
	btnSortareNume = new QPushButton("Sorteaza dupa nume");
	btnSortarePret = new QPushButton("Sorteaza dupa pret");
	btnSortareNumeTip = new QPushButton("Sorteaza dupa nume si tip");
	btnFiltrarePretMaiMare = new QPushButton("Filtreaza dupa pretul mai mare");
	btnFiltrareNume = new QPushButton("Filtreaza dupa nume");
	btnFiltrareProducator = new QPushButton("Filtreaza dupa producator");
	btnRaport = new QPushButton("Generare raport");
	btnUndo = new QPushButton("Undo");
	btnCos = new QPushButton("Deschide cos");
	btnReadOnlyCos = new QPushButton("Deschide cos read only");
	btnLoad = new QPushButton("Refresh");
	btnExit = new QPushButton("Exit");
	btnAdCos = new QPushButton("Adauga produs in cos");
	btnAdRandom = new QPushButton("Adauga random");
	btnStCos = new QPushButton("Goleste cos");
	btnSalvHtml = new QPushButton("Exporta produse");

	QHBoxLayout* lyBtns1= new QHBoxLayout;
	lyBtns1->addWidget(btnAdauga);
	lyBtns1->addWidget(btnSterge);
	lyBtns1->addWidget(btnModifica);
	lyBtns1->addWidget(btnCauta);
	QHBoxLayout* lyBtns2 = new QHBoxLayout;
	lyBtns2->addWidget(btnUndo);
	lyBtns2->addWidget(btnSortareNume);
	lyBtns2->addWidget(btnSortarePret);
	lyBtns2->addWidget(btnSortareNumeTip);
	QHBoxLayout* lyBtns3 = new QHBoxLayout;
	lyBtns3->addWidget(btnFiltrarePretMaiMare);
	lyBtns3->addWidget(btnFiltrareNume);
	lyBtns3->addWidget(btnFiltrareProducator);
	lyBtns3->addWidget(btnRaport);
	QHBoxLayout* lyBtns4 = new QHBoxLayout;
	lyBtns4->addWidget(btnAdCos);
	lyBtns4->addWidget(btnAdRandom);
	lyBtns4->addWidget(btnStCos);
	lyBtns4->addWidget(btnSalvHtml);
	QHBoxLayout* lyBtns5 = new QHBoxLayout;
	lyBtns5->addWidget(btnExit);
	lyBtns5->addWidget(btnLoad);
	lyBtns5->addWidget(btnCos);
	lyBtns5->addWidget(btnReadOnlyCos);

	lyStanga->addLayout(lyBtns1);
	lyStanga->addLayout(lyBtns2);
	lyStanga->addLayout(lyBtns3);
	lyStanga->addLayout(lyBtns4);
	lyStanga->addLayout(lyBtns5);

	lyMain->addLayout(lyStanga);
	lyMain->addWidget(listaRez);
	
	auto rap = srv.generareRaport(srv.getListaProd());
	for (auto const& p : rap) {
		QPushButton* buton = new QPushButton(QString::fromStdString(p.first));
		vectorbutoane.push_back(buton);
	}
	for (auto buton : vectorbutoane) {
		butoaneRaport->addWidget(buton);
	}
	lyMain->addLayout(butoaneRaport);
	
};

void GUI::load() {
	listaProduse->clear();
	const auto& lista = srv.getListaProd();
	for (const auto& p : lista) {
		listaProduse->addItem(QString::fromStdString(p.getNume()));
	}
	model = new MyTableModel{ lista };
	tabelProduse->setModel(model);
	/*
	tabelProduse->setColumnCount(5);
	int nr = srv.getListaProd().size();
	tabelProduse->setRowCount(nr);
	tabelProduse->setHorizontalHeaderLabels(QStringList{ "Id", "Nume", "Tip", "Pret", "Producator" });
	auto produse = srv.getListaProd();
	for (int i = 0; i < nr; i++) {
		tabelProduse->setItem(i, 0, new QTableWidgetItem(QString::number(produse[i].getId())));
		tabelProduse->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(produse[i].getNume())));
		tabelProduse->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(produse[i].getTip())));
		tabelProduse->setItem(i, 3, new QTableWidgetItem(QString::number(produse[i].getPret())));
		tabelProduse->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(produse[i].getProducator())));
	}
	listaCos->clear();
	const auto& prodcos = srv.getComp();
	listaCos->addItem("Produsele din cos sunt ");
	for (const auto& p : prodcos) {
		listaCos->addItem(QString::fromStdString(p.getNume()));
	}
	*/
}

void GUI::connectSignals() {
	QObject::connect(btnExit, &QPushButton::clicked, [&]() {
		this->close();
		QMessageBox::information(nullptr, "!", "Se inchide aplicatia");
		});
	QObject::connect(btnAdauga, &QPushButton::clicked, this, &GUI::adgui);
	QObject::connect(btnSterge, &QPushButton::clicked, this, &GUI::stergui);
	QObject::connect(btnModifica, &QPushButton::clicked, this, &GUI::modifgui);
	QObject::connect(btnCauta, &QPushButton::clicked, this, &GUI::cautgui);
	QObject::connect(btnSortareNume, &QPushButton::clicked, this, &GUI::sortnumegui);
	QObject::connect(btnSortarePret, &QPushButton::clicked, this, &GUI::sortpretgui);
	QObject::connect(btnSortareNumeTip, &QPushButton::clicked, this, &GUI::sortnumetipgui);
	QObject::connect(btnFiltrarePretMaiMare, &QPushButton::clicked, this, &GUI::filtpretgui);
	QObject::connect(btnFiltrareNume, &QPushButton::clicked, this, &GUI::filtnumegui);
	QObject::connect(btnFiltrareProducator, &QPushButton::clicked, this, &GUI::filtproducatorgui);
	QObject::connect(btnRaport, &QPushButton::clicked, this, &GUI::raportgui);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &GUI::undogui);
	QObject::connect(listaProduse, &QListWidget::itemClicked, this, &GUI::detalii);
	QObject::connect(tabelProduse->selectionModel(), &QItemSelectionModel::currentChanged,
		this, &GUI::detaliiTabel);
	QObject::connect(btnLoad, &QPushButton::clicked, [&]() {
		this->load();
		});
	QObject::connect(btnCos, &QPushButton::clicked, [&]() {
		GUICos* cosguin = new GUICos(srv, coscump);
		cosguin->show();
		});
	QObject::connect(btnReadOnlyCos, &QPushButton::clicked, [&]() {
		GUICosReadOnly* cosguirdon = new GUICosReadOnly(coscump);
		cosguirdon->show();
		});
	QObject::connect(btnAdCos, &QPushButton::clicked, this, &GUI::adcos);
	QObject::connect(btnAdRandom, &QPushButton::clicked, this, &GUI::adRandom);
	QObject::connect(btnStCos, &QPushButton::clicked, this, &GUI::stCos);
	QObject::connect(btnSalvHtml, &QPushButton::clicked, this, &GUI::salveazaHtml);
	butoaneraportgui();
}

void GUI::curatareCampuriText() {
	txtId->clear();
	txtNume->clear();
	txtTip->clear();
	txtPret->clear();
	txtProducator->clear();
}

void GUI::butoaneraportgui() {
	for (auto buton : vectorbutoane) {
		QObject::connect(buton, &QPushButton::clicked, this, [this, buton]() {
			auto txt = buton->text();
			const auto& rap = srv.generareRaport(srv.getListaProd());
			for (const auto& p : rap) {
				if (p.first == txt.toStdString()) {
					QMessageBox::information(this, "Raport", "Numarul de produse de acest tip este: " + QString::number(p.second.nr));
					break;
				}
			}
			});
	}
}

void GUI::adgui() {
	try {
		auto nume = txtNume->text().toStdString();
		auto tip = txtTip->text().toStdString();
		auto pret = txtPret->text().toDouble();
		auto producator = txtProducator->text().toStdString();
		srv.adaugaProd(nume, tip, pret, producator);
		load();
		curatareCampuriText();
	}
	catch (ValidException& e1) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(e1.getMesaje()));
	}
	catch (RepoException& e2) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(e2.getMesaj()));
	}
}

void GUI::stergui() {
	try {
		auto id = txtId->text().toInt();
		srv.stergeProd(id);
		load();
		curatareCampuriText();
	}
	catch (RepoException& e2) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(e2.getMesaj()));
	}
}

void GUI::modifgui() {
	auto id = txtId->text().toInt();
	auto nume = txtNume->text().toStdString();
	auto tip = txtTip->text().toStdString();
	auto pret = txtPret->text().toDouble();
	auto producator = txtProducator->text().toStdString();
	try {
		srv.modificaProd(id, nume, tip, pret, producator);
		load();
		curatareCampuriText();
	}
	catch (RepoException& e2) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(e2.getMesaj()));
	}
}

void GUI::cautgui() {
	try {
		auto id = txtId->text().toInt();
		auto prod = srv.cautaProd(id);
		txtNume->setText(QString::fromStdString(prod.getNume()));
		txtTip->setText(QString::fromStdString(prod.getTip()));
		txtPret->setText(QString::number(prod.getPret()));
		txtProducator->setText(QString::fromStdString(prod.getProducator()));
	}
	catch (const RepoException& e) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(e.getMesaj()));
	}
}

void GUI::sortnumegui() {
	const auto& listasort = srv.sortNume();
	listaRez->clear();
	listaRez->addItem("Lista sortata dupa nume este:");
	if (listasort.size() > 0) {
		for (const auto& p : listasort) {
			listaRez->addItem(QString::fromStdString(p.getNume()));
		}
	}
	else {
		listaRez->addItem("Lista vida!");
	}
}

void GUI::sortpretgui() {
	const auto& listasort = srv.sortPret();
	listaRez->clear();
	listaRez->addItem("Lista sortata dupa pret este:");
	if (listasort.size() > 0) {
		for (const auto& p : listasort) {
			listaRez->addItem(QString::fromStdString(p.getNume()));
		}
	}
	else {
		listaRez->addItem("Lista vida!");
	}
}

void GUI::sortnumetipgui() {
	const auto& listasort = srv.sortNumeTip();
	listaRez->clear();
	listaRez->addItem("Lista sortata dupa nume si tip este:");
	if (listasort.size() > 0) {
		for (const auto& p : listasort) {
			listaRez->addItem(QString::fromStdString(p.getNume()));
		}
	}
	else {
		listaRez->addItem("Lista vida!");
	}
}

void GUI::filtpretgui() {
	//curatareCampuriText();
	auto pret = txtPret->text().toDouble();
	const auto& listafilt = srv.filtPretMaiMare(pret);
	listaRez->clear();
	listaRez->addItem("Lista filtrata dupa pret este:");
	if (listafilt.size() > 0) {
		for (const auto& p : listafilt) {
			listaRez->addItem(QString::fromStdString(p.getNume()));
		}
	}
	else {
		listaRez->addItem("Lista vida!");
	}
}

void GUI::filtnumegui() {
	//curatareCampuriText();
	auto nume = txtNume->text().toStdString();
	const auto& listafilt = srv.filtNume(nume);
	listaRez->clear();
	listaRez->addItem("Lista filtrata dupa nume este:");
	if (listafilt.size() > 0) {
		for (const auto& p : listafilt) {
			listaRez->addItem(QString::fromStdString(p.getNume()));
		}
	}
	else {
		listaRez->addItem("Lista vida!");
	}
}

void GUI::filtproducatorgui() {
	//curatareCampuriText();
	auto producator = txtProducator->text().toStdString();
	const auto& listafilt = srv.filtProducator(producator);
	listaRez->clear();
	listaRez->addItem("Lista filtrata dupa producator este:");
	if (listafilt.size() > 0) {
		for (const auto& p : listafilt) {
			listaRez->addItem(QString::fromStdString(p.getNume()));
		}
	}
	else {
		listaRez->addItem("Lista vida!");
	}
}

void GUI::raportgui() {
	const auto& listarap = srv.generareRaport(srv.getListaProd());
	if (listarap.size() > 0) {
		listaRez->clear();
		listaRez->addItem("Raport in functie de tip:");
		for (const auto& p : listarap) {
			listaRez->addItem(QString::fromStdString(p.first) + ": " + QString::number(p.second.nr));
		}
	}
	else {
		QMessageBox::warning(nullptr, "Warning", "Nu exista produse!");
	}
}

void GUI::undogui() {
	try {
		srv.undo();
		load();
	}
	catch (const RepoException& e) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(e.getMesaj()));
	}
}

void GUI::detalii() {
	auto numeProdus = listaProduse->currentItem()->text().toStdString();
	auto idp = srv.cautaProdN(numeProdus);
	const auto& prod = srv.cautaProd(idp);
	txtId->setText(QString::number(prod.getId()));
	txtNume->setText(QString::fromStdString(prod.getNume()));
	txtTip->setText(QString::fromStdString(prod.getTip()));
	txtPret->setText(QString::number(prod.getPret()));
	txtProducator->setText(QString::fromStdString(prod.getProducator()));
}		

void GUI::adcos() {
	try {
		const auto& id = txtId->text().toInt();
		const auto& nume = txtNume->text().toStdString();
		const auto& tip = txtTip->text().toStdString();
		auto pret = txtPret->text().toDouble();
		const auto& producator = txtProducator->text().toStdString();
		Produs prod{ id,nume,tip,pret,producator };
		coscump.adaugaCos(prod);
		listaCos->addItem(QString::fromStdString(nume));
		curatareCampuriText();
	}
	catch (const CosCumpException& e) {
		curatareCampuriText();
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(e.getMesaj()));
	}
}

void GUI::salveazaHtml() {
	auto numefis = txtSalvHtml->text().toStdString();
	if (numefis.size() > 0) {
		coscump.salveazaFisier(numefis);
		curatareCampuriText();
	}
	else {
		curatareCampuriText();
		QMessageBox::warning(nullptr, "Warning", "Eroare la fisier! ");
	}

}

void GUI::adRandom() {
	auto nr = txtAdRandom->text().toInt();
	try {
		coscump.adaugaRandom(srv.getListaProd(), nr);
		load();
		curatareCampuriText();
	}
	catch (const CosCumpException& e) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(e.getMesaj()));
	}
}

void GUI::stCos() {
	coscump.stergeCos();
	load();
	curatareCampuriText();
}

void GUI::detaliiTabel(const QModelIndex& ind) {
	Produs prsel = model->getProd(ind);
	txtId->setText(QString::number(prsel.getId()));
	txtNume->setText(QString::fromStdString(prsel.getNume()));
	txtTip->setText(QString::fromStdString(prsel.getTip()));
	txtPret->setText(QString::number(prsel.getPret()));
	txtProducator->setText(QString::fromStdString(prsel.getProducator()));
}