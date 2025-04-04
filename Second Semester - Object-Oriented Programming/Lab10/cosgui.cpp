#include "cosgui.h"

GUICos::GUICos(ServiceProdus& srv, Cos& coscump) :srv{ srv }, coscump{ coscump } {
	initGUICos();
	conncetGUICos();
	loadGUICos();
}

void GUICos::initGUICos() {
	setWindowTitle("Cos");
	coscump.adaugaObserver(this);
	QPalette secondpalette = QPalette();
	secondpalette.setColor(QPalette::Window, "#a8329a");
	QFont font2("Times New Roman", 12);
	setPalette(secondpalette);
	setFont(font2);
	setLayout(mainLy);
	mainLy->addWidget(listaProduseCos);
	QFormLayout* formLy = new QFormLayout();
	formLy->addRow("Nr. de produse", txtAdaugaRandom);
	QVBoxLayout* stLy = new QVBoxLayout();
	stLy->addLayout(formLy);
	btnAdaugaRandom = new QPushButton("Adauga random");
	btnStergeCos = new QPushButton("Goleste cos");
	btnRefreshCos = new QPushButton("Refresh");
	btnExitCos = new QPushButton("Exit");
	QHBoxLayout* btnsLyst = new QHBoxLayout();
	btnsLyst->addWidget(btnAdaugaRandom);
	btnsLyst->addWidget(btnStergeCos);
	btnsLyst->addWidget(btnRefreshCos);
	btnsLyst->addWidget(btnExitCos);
	stLy->addLayout(btnsLyst);
	mainLy->addLayout(stLy);

}

void GUICos::loadGUICos() {
	listaProduseCos->clear();
	for (const auto& elem : coscump.getComponente()) {
		listaProduseCos->addItem(QString::fromStdString(elem.getNume()) + ' ' + QString::fromStdString(elem.getTip()) + ' ' + QString::number(elem.getPret()) + ' ' + QString::fromStdString(elem.getProducator()));
	}
}

void GUICos::conncetGUICos() {
	QObject::connect(btnRefreshCos, &QPushButton::clicked, [&]() {
		loadGUICos();
		});
	QObject::connect(btnExitCos, &QPushButton::clicked, [&]() {
		close();
		});
	QObject::connect(btnAdaugaRandom, &QPushButton::clicked, this, &GUICos::adaugaRandom);
	QObject::connect(btnStergeCos, &QPushButton::clicked, this, &GUICos::stergeCos);
	QObject::connect(this, &QWidget::close, this, [this]() {
		coscump.stergeObserver(this);
		});
}

void GUICos::adaugaRandom() {
	auto nr = txtAdaugaRandom->text().toInt();
	try {
		coscump.adaugaRandom(srv.getListaProd(), nr);
	}
	catch (const CosCumpException& e) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(e.getMesaj()));
	}
}

void GUICos::stergeCos() {
	srv.golesteCos();
	loadGUICos();
}

void GUICos::curatareCampuriText() {
	txtAdaugaRandom->clear();
}

GUICosReadOnly::GUICosReadOnly(Cos& coscump) : coscump{ coscump } {
	coscump.adaugaObserver(this);
	connect();
}

void GUICosReadOnly::connect() {
	QObject::connect(this, &QWidget::close, this, [&]() {
		coscump.stergeObserver(this);
		});
}