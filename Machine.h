#pragma once
#ifndef _MACHINE_HPP
#define _MACHINE_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
using namespace std;

class MainMemory;
class Register;
class Machine;
class Simulator;


//Main Memory class
class MainMemory
{
private:
	vector <vector<string>> cells;
	int size;
public:
	MainMemory();

	string getCell(string address);

	void store(string data, string address);
	void loadFile(string filename);
	void loadInput(const char* userInput);
	void display();
	void clear();
};

//

// Register class

class Register
{
private:
	vector <string> values;
	int size;
public:
	Register();

	string getRegister(char address);
	void store(string data, char address);
	void display();
	void clear();
};

//


class Machine:public MainMemory ,public Register
{
protected:
	MainMemory Memory;
	Register registers;
	string IR;
	int ProgramCounter;
	bool Halt;
public:
	Machine();
	bool getHalt();
	void setHalt(bool halt);
	int  getCounter();
	string getInstruction();
	string getMemoryCell(string address);
	string getMemoryRegister(char address);
	void clearMemory();
	void clearRegister();
	

	void loadProgramInput(const char* userInput);
	void loadProgramFile(string filename);
	void fetchProgramInstruction();
	void executeProgramInstrction();
	void displayCurrentStatus();
};

class Simulator : public Machine
{
private:
	Machine voleMachine;
public:
	void Menu();
	void loadProgramFile(string filename);
	void executeProgram();
	void displayMachineStatus();
};


#endif

int hexToDecimal(const string& hex);

string decimalToHex(int decimalNum);
