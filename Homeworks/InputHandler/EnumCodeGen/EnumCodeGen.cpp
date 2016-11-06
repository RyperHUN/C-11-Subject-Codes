// EnumCodeGen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class EnumCreator 
{
public:
	class EnumType
	{
	public:
		std::string name;
		EnumType(std::string name) : name(name) {}
		void AddEnumString(std::string _enum)
		{
			enums.push_back(_enum);
		}
		std::vector<std::string> enums;
	};

	EnumCreator (std::initializer_list<EnumType> list)
	{
		for (auto elem : list)
			enumTypes.push_back (elem);
	}
	

	void AddEnumType (EnumType const& enumType)
	{
		enumTypes.push_back (enumType);
	}

	void createFiles (std::string fileName)
	{
		std::ofstream file (fileName);
		prepareHeader (file);
		writeEnums (file);
		WriteStringToEnum (file);
		finishHeader (file);
	}
private:
	void prepareHeader (std::ofstream & file)
	{
		file << "#pragma once" << std::endl;
		file << "#include <map>" << std::endl << std::endl;

		file << "namespace InputMapping" << std::endl;
		file << "{" << std::endl << std::endl;
	}
	void writeEnums (std::ofstream & file)
	{
		std::string TAB = "\t";
		for (auto type : enumTypes)
		{
			file << TAB << "enum " << type.name << std::endl;
			file << TAB << "{" << std::endl;

			TAB = "\t\t";
			for (auto values : type.enums)
			{
				file << TAB << values << "," << std::endl;
			}

			TAB = "\t";
			file << TAB << "};" << std::endl << std::endl;
		}
	}
	void finishHeader (std::ofstream & file)
	{
		file << "}" << std::endl;
	}
	void WriteStringToEnum (std::ofstream & file)
	{
		std::string TAB = "\t";
		for (auto type : enumTypes)
		{
			const std::string className = std::string("StringTo").append(type.name);
			file << TAB << "struct " << className << " : public std::map<std::string, " << type.name << ">" << std::endl;
			file << TAB << "{" << std::endl;

			TAB = "\t\t";
			file << TAB << className << " ()" << std::endl;
			file << TAB << "{" << std::endl;
			TAB = "\t\t\t";
			for (auto values : type.enums)
			{
				file << TAB << "this->operator[](\"" << values << "\") = " << type.name << "::" << values << ";" << std::endl;
			}
			TAB = "\t\t";
			file << TAB << "}" << std::endl;

			file << TAB << "~" << className << "() {}" << std::endl;
			TAB = "\t";
			file << TAB << "};" << std::endl << std::endl;
		}
	}
private:
	std::vector<EnumType> enumTypes;
};

int main()
{
	EnumCreator::EnumType RawInputButton ("RawInputButton");
	RawInputButton.AddEnumString ("RAW_INPUT_BUTTON_W");
	RawInputButton.AddEnumString ("RAW_INPUT_BUTTON_A");
	RawInputButton.AddEnumString ("RAW_INPUT_BUTTON_S");
	RawInputButton.AddEnumString ("RAW_INPUT_BUTTON_D");

	EnumCreator::EnumType RawInputAxis ("RawInputAxis");
	RawInputAxis.AddEnumString ("RAW_INPUT_AXIS_MOUSE_X");
	RawInputAxis.AddEnumString ("RAW_INPUT_AXIS_MOUSE_Y");

	EnumCreator creator {RawInputButton, RawInputAxis};
	//Or creator.AddEnumType ()

	creator.createFiles ("RawInputConstants.h");

    return 0;
}

