#pragma once

#define CAPACITATE 20
#define NULL_TELEM -200000

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorMultime;


class Multime {

	friend class IteratorMultime;

private:
	int rad;
	int primLiber;
	int lg;
	int cap;
	TElem* element;
	int* stanga;
	int* dreapta;

	void redimensionare();
	void initSpatiuLiber();
	int aloca();
	void dealoca(int i);
	int minim(int nod);
	
public:
	//constructorul implicit
	Multime();

	//adauga un element in multime
	//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
	bool adauga(TElem e);

	//sterge un element din multime
	//returneaza adevarat daca elementul a existat si a fost sters
	bool sterge(TElem e);

	//verifica daca un element se afla in multime
	bool cauta(TElem elem) const;


	//intoarce numarul de elemente din multime;
	int dim() const;

	//verifica daca multimea e vida;
	bool vida() const;

	//returneaza un iterator pe multime
	IteratorMultime iterator() const;


	// destructorul multimii
	~Multime();

};

