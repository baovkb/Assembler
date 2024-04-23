#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum class FORMAT
{
	R_type,
	I_type,
	J_type
};

string DecToBinary(long n, int numberOfBits)
{
	bool isPos = true;
	if (n < 0)
	{
		isPos = false;
		n = -n;
	}

	if (pow(2, numberOfBits) <= n)
		return "\0";

	char *bin = new char[numberOfBits + 1];
	bin[numberOfBits] = '\0';

	int i = numberOfBits  - 1;
	while (n != 0)
	{
		bin[i--] = (char)(n % 2 + 48);
		n /= 2;
	}
	isPos ? bin[i] = '0' : bin[i] = '1';

	int j = numberOfBits - 1;
	if (!isPos)
	{
		while (j > i && bin[j] != '1')
			--j;
		--j;
		while (j > i)
		{
			if (bin[j] == '0')
				bin[j] = '1';
			else bin[j] = '0';
			--j;
		}
	}

	for (int k = i; k >= 0; --k)
		bin[k] = bin[i];

	string rel = bin;

	return rel;
}

long CoverFromStringToLong(string arg)
{
	int len = arg.length();
	long rel = 0;
	bool isPos = true;

	if (arg[0] == '-')
	{
		arg = arg.substr(1, len - 1);
		len = arg.length();
		isPos = false;
	}

	for (int i = 0; i < len; ++i)
		rel = rel + (arg[i] - 48) * pow(10, len - i - 1);

	return isPos ? rel : -rel;
}

int HexToDec(string oper)
{
	int len = oper.length();
	if (oper[0] == '0' && oper[1] == 'x')
	{
		string subtr = oper.substr(2, oper.length() - 1);
		oper = subtr;
		len = oper.length();
	}

	long Dex = 0;
	for (int i = 0; i < len; ++i)
	{
		if (oper[len - i - 1] >= '0' && oper[len - i - 1] <= '9')
			Dex += ((long)oper[len - i - 1] - 48) * pow(16, i);
		else if (oper[len - i - 1] >= 'A' && oper[len - i - 1] <= 'F')
			Dex += ((long)oper[len - i - 1] - 55) * pow(16, i);
		else if (oper[len - i - 1] >= 'a' && oper[len - i - 1] <= 'f')
			Dex += ((long)oper[len - i - 1] - 87) * pow(16, i);
	}
	return Dex;
}

bool isHex(string src)
{
	if (src.length() <= 2)
		return false;
	else
		if (src[0] == '0' && src[1] == 'x')
			return true;
		else return false;
}

string DexToHex(long n)
{
	char hexString[9];
	_itoa_s(n, hexString, 16);
	int len = strlen(hexString);

	string rel = "0x";

	for (int i = len; i < 8; ++i)
		rel += "0";
	rel += hexString;
	
	return rel;
}

string* Split(string src)
{
	string *arrayStr;
	int numberOfWord = 1;

	int len = src.length();
	int i;
	for (i = 0; i < len; ++i)
		if (src[i] == ' ')
			++numberOfWord;
	arrayStr = new string[numberOfWord];

	int k = 0;
	int j = 0;
	for (i = 0; i < numberOfWord; ++i)
	{
		string temp;
		while (j < len)
		{
			if (src[j] != ' ')
				temp += src[j];
			else
			{
				++j;
				break;
			}
			++j;
		}
		arrayStr[i] = temp;
	}

	return arrayStr;
}

