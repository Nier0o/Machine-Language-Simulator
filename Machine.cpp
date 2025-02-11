// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Machine.h"

int hexToDecimal(const std::string& hex) {
	int decimalNum;
	std::istringstream(hex) >> std::hex >> decimalNum;
	return decimalNum;
}

string decimalToHex(int decimalNum) {
	std::stringstream ss;
	ss << std::hex << decimalNum;
	return ss.str();
}

void Simulator::Menu()
{
	
	cout << "Welcome to Vole Machine Simulator.\n";
	
	cout << endl;
	while (!voleMachine.getHalt())
	{
		int n;
		cout << endl;
		cout << "To load data from file Press 1\n"; 
		cout << "To excute single step Press 2\n";
		cout << "To clear memory Press 3\n";
		cout << "To clear registers Press 4\n";
		cout << "To run the program Press 5\n";
		cout << "To halt the program Press 6\n";
		cout << endl;
		cout << "Enter Your Choice: ";
		cout << endl;
		cin >> n;
		if (n == 1)
		{
			string filename;
			cout << "Please enter the date file name (example.txt): ";
			cin >> filename;
			voleMachine.loadProgramFile(filename);
			cout << endl;
			voleMachine.displayCurrentStatus();
		}
		else if (n == 2)
		{
			voleMachine.fetchProgramInstruction();
			voleMachine.executeProgramInstrction();
			cout << endl;
			this->displayMachineStatus();
		}
		else if (n == 3)
		{
			voleMachine.clearMemory();
			cout << endl;
			this->displayMachineStatus();
		}
		else if (n == 4)
		{
			voleMachine.clearRegister();
			cout << endl;
			this->displayMachineStatus();
		}
		else if (n == 5)
		{
			this->executeProgram();
			this->displayMachineStatus();
		}
		else if (n == 6)
		{
			break;
		}
	}
}

void Simulator::loadProgramFile(string filename)
{
	voleMachine.loadProgramFile(filename);
}

void Simulator::executeProgram()
{
	while (!voleMachine.getHalt())
	{
		voleMachine.fetchProgramInstruction();
		voleMachine.executeProgramInstrction();
	}
}

void Simulator::displayMachineStatus()
{
	voleMachine.displayCurrentStatus();
}

//MainMemory class

MainMemory::MainMemory() : size(256)
{
	cells.resize(16, vector<string>(16));
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			cells[i][j] = "00";
		}
	}
}

void MainMemory::store(string data, string address)
{
	int address0, address1;
	if (isalpha(address[0]))
	{
		address0 = address[0] - '7';
	}
	else address0 = address[0] - '0';

	if (isalpha(address[1]))
	{
		address1 = address[1] - '7';
	}
	else address1 = address[1] - '0';

	cells[address0][address1] = data;
}

string MainMemory::getCell(string address)
{
	int address0, address1;
	if (isalpha(address[0]))
	{
		address0 = address[0] - '7';
	}
	else address0 = address[0] - '0';

	if (isalpha(address[1]))
	{
		address1 = address[1] - '7';
	}
	else address1 = address[1] - '0';

	return cells[address0][address1];
}

void MainMemory::loadFile(string filename)
{
	string line;
	ifstream file(filename);
	if (file.is_open())
	{
		int row = 0, col = 0;
		while (getline(file, line))
		{
			if (col >= 16)
			{
				row++;
				col = 0;
			}
			cells[row][col] = line.substr(2, 1) + line.substr(6, 1);
			cells[row][col + 1] = line.substr(10, 2);
			col += 2;
		}
		file.close();
	}
	else cout << "Error opening file";

}
void MainMemory::loadInput(const char* userInput)
{
	stringstream ss(userInput);
	string line;
	int row = 0, col = 0;
	while (getline(ss, line))
	{
		if (col >= 16)
		{
			row++;
			col = 0;
		}  
		char c_row = (row < 10) ? ('0' + row) : ('7' + row);
		char c_col1 = (col < 10) ? ('0' + col) : ('7' + col);
		char c_col2 = (col + 1 < 10) ? ('0' + col + 1) : ('7' + col + 1);

		cells[row][col] = line.substr(2, 1) + line.substr(6, 1);
		cells[row][col + 1] = line.substr(10, 2);
		col += 2;
	}
}

void MainMemory::display()
{
	cout << "   0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F\n";
	char c;
	for (int i = 0; i < 16; i++)
	{
		if (i < 10) c = '0' + i;
		else c = '7' + i;

		cout << c << "  ";
		for (int j = 0; j < 16; j++)
		{
			cout << cells[i][j] << "  ";
		}
		cout << endl;
		cout << endl;
	}
}

void MainMemory::clear()
{
	for (int i = 0; i < size / 2; i++)
	{
		for (int j = 0; j < size / 2; j++)
		{
			cells[i][j] = "00";
		}
	}
}

//end of MainMemory class

//Register class

Register::Register() : size(16)
{
	values.resize(size, "00");
}

string Register::getRegister(char address)
{
	int address0;
	if (isalpha(address)) address0 = address - '7';
	else address0 = address - '0';

	return values[address0];
}

