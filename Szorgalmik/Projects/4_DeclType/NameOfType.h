#pragma once

#include <iostream>
#include <string>
#include <cmath>

template <typename T>
struct NameOfType {
};

/* beÊpített típusok (mÊg lehetne pårat) */
template <>
struct NameOfType<int> {
	static std::string get() { return "int"; }
};

template <>
struct NameOfType<char> {
	static std::string get() { return "char"; }
};

template <>
struct NameOfType<double> {
	static std::string get() { return "double"; }
};

template <>
struct NameOfType<void> {
	static std::string get() { return "void"; }
};

/* módosítók - tÜmb */
template <typename T, size_t S>
struct NameOfType<T[S]> {
	static std::string get() {
		char s[100];
		sprintf(s, "%d", (int)S);
		return "array[" + std::string(s) + "] of " + NameOfType<T>::get();
	}
};

template <typename T, size_t S>
struct NameOfType<T const[S]> {
	static std::string get() {
		char s[100];
		sprintf(s, "%d", (int)S);
		return "array[" + std::string(s) + "] of " + NameOfType<T const>::get();
	}
};

/* módosítók */
template <typename T>
struct NameOfType<T const> {
	static std::string get() { return NameOfType<T>::get() + " const"; }
};

template <typename T>
struct NameOfType<T &> {
	static std::string get() { return "reference of " + NameOfType<T>::get(); }
};

template <typename T>
struct NameOfType<T &&> {
	static std::string get() { return "rvalue reference of " + NameOfType<T>::get(); }
};

template <typename T>
struct NameOfType<T *> {
	static std::string get() { return "pointer to " + NameOfType<T>::get(); }
};

/* nulla paramÊterŹ fßggvÊny */
template <typename RET>
struct NameOfType<RET()> {
	static std::string get() { return "function of () returning " + NameOfType<RET>::get(); }
};

/* fßggvÊny egy paramÊterrel */
template <typename RET, typename ARG>
struct NameOfType<RET(ARG)> {
	static std::string get() { return "function of (" + NameOfType<ARG>::get() + ") returning " + NameOfType<RET>::get(); }
};
