// Lab10_DeclerativeLambdaMagic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <set>

template <typename VALUETYPE>
class Tester {
public:
	/* Ilyen t�rol� t�rolja az egyes v�ltoz�k lehets�ges �rt�keit. */
	using Container = std::vector<VALUETYPE>;
	/* VariableValue: ez azt a v�ltoz�t reprezent�lja, amely tesztel�s
	* k�zben k�l�nf�le �rt�keket vesz fel. Ha megh�vjuk a f�ggv�nyt,
	* megkapjuk az �rt�ket. */
	using VariableValue = std::function<VALUETYPE()>;
	/* Constraint: egy olyan param�ter n�lk�li f�ggv�ny, amely megmondja,
	* hogy az elv�rt �sszef�gg�sek �pp teljes�lnek-e. */
	using Constraint = std::function<bool()>;
	/* Activity: ilyen f�ggv�nyt fog megh�vni a Tester, amikor tesztel�s
	* k�zben tal�l egy megold�st. */
	using Activity = std::function<void()>;


private:
	using Iterator = typename Container::const_iterator;
	/* Lehets�ges �rt�kek: egy tartom�ny iter�torai, �s az aktu�lis
	* �rt�ket mutat� iter�tor. */
	struct Variable {
		Container values_;
		Iterator current_;
	};
	/* Ezeket a v�ltoz�kat kell vizsg�lni */
	std::vector<Variable> variables_;
	/* Ezen felt�telek szerint */
	std::vector<Constraint> constraints_;

public:
	/* Egy v�ltoz� lehets�ges �rt�keit tartalmaz� t�rol�t v�rja.
	* Ad egy olyan f�ggv�nyt vissza, amelyet megh�vva
	* lek�rdezhet�, hogy a tesztel�s k�zben az adott v�ltoz�nak �ppen
	* mi az �rt�ke. A haszn�l� ezekre a f�ggv�nyekre tud majd �p�teni.
	* Az std::vector push_back()-n�l �thelyezheti a mem�ri�ban az
	* elemeket, �gy a vektorba tett current iter�tor referenci�j�t
	* nem adhatjuk vissza. Helyette megjegyezz�k, hogy a besz�rt
	* strukt�ra h�nyadik indexre ker�lt, �s az ker�l a lambd�ba. */
	VariableValue add_variable(Container values_) {
		variables_.push_back(Variable{ values_, Iterator{} });
		size_t pos = variables_.size() - 1;
		return [this, pos]() -> VALUETYPE {
			return *variables_[pos].current_;
		};
	}

	/* Felt�tel hozz�ad�sa. A felt�tel egy f�ggv�ny, amely igaz �rt�ke
	* eset�n az aktu�lis �llapot elfogadhat�. */
	void add_constraint(Constraint values_) {
		constraints_.push_back(values_);
	}

	/* Teszteli az �sszes lehets�ges �rt�ket, �s amikor olyan
	* �llapotban vannak az iter�torok, amik �pp egy elfogadhat�
	* kombin�ci�ra mutatnak, akkor megh�vja a f�ggv�nyt. */
	void solve(Activity do_what) {
		/* iter�torok inicializ�l�sa */
		for (auto & v : variables_)
			v.current_ = v.values_.begin();
		/* A Variable-k current iter�torait m�r mind begin-re
		* �ll�tottuk, sz�val most az elej�n �ll az �sszes. */
		bool end = false;
		while (!end) {
			/* J� az aktu�lis �llapot? Ha mindegyik j�. */
			auto satisfied = std::all_of(
				constraints_.begin(), constraints_.end(),
				[](Constraint cons) { return cons(); });
			/* Megfelel ez az �llapot, ha mindegyik Constraint igazat v�laszolt. */
			if (satisfied)
				do_what();

			/* K�vetkez�re ugr�s: a digit "teljes �sszead�"ja k�dban. */
			bool carry = true;
			for (auto & v : variables_) {
				++v.current_;
				carry = v.current_ == v.values_.end();
				if (carry)
					v.current_ = v.values_.begin();
				else
					break;
			}
			/* Ha v�ge lett, �s m�g mindig carry=true, k�rbe�rt�nk. */
			end = carry;
		}
	}
};


int main() {
	Tester<int> t;

	// Baker, Cooper, Fletcher, Miller �s Smith egy �temeletes h�z
	auto baker = t.add_variable({ 1, 2, 3, 4, 5 });
	auto cooper = t.add_variable({ 1, 2, 3, 4, 5 });
	auto fletcher = t.add_variable({ 1, 2, 3, 4, 5 });
	auto miller = t.add_variable({ 1, 2, 3, 4, 5 });
	auto smith = t.add_variable({ 1, 2, 3, 4, 5 });

	// k�l�nb�z� emeletein laknak.
	auto guys = { baker, cooper, fletcher, miller, smith };
	t.add_constraint([=]() -> bool {
		std::set<int> s;
		for (auto f : guys)
			s.insert(f());
		return s.size() == guys.size();
	});
	// Baker nem a legf�ls� emeleten lakik,
	t.add_constraint([=]()  mutable -> bool { return baker() != 5; });
	// Cooper pedig nem az als� szinten.
	t.add_constraint([=] { return cooper() != 1; });
	// Fletcher lakhelye sem a legals� szinten van, de nem is a legf�ls�n.
	t.add_constraint([=] { return fletcher() != 1 && fletcher() != 5; });
	// Miller magasabban lakik, mint Cooper. 
	t.add_constraint([=] { return miller() > cooper(); });
	// Smith nem Fletcherrel szomsz�dos emeleten lakik,
	t.add_constraint([=] { return abs(smith() - fletcher()) != 1; });
	// ahogy Cooper �s Fletcher sem emelet-szomsz�dok.
	t.add_constraint([=] { return abs(cooper() - fletcher()) != 1; });

	// A k�rd�s: melyik emelet ki�?
	auto print_all = [=] {
		std::cout << "Baker " << baker() << std::endl
			<< "Cooper " << cooper() << std::endl
			<< "Fletcher " << fletcher() << std::endl
			<< "Miller " << miller() << std::endl
			<< "Smith " << smith() << std::endl;
	};
	t.solve(print_all);
}