void Register::store(string data, char address)
{
	int address0;
	if (isalpha(address)) address0 = address - '7';
	else address0 = address - '0';

	values[address0] = data;
}

void Register::display()
{
	char c;
	for (int i = 0; i < 16; i++)
	{
		if (i < 10) c = '0' + i;
		else c = '7' + i;

		cout << 'R' << c << " " << values[i] << endl;
	}
}

void Register::clear()
{
	fill(values.begin(), values.end(), "00");
}

//end of Register class

//Instruction class

//end of Instruction class

//Machine class
Machine::Machine() : ProgramCounter(0), IR("0000"), Halt(0) {}

void Machine::loadProgramFile(string filename)
{
	Memory.loadFile(filename);
}


void Machine::fetchProgramInstruction() 
{
	int row, col;
	row = ProgramCounter / 16;
	if (ProgramCounter < 16) col = ProgramCounter;
	else col = ProgramCounter % 16;

	string rowstr, colstr1, colstr2;
	if (row > 9) rowstr = '7' + row;
	else rowstr = row + '0';
	if (col > 9) colstr1 = '7' + col;
	else colstr1 = col + '0';
	if (col + 1 > 9) colstr2 = '7' + col + 1;
	else colstr2 = col + '0' + 1;

	IR = Memory.getCell(rowstr + colstr1) + Memory.getCell(rowstr + colstr2);
	ProgramCounter += 2;
}

void Machine::executeProgramInstrction()
{
	if (IR[0] == '1')
	{
		if (isalpha(IR[1])) IR[1] = toupper(IR[1]);
		if (isalpha(IR[2])) IR[2] = toupper(IR[2]);
		if (isalpha(IR[3])) IR[3] = toupper(IR[3]);
		string data, str;
		str = IR.substr(2, 2);
		data = Memory.getCell(str);
		registers.store(data, IR[1]);
	}
	else if (IR[0] == '2')
	{
		string str;
		str = IR.substr(2, 2);
		registers.store(str, IR[1]);
	}
	else if (IR[0] == '3')
	{
		if (isalpha(IR[1])) IR[1] = toupper(IR[1]);
		if (isalpha(IR[2])) IR[2] = toupper(IR[2]);
		if (isalpha(IR[3])) IR[3] = toupper(IR[3]);
		string str, address;
		str = registers.getRegister(IR[1]);
		address = IR.substr(2, 2);
		if (address == "00")
		{
			cout << str << endl;
		}
		else
		{
			Memory.store(str, address);
		}
	}
	else if (IR[0] == '4' && IR[1] == '0')
	{
		if (isalpha(IR[1])) IR[1] = toupper(IR[1]);
		if (isalpha(IR[2])) IR[2] = toupper(IR[2]);
		if (isalpha(IR[3])) IR[3] = toupper(IR[3]);
		string str = registers.getRegister(IR[2]);
		registers.store(str, IR[3]);
	}
	else if (IR[0] == '5')
	{
		if (isalpha(IR[1])) IR[1] = toupper(IR[1]);
		if (isalpha(IR[2])) IR[2] = toupper(IR[2]);
		if (isalpha(IR[3])) IR[3] = toupper(IR[3]);
		string hex1, hex2;
		hex1 =  registers.getRegister(IR[2]);
		hex2 =  registers.getRegister(IR[3]);

		int dec1 = hexToDecimal(hex1);
		int dec2 = hexToDecimal(hex2);

		int sum = dec1 + dec2;

		string hexSum = decimalToHex(sum);
		
		registers.store(hexSum, IR[1]);
		
	}
	else if (IR[0] == 'B' || IR[0] == 'b')
	{
		string str0 = registers.getRegister('0');
		string str1 = registers.getRegister(IR[1]);

		if (str0 == str1)
		{
			int index1, index2;
			if (isalpha(IR[2])) index1 = IR[2] - '7';
			else index1 = IR[2] - '0';
			if (isalpha(IR[3])) index2 = IR[3] - '7';
			else index2 = IR[3] - '0';

			
			if ((index1 * index2) % 2 != 0) ProgramCounter = (index1 * 16) + index2 + 1;
			else ProgramCounter = (index1 * 16) + index2;
		}
	}
	else if (IR[0] == 'c' || IR[0] == 'C')
	{
		Halt = 1;
	}

	if (ProgramCounter >= 256) Halt = 1;
}

bool Machine::getHalt()
{
	return Halt;
}

void Machine::setHalt(bool halt)
{
	Halt = halt;
}

void Machine::clearMemory()
{
	Memory.clear();
}

void Machine::clearRegister()
{
	registers.clear();
}

int Machine::getCounter()
{
	return ProgramCounter;
}

string Machine::getInstruction()
{
	return IR;
}

string Machine::getMemoryCell(string address)
{
	return Memory.getCell(address);
}

string Machine::getMemoryRegister(char address)
{
	return registers.getRegister(address);
}

void Machine::loadProgramInput(const char* userInput)
{
	Memory.loadInput(userInput);
}

void Machine::displayCurrentStatus()
{
	Memory.display();
	cout << endl;
	registers.display();
}