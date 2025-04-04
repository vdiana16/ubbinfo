#pragma once

typedef int TElem;

class Vectorind {
private:
	int cp;
	int lg;
	
public:
	int* v;
	Vectorind();
	~Vectorind();
	int getlg() const;
	void adauga(int ind);
	void redim();
	void sterge(int ind);
};

class Vectorval {
private:
	int cp;
	int lg;

public:
	TElem* v;
	Vectorval();
	~Vectorval();
	int getlg() const;
	void adauga(TElem val);
	void redim();
	void sterge(TElem val);
};