string Register(string ins)
{
	if (ins == "$zero" || ins == "$0")
		return "00000";
	else if (ins == "$at" || ins == "$1")
		return "00001";
	else if (ins == "$v0" || ins == "$2")
		return "00010";
	else if (ins == "$v1" || ins == "$3")
		return "00011";
	else if (ins == "$a0" || ins == "$4")
		return "00100";
	else if (ins == "$a1" || ins == "$5")
		return "00101";
	else if (ins == "$a2" || ins == "$6")
		return "00110";
	else if (ins == "$a3" || ins == "$7")
		return "00111";
	else if (ins == "$t0" || ins == "$8")
		return "01000";
	else if (ins == "$t1" || ins == "$9")
		return "01001";
	else if (ins == "$t2" || ins == "$10")
		return "01010";
	else if (ins == "$t3" || ins == "$11")
		return "01011";
	else if (ins == "$t4" || ins == "$12")
		return "01100";
	else if (ins == "$t5" || ins == "$13")
		return "01101";
	else if (ins == "$t6" || ins == "$14")
		return "01110";
	else if (ins == "$t7" || ins == "$15")
		return "01111";
	else if (ins == "$s0" || ins == "$16")
		return "10000";
	else if (ins == "$s1" || ins == "$17")
		return "10001";
	else if (ins == "$s2" || ins == "$18")
		return "10010";
	else if (ins == "$s3" || ins == "$19")
		return "10011";
	else if (ins == "$s4" || ins == "$20")
		return "10100";
	else if (ins == "$s5" || ins == "$21")
		return "10101";
	else if (ins == "$s6" || ins == "$22")
		return "10110";
	else if (ins == "$s7" || ins == "$23")
		return "10111";
	else if (ins == "$t8" || ins == "$24")
		return "11000";
	else if (ins == "$t9" || ins == "$25")
		return "11001";
	else if (ins == "$k0" || ins == "$26")
		return "11010";
	else if (ins == "$k1" || ins == "$27")
		return "11011";
	else if (ins == "$gp" || ins == "$28")
		return "11100";
	else if (ins == "$sp" || ins == "$29")
		return "11101";
	else if (ins == "$fp" || ins == "$30")
		return "11110";
	else if (ins == "$ra" || ins == "$31")
		return "11111";
}

FORMAT Format(string command)
{
	if (command == "add" || command == "addu" || command == "and" || command == "jr" || command == "nor" || command == "or" || command == "slt" || command == "sltu" || command == "add" || command == "sll" || command == "srl" || command == "sub" || command == "subu" || command == "div" || command == "divu" || command == "mfhi" || command == "mflo" || command == "mfc0" || command == "mult" || command == "multu" || command == "sra")
		return FORMAT::R_type;
	else if (command == "addi" || command == "addiu" || command == "andi" || command == "beq" || command == "bne" || command == "lbu" || command == "lhu" || command == "ll" || command == "lui" || command == "lw" || command == "ori" || command == "slti" || command == "sltiu" || command == "sb" || command == "sc" || command == "sh" || command == "sw" || command == "lwcl" || command == "ldcl" || command == "swcl" || command == "sdcl")
		return FORMAT::I_type;
	else if (command == "j" || command == "jal")
		return FORMAT::J_type;
}

string Opcode(string instr)
{
	FORMAT ins = Format(instr);
	if (ins == FORMAT::R_type)
		return "000000";
	else if (ins == FORMAT::I_type)
	{
		if (instr == "addi")
			return "001000";
		else if (instr == "addiu")
			return "001001";
		else if (instr == "andi")
			return "001100";
		else if (instr == "beq")
			return "000100";
		else if (instr == "bne")
			return "000101";
		else if (instr == "lbu")
			return "100100";
		else if (instr == "lhu")
			return "100101";
		else if (instr == "ll")
			return "110000";
		else if (instr == "lui")
			return "001111";
		else if (instr == "lw")
			return "100011";
		else if (instr == "ori")
			return "001101";
		else if (instr == "slti")
			return "001010";
		else if (instr == "sltiu")
			return "001011";
		else if (instr == "sb")
			return "101000";
		else if (instr == "sc")
			return "111000";
		else if (instr == "sh")
			return "101001";
		else if (instr == "sw")
			return "101011";
		else if (instr == "lwcl")
			return "110001";
		else if (instr == "ldcl")
			return "110101";
		else if (instr == "swcl")
			return "111001";
		else if (instr == "sdcl")
			return "111101";
	}
	else if (ins == FORMAT::J_type)
	{
		if (instr == "j")
			return "000010";
		else if (instr == "jal")
			return "000011";
	}
}

