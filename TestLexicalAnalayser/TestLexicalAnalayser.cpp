// TestLexicalAnalayser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <LexicalAnalyser.h>
#include <FileInputStream.h>
#include <TokenClass.h>
#include <IParser.h>
#include <UCFParser.h>
#include "Console.h"

using namespace obaro::lexical;
using namespace obaro::io;
using namespace obaro::parsers;

class SimpleDemo
{
private:
	LexicalAnalyser *__lexer;
	IParser * __parser__;
	std::string __source;
	void __parser();
	void __finished();
	void __continueStart();
public:
	SimpleDemo(LexicalAnalyser *lexer);
	void start();


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
	Console::clear();
	std::cout << "\n UCF 1.0 programming language IDE for windows OS\n";
}

void SimpleDemo::start()
{
	
	if (this->__lexer != NULL)
	{

		this->__source = Console::prompt("\nsrc >> ");
		if (this->__source.size() > 0)
		{
			char c = this->__source.at(0);
			if (!Console::isExists(this->__source) && (c == 'E' || c == 'e'))
			{
				Console::writeln("\n aborted...");
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
	if (IParser::Success){
		Console::writeln("\nParser build: successful , error found =" + std::to_string(IParser::ErrorCount) + "");
	}
	else{
		Console::writeln("\nParser build : fails , error found ="+std::to_string(IParser::ErrorCount)+"");
	}

	IParser::ErrorCount = 0;
	IParser::Success = true;
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
	this->__parser__ =  new UCFParser(this->__lexer);
	IExpression *node =this->__parser__->parse();



}

