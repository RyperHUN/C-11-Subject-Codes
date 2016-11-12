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

	void createFile (std::string fileName)
	{
		std::ofstream file (fileName);
		prepareHeader (file);
		writeEnums (file);
		WriteStringToEnum (file);
		WriteEnumToString (file);
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
	void WriteEnumToString (std::ofstream & file)
	{
		std::string TAB = "\t";
		for (const auto& type : enumTypes)
		{
			const std::string className = std::string(type.name).append("ToString");
			file << TAB << "struct " << className << " : public std::map<" << type.name << ", std::string> " << std::endl;
			file << TAB << "{" << std::endl;

			TAB = "\t\t";
			file << TAB << className << " ()" << std::endl;
			file << TAB << "{" << std::endl;
			TAB = "\t\t\t";
			for (auto values : type.enums)
			{
				file << TAB << "this->operator[](" << type.name << "::" << values << ") = \"" << values << "\";" << std::endl;
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
	RawInputButton.AddEnumString ("RAW_INPUT_BUTTON_K");
	RawInputButton.AddEnumString ("RAW_INPUT_BUTTON_L");

	EnumCreator::EnumType RawInputAxis ("RawInputAxis");
	RawInputAxis.AddEnumString ("RAW_INPUT_AXIS_MOUSE_X");
	RawInputAxis.AddEnumString ("RAW_INPUT_AXIS_MOUSE_Y");
	
	//THis can be used to index array
	EnumCreator::EnumType RawGamePadInput ("RawGamePadInput");
	RawGamePadInput.AddEnumString("A"); // = 0
	RawGamePadInput.AddEnumString("B"); // = 1
	RawGamePadInput.AddEnumString("X"); // = 2
	RawGamePadInput.AddEnumString("Y"); // = 3

	RawGamePadInput.AddEnumString("DPad_Up"); // = 4
	RawGamePadInput.AddEnumString("DPad_Down"); // = 5
	RawGamePadInput.AddEnumString("DPad_Left"); // = 6
	RawGamePadInput.AddEnumString("DPad_Right"); // = 7

	RawGamePadInput.AddEnumString("L_Shoulder"); // = 8
	RawGamePadInput.AddEnumString("R_Shoulder"); // = 9

	RawGamePadInput.AddEnumString("L_Thumbstick"); // = 10
	RawGamePadInput.AddEnumString("R_Thumbstick"); // = 11

	RawGamePadInput.AddEnumString("Start"); // = 12
	RawGamePadInput.AddEnumString("Back"); // = 13

	EnumCreator creatorRaw {RawInputButton, RawInputAxis, RawGamePadInput};
	//Or creator.AddEnumType ()

	creatorRaw.createFile ("../Skeleton/Input/RawInputConstants.h");

	EnumCreator::EnumType Actions("Actions");
	Actions.AddEnumString ("Teleport");

	EnumCreator::EnumType Axises("Axises");
	Axises.AddEnumString ("MoveX");
	Axises.AddEnumString ("MoveY");

	EnumCreator::EnumType States("States");
	States.AddEnumString ("Sprint");

	EnumCreator creatorHighLevel {Actions, Axises, States};

	creatorHighLevel.createFile ("../Skeleton/Input/HighLevelInputConstants.h");

    return 0;
}