string Function(string instr)
{
	FORMAT ins = Format(instr);
	if (ins == FORMAT::R_type)
	{
		if (instr == "add")
			return "100000";
		else if (instr == "addu")
			return "100001";
		else if (instr == "and")
			return "100100";
		else if (instr == "jr")
			return "001000";
		else if (instr == "nor")
			return "100111";
		else if (instr == "or")
			return "100101";
		else if (instr == "slt")
			return "101010";
		else if (instr == "sltu")
			return "101011";
		else if (instr == "sll")
			return "000000";
		else if (instr == "srl")
			return "000010";
		else if (instr == "sub")
			return "100010";
		else if (instr == "subu")
			return "100011";
		else if (instr == "div")
			return "011010";
		else if (instr == "divu")
			return "011011";
		else if (instr == "mfhi")
			return "010000";
		else if (instr == "mflo")
			return "010010";
		else if (instr == "mfc0")
			return "000000";
		else if (instr == "mult")
			return "011000";
		else if (instr == "multu")
			return "011001";
		else if (instr == "sra")
			return "000011";
	}
}

int PreProcessing(string *&AddressIns, int &numberOfLine)
{
	ifstream src;
	src.open("input.asm", ios::in);
	if (!src.is_open())
		return -1;

	// do file den khi xuat hien .text
	while (1)
	{
		string data;
		src >> data;
		if (data == ".text")
		{
			char c;
			src.get(c);
			break;
		}
		if (src.eof())
		{
			src.clear();
			src.seekg(0, ios::beg);
			break;
		}
	}

	if (!src.is_open())
		return -1;

	fstream tempFile;
	tempFile.open("temp.asm", ios::trunc | ios::out);
	if (!tempFile.is_open())
		return -1;

	string textFromFile;
	numberOfLine = 1;
	while (!src.eof())
	{
		getline(src, textFromFile);
		int len = textFromFile.length();

		int beg = 0;
		bool isComment = true;
		for (int i = 0; i < len; ++i)
		{
			if (textFromFile[i] == '#')
				break;
			if (textFromFile[i] != ' ' && textFromFile[i] != '\t')
			{
				beg = i;
				isComment = false;
				break;
			}
		}

		if (isComment == false)
		{
			int end = 0;
			for (int i = len - 1; i >= beg; --i)
			{
				if (textFromFile[i] != ' ' && end == 0 && textFromFile[i] != '\t')
					end = i;
				if (textFromFile[i] == '#')
					end = 0;
			}

			string formatText = "";

			int j = beg;
			while (j <= end)
			{
				if ((textFromFile[j] == ':' && j == end) || (textFromFile[j] != ' ' && textFromFile[j] != ',' && textFromFile[j] != '\t' && textFromFile[j] != '(' && textFromFile[j] != ')' && textFromFile[j] != ':'))
					formatText += textFromFile[j];
				else 
				{
					bool isEndL = false;
					if (textFromFile[j] == ':' && j != end)
						isEndL = true;
					if (j < end)
						++j;
					while (textFromFile[j] == ' ' || textFromFile[j] == '\t')
						++j;

					if (isEndL)
					{
						formatText += ":\n";
						numberOfLine++;
					}
					else if (textFromFile[j] != ')')
						formatText += ' ';
					else
						++j;
					continue;
				}

				++j;
			}

			tempFile << formatText << '\n';
			numberOfLine++;
		}
	}
	tempFile.close();
	src.close();

	AddressIns = new string[numberOfLine];
	tempFile.open("temp.asm", ios::in);
	//khoi tao dia chi lenh
	int i = 0;
	int j = 0;
	while (!tempFile.eof())
	{
		textFromFile = "";
		getline(tempFile, textFromFile);

		if (textFromFile != "" && textFromFile.back() == ':')
		{
			AddressIns[i] = textFromFile;
		}
		else
		{
			AddressIns[i] = DexToHex(HexToDec("0x00400000") + j * 4);
			j++;
		}
		++i;
	}
	tempFile.close();
}

