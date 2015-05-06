// TestLexicalAnalayser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <LexicalAnalyser.h>
#include <FileInputStream.h>
#include <TokenClass.h>
#include <IParser.h>
#include <UCFParser.h>
#include <fstream>
using namespace obaro::lexical;
using namespace obaro::io;
using namespace obaro::parsers;

class SimpleDemo
{
private:
	LexicalAnalyser *__lexer;
	std::string __source;
	void __parser();
	void __finished();
	void __continueStart();
public:
	SimpleDemo(LexicalAnalyser *lexer);
	void start();


};

class Console
{

protected:
	Console();
private:
	static void write(std::string out);
public:

	static std::string prompt(std::string output);
	static bool isExists(std::string filename);
	static void writeln(std::string output);

	class Path
	{
	private:
		static std::string __getFileExtension(const std::string FileName);
	public:
		Path();
		static bool	isExtensionEqual(std::string filename, std::string exe);

	};
};


int _tmain(int argc, _TCHAR* argv[])
{

	LexicalAnalyser *__lexer = new LexicalAnalyser();
	__lexer->prepare();

	//Delay starts here 
	SimpleDemo *demoParser = new SimpleDemo(__lexer);
	demoParser->start();







	getchar();
	return 0;
}






//Simple demo methjods

SimpleDemo::SimpleDemo(LexicalAnalyser * lexer)
{
	this->__lexer = lexer;
}

void SimpleDemo::start()
{

	if (this->__lexer != NULL)
	{

		this->__source = Console::prompt("\nEnter source file path or [e] to exit ? ");
		if (this->__source.size() > 0)
		{
			char c = this->__source.at(0);
			if (!Console::isExists(this->__source) && (c == 'E' || c == 'e'))
			{
				this->__finished();
				return;
			}
			this->__continueStart();
		}
		

	}
	else
		Console::writeln("Error: lexer not set!");
}

void SimpleDemo::__finished()
{
	//finished
	Console::writeln("\nFinished build");
}
void SimpleDemo::__continueStart()
{
	if (Console::isExists(this->__source))
	{
		//it exist
		if (Console::Path::isExtensionEqual(this->__source, "ucf"))
		{
			//yes its has that extensions
			__lexer->setSource(new FileInputStream(this->__source));
			this->__parser();
			this->__finished();

		}
		else
			Console::writeln("Error: filename must have an extension of .ucf");

	}
	else
		Console::writeln("\nError: this path" + this->__source + "does not exists ");

	//call the method again
	start();
}
	

//method
void SimpleDemo::__parser()
{
	//start parsing programming language
	IParser * parser =  new UCFParser(this->__lexer);
	IExpression *node = parser->parse();




}


//implementation of the console class

Console::Console()
{

}

std::string Console::prompt(std::string msg)
{
	//print the message to the console
	Console::write(msg);
	std::string input;
	std::getline(std::cin, input);
	//clear and resert std input
   //	std::cin.clear();
	//std::cin.ignore(INT_MAX, '\n');
	return input;

}
void Console::writeln(std::string out)
{
	Console::write(out + "\n");
}
void Console::write(std::string out)
{
	std::cout << out;
}
bool Console::isExists(std::string filename)
{
	std::ifstream ifile(filename);
	if (ifile)
	{
		return true;
	}
	return false;
}


//implement inner path class 
Console::Path::Path()
{
	//do nothing
}
bool Console::Path::isExtensionEqual(const std::string filename, const std::string __ext)
{

	std::string ext__ = Path::__getFileExtension(filename);
	if (ext__.compare(__ext) == 0)
	{
		return true;
	}
	return false;
}

std::string Console::Path::__getFileExtension(const std::string FileName)
{
	if (FileName.find_last_of(".") != std::string::npos)
		return FileName.substr(FileName.find_last_of(".") + 1);
	return NULL;
}