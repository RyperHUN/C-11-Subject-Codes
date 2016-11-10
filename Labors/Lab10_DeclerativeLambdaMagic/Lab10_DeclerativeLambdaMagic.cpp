// Lab10_DeclerativeLambdaMagic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <set>
#include <numeric>

template <typename VALUETYPE>
class Tester {
  public:
    /* Ilyen tároló tárolja az egyes változók lehetséges értékeit. */
    using Container = std::vector<VALUETYPE>;
    /* VariableValue: ez azt a változót reprezentálja, amely tesztelés
     * közben különféle értékeket vesz fel. Ha meghívjuk a függvényt,
     * megkapjuk az értéket. */
    using VariableValue = std::function<VALUETYPE()>;
    /* Constraint: egy olyan paraméter nélküli függvény, amely megmondja,
     * hogy az elvárt összefüggések épp teljesülnek-e. */
    using Constraint = std::function<bool()>;
    /* Activity: ilyen függvényt fog meghívni a Tester, amikor tesztelés
     * közben talál egy megoldást. */
    using Activity = std::function<void()>;


  private:
    using Iterator = typename Container::const_iterator;
    /* Lehetséges értékek: egy tartomány iterátorai, és az aktuális
     * értéket mutató iterátor. */
    struct Variable {
        Container values_;
        Iterator current_;
    };
    /* Ezeket a változókat kell vizsgálni */
    std::vector<Variable> variables_;
    /* Ezen feltételek szerint */
    std::vector<Constraint> constraints_;
  
  public:
    /* Egy változó lehetséges értékeit tartalmazó tárolót várja.
     * Ad egy olyan függvényt vissza, amelyet meghívva
     * lekérdezhetõ, hogy a tesztelés közben az adott változónak éppen
     * mi az értéke. A használó ezekre a függvényekre tud majd építeni.
     * Az std::vector push_back()-nél áthelyezheti a memóriában az
     * elemeket, így a vektorba tett current iterátor referenciáját
     * nem adhatjuk vissza. Helyette megjegyezzük, hogy a beszúrt
     * struktúra hányadik indexre került, és az kerül a lambdába. */
    VariableValue add_variable(Container values_) {
        variables_.push_back(Variable{values_, Iterator{}});
        size_t pos = variables_.size()-1;
        return [this, pos] () -> VALUETYPE {
            return *variables_[pos].current_;
        };
    }

    /* Feltétel hozzáadása. A feltétel egy függvény, amely igaz értéke
     * esetén az aktuális állapot elfogadható. */
    void add_constraint(Constraint values_) {
        constraints_.push_back(values_);
    }

    /* Teszteli az összes lehetséges értéket, és amikor olyan
     * állapotban vannak az iterátorok, amik épp egy elfogadható
     * kombinációra mutatnak, akkor meghívja a függvényt. */
    void solve(Activity do_what) {
        /* iterátorok inicializálása */
        for (auto & v : variables_)
            v.current_ = v.values_.begin();
        /* A Variable-k current iterátorait már mind begin-re
         * állítottuk, szóval most az elején áll az összes. */
        bool end = false;
        while (!end) {
            /* Jó az aktuális állapot? Ha mindegyik jó. */
            auto satisfied = std::all_of(
                constraints_.begin(), constraints_.end(),
                [] (Constraint cons) { return cons(); });
            /* Megfelel ez az állapot, ha mindegyik Constraint igazat válaszolt. */
            if (satisfied)
                do_what();

            /* Következõre ugrás: a digit "teljes összeadó"ja kódban. */
            bool carry = true;
            for (auto & v : variables_) {
                ++v.current_;
                carry = v.current_ == v.values_.end();
                if (carry)
                    v.current_ = v.values_.begin();
                else
                    break;
            }
            /* Ha vége lett, és még mindig carry=true, körbeértünk. */
            end = carry;
        }
    }
};


int main() {
	//Pitagoras numbers
	{
		std::vector<int> numbers(100);
		auto fill_with_num = std::iota<std::vector<int>::iterator,int>;
		fill_with_num(numbers.begin(), numbers.end(), 1);
		//for (auto i : numbers)
		//	std::cout << i << ' ';
		Tester<int> tester;

		auto a = tester.add_variable (numbers);
		auto b = tester.add_variable (numbers);
		auto c = tester.add_variable(numbers);
    
		// a < b 
		tester.add_constraint([=] {
			return a() < b();
		});
		// b < c
		tester.add_constraint([=] {
			return b() < c();
		});
		// a^2 + b^2 = c^2;
		tester.add_constraint([=] {
			return (a() * a() + b() * b()) == (c() * c()); 
		});

		auto print_nums = [=] {
			std::cout << a() << "+" << b() << "==" << c() << std::endl;
		};
		int counter = 0;
		auto count_nums = [&counter] { counter++; };
		tester.solve(count_nums);
		std::cout << "0-100 Pitagorean nums =" << counter << std::endl;
	}
}

