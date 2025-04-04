#pragma once
#ifndef OBSERVER_H
#define OBSERVER_H
#include <algorithm>
#include <vector>

using std::vector;

class Observer {
public:
	virtual void update() = 0;
};

class Observable {
private:
	vector<Observer*> observers;
protected:
	void notify() {
		for (auto obs : observers) {
			obs->update();
		}
	}
public:
	void adaugaObserver(Observer* obs) {
		observers.push_back(obs);
	}
	void stergeObserver(Observer* obs) {
		observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
	}
};

#endif // !OBSERVER_H