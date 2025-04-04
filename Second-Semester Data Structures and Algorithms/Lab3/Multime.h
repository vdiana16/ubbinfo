#pragma once

#define NULL_TELEM -1
#define CAPACITATE 10

typedef int TElem;

class IteratorMultime;

class Multime {
	friend class IteratorMultime;

    private:
		/* aici e reprezentarea */
		int cp;
		int lg;
		//vectorul static de elemente de tip TElem (cu spatiu fix de memorare = CAPACITATE)
		TElem* e;
		//vectorul static pentru legaturi
		int* urm;
		//referinta catre primul element al listei
		int prim;
		//referinta catre primul element din lista spatiului liber
		int primLiber;
		//lungimea listelor
		void redim();

		//functii de alocarea/dealocarea unui spatiu liber
		//se returneaza pozitia unui spatiu liber in lista
		int aloca();
		//dealoca spatiul de indice i
		void dealoca(int i);
		//functie care creeaza un nod in lista inlantuita
		int creeazaNod(TElem e);

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
		IteratorMultime iterator();

		// destructorul multimii
		~Multime();
};