int OutFile(string *AddressIns, int numberOfAddress)
{
	ifstream tempFile;
	ofstream outFile;

	tempFile.open("temp.asm", ios::in);
	if (!tempFile.is_open())
		return -1;

	outFile.open("output.asm", ios::trunc | ios::out);
	if (!outFile.is_open())
		return -1;

	string textFromFile;

	getline(tempFile, textFromFile);
	for (int curLine = 0; !tempFile.eof(); curLine++)
	{
		string bin = "";
		if (textFromFile == "syscall")
			bin += DecToBinary(HexToDec("0x0000000c"), 32);
		else if (textFromFile != "" && textFromFile.back() != ':')
		{
			string* data = Split(textFromFile);
			int insLen = data->length();
			bin = Opcode(data[0]); //opcode

			if (Format(data[0]) == FORMAT::R_type)
			{
				if (data[0] == "sll" || data[0] == "srl")
				{
					bin += "00000"; //rs
					bin += Register(data[2]); //rt
					bin += Register(data[1]); //rd
					bin += DecToBinary(CoverFromStringToLong(data[3]), 5); // shamp
					bin += Function(data[0]);
				}
				else if (data[0] == "jr")
				{
					bin += Register(data[1]);
					bin += "000000000000000";
					bin += Function(data[0]);
				}
				else
				{
					bin += Register(data[2]);
					bin += Register(data[3]);
					bin += Register(data[1]);
					bin += "00000";
					bin += Function(data[0]);
				}
			}
			else if (Format(data[0]) == FORMAT::I_type)
			{
				if (data[0] == "lui")
				{
					bin += "00000"; //rs
					bin += Register(data[1]); //rt
					if (isHex(data[2]))
						bin += DecToBinary(HexToDec(data[2]), 16);
					else bin += DecToBinary(CoverFromStringToLong(data[2]), 16);
				}
				else if (data[0] == "beq" || data[0] == "bne")
				{
					bin += Register(data[1]);
					bin += Register(data[2]);

					string temp = data[3] + ':';
					int count = 0;
					int i;
					for (i = curLine + 1; i < numberOfAddress; ++i) // tim phia sau 
					{
						if (AddressIns[i] == temp)
							break;
						if (isHex(AddressIns[i]))
							count++;
					}

					if (i >= numberOfAddress) // tim phia truoc
					{
						count = -1;
						for (i = curLine - 1; i >= 0; --i)
						{
							if (AddressIns[i] == temp)
								break;
							if (isHex(AddressIns[i]))
								count--;
						}
					}
					bin += DecToBinary(count, 16);
				}
				else if (data[0] == "addi" || data[0] == "addiu" || data[0] == "andi" || data[0] == "ori" || data[0] == "slti" || data[0] == "sltiu") // 
				{
					bin += Register(data[2]);
					bin += Register(data[1]);
					if (isHex(data[3]))
						bin += DecToBinary(HexToDec(data[3]), 16);
					else bin += DecToBinary(CoverFromStringToLong(data[3]), 16);
				}
				else // lenh store, load
				{
					bin += Register(data[3]);
					bin += Register(data[1]);
					if (isHex(data[2]))
						bin += DecToBinary(HexToDec(data[2]), 16);
					else bin += DecToBinary(CoverFromStringToLong(data[2]), 16);
				}
			}
			else if (Format(data[0]) == FORMAT::J_type)
			{
				string temp = data[1] + ':';
				int i;
				for (i = 0; i < numberOfAddress; ++i)
				{
					if (AddressIns[i] == temp)
					{
						++i;
						break;
					}
				}

				bin += DecToBinary(HexToDec(AddressIns[i]) / 4, 26); // dia chi dich phai 2 lan, => / 4
			}
		}
		else
		{
			getline(tempFile, textFromFile);
			continue;
		}
		outFile << bin << endl;
		getline(tempFile, textFromFile);
	}

	tempFile.close();
	outFile.close();
}

int main()
{
	string* AddressIns;
	int numberOfAddress = 0;
	PreProcessing(AddressIns, numberOfAddress);

	OutFile(AddressIns, numberOfAddress);

	return 0;
}