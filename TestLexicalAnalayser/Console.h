#ifndef CONSOLE_H
#define CONSOLE_H
#include <string>

namespace obaro
{
	namespace io
	{
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
			static void clear();

			class Path
			{
			private:
				static std::string __getFileExtension(const std::string FileName);
			public:
				Path();
				static bool	isExtensionEqual(std::string filename, std::string exe);

			};
		};
	}
}
#endif