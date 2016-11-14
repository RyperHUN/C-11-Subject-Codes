// 7_TesterImprovement.cpp : Defines the entry point for the console application.
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
	/* Ilyen tĂĄrolĂł tĂĄrolja az egyes vĂĄltozĂłk lehetsĂŠges ĂŠrtĂŠkeit. */
	using Container = std::vector<VALUETYPE>;
	/* VariableValue: ez azt a vĂĄltozĂłt reprezentĂĄlja, amely tesztelĂŠs
	* kĂśzben kĂźlĂśnfĂŠle ĂŠrtĂŠkeket vesz fel. Ha meghĂ­vjuk a fĂźggvĂŠnyt,
	* megkapjuk az ĂŠrtĂŠket. */
	using VariableValue = std::function<VALUETYPE ()>;
	/* Constraint: egy olyan paramĂŠter nĂŠlkĂźli fĂźggvĂŠny, amely megmondja,
	* hogy az elvĂĄrt ĂśsszefĂźggĂŠsek ĂŠpp teljesĂźlnek-e. */
	using Constraint = std::function<bool ()>;
	/* Activity: ilyen fĂźggvĂŠnyt fog meghĂ­vni a Tester, amikor tesztelĂŠs
	* kĂśzben talĂĄl egy megoldĂĄst. */
	using Activity = std::function<void ()>;


private:
	using Iterator = typename Container::const_iterator;
	/* LehetsĂŠges ĂŠrtĂŠkek: egy tartomĂĄny iterĂĄtorai, ĂŠs az aktuĂĄlis
	* ĂŠrtĂŠket mutatĂł iterĂĄtor. */
	struct Variable {
		Container values_;
		Iterator current_;
	};
	/* Ezeket a vĂĄltozĂłkat kell vizsgĂĄlni */
	std::vector<Variable> variables_;
	/* Ezen feltĂŠtelek szerint */
	std::vector<Constraint> constraints_;

public:
	/* Egy vĂĄltozĂł lehetsĂŠges ĂŠrtĂŠkeit tartalmazĂł tĂĄrolĂłt vĂĄrja.
	* Ad egy olyan fĂźggvĂŠnyt vissza, amelyet meghĂ­vva
	* lekĂŠrdezhetĹ, hogy a tesztelĂŠs kĂśzben az adott vĂĄltozĂłnak ĂŠppen
	* mi az ĂŠrtĂŠke. A hasznĂĄlĂł ezekre a fĂźggvĂŠnyekre tud majd ĂŠpĂ­teni.
	* Az std::vector push_back()-nĂŠl ĂĄthelyezheti a memĂłriĂĄban az
	* elemeket, Ă­gy a vektorba tett current iterĂĄtor referenciĂĄjĂĄt
	* nem adhatjuk vissza. Helyette megjegyezzĂźk, hogy a beszĂşrt
	* struktĂşra hĂĄnyadik indexre kerĂźlt, ĂŠs az kerĂźl a lambdĂĄba. */
	VariableValue add_variable (Container values_)
	{
		variables_.push_back (Variable{values_, Iterator{}});
		size_t pos = variables_.size () - 1;
		return [this, pos]() -> VALUETYPE {
			return *variables_[pos].current_;
		};
	}

	/* FeltĂŠtel hozzĂĄadĂĄsa. A feltĂŠtel egy fĂźggvĂŠny, amely igaz ĂŠrtĂŠke
	* esetĂŠn az aktuĂĄlis ĂĄllapot elfogadhatĂł. */
	void add_constraint (Constraint values_)
	{
		constraints_.push_back (values_);
	}

	/* Teszteli az Ăśsszes lehetsĂŠges ĂŠrtĂŠket, ĂŠs amikor olyan
	* ĂĄllapotban vannak az iterĂĄtorok, amik ĂŠpp egy elfogadhatĂł
	* kombinĂĄciĂłra mutatnak, akkor meghĂ­vja a fĂźggvĂŠnyt. */
	void solve (Activity do_what)
	{
		/* iterĂĄtorok inicializĂĄlĂĄsa */
		for (auto & v : variables_)
			v.current_ = v.values_.begin ();
		/* A Variable-k current iterĂĄtorait mĂĄr mind begin-re
		* ĂĄllĂ­tottuk, szĂłval most az elejĂŠn ĂĄll az Ăśsszes. */
		bool end = false;
		while (!end) {
			/* JĂł az aktuĂĄlis ĂĄllapot? Ha mindegyik jĂł. */
			auto satisfied = std::all_of (
				constraints_.begin (), constraints_.end (),
				[](Constraint cons) { return cons (); });
			/* Megfelel ez az ĂĄllapot, ha mindegyik Constraint igazat vĂĄlaszolt. */
			if (satisfied)
				do_what ();

			/* KĂśvetkezĹre ugrĂĄs: a digit "teljes ĂśsszeadĂł"ja kĂłdban. */
			bool carry = true;
			for (auto & v : variables_) {
				++v.current_;
				carry = v.current_ == v.values_.end ();
				if (carry)
					v.current_ = v.values_.begin ();
				else
					break;
			}
			/* Ha vĂŠge lett, ĂŠs mĂŠg mindig carry=true, kĂśrbeĂŠrtĂźnk. */
			end = carry;
		}
	}
};


int main ()
{
	Tester<int> t;

	// Baker, Cooper, Fletcher, Miller ĂŠs Smith egy Ăśtemeletes hĂĄz
	auto baker = t.add_variable ({1, 2, 3, 4, 5});
	auto cooper = t.add_variable ({1, 2, 3, 4, 5});
	auto fletcher = t.add_variable ({1, 2, 3, 4, 5});
	auto miller = t.add_variable ({1, 2, 3, 4, 5});
	auto smith = t.add_variable ({1, 2, 3, 4, 5});

	// kĂźlĂśnbĂśzĹ emeletein laknak.
	auto guys ={baker, cooper, fletcher, miller, smith};
	t.add_constraint ([=]() -> bool {
		std::set<int> s;
		for (auto f : guys)
			s.insert (f ());
		return s.size () == guys.size ();
	});
	// Baker nem a legfĂślsĹ emeleten lakik,
	t.add_constraint ([=]()  mutable -> bool { return baker () != 5; });
	// Cooper pedig nem az alsĂł szinten.
	t.add_constraint ([=] { return cooper () != 1; });
	// Fletcher lakhelye sem a legalsĂł szinten van, de nem is a legfĂślsĹn.
	t.add_constraint ([=] { return fletcher () != 1 && fletcher () != 5; });
	// Miller magasabban lakik, mint Cooper. 
	t.add_constraint ([=] { return miller () > cooper (); });
	// Smith nem Fletcherrel szomszĂŠdos emeleten lakik,
	t.add_constraint ([=] { return abs (smith () - fletcher ()) != 1; });
	// ahogy Cooper ĂŠs Fletcher sem emelet-szomszĂŠdok.
	t.add_constraint ([=] { return abs (cooper () - fletcher ()) != 1; });

	// A kĂŠrdĂŠs: melyik emelet kiĂŠ?
	auto print_all = [=] {
		std::cout << "Baker " << baker () << std::endl
			<< "Cooper " << cooper () << std::endl
			<< "Fletcher " << fletcher () << std::endl
			<< "Miller " << miller () << std::endl
			<< "Smith " << smith () << std::endl;
	};
	t.solve (print_all);
}
