/**
\file
\brief Заголовочный файл с описанием классов
Данный файл содержит в себе определения классов, используемых в программе
*/


#pragma once
#include <fstream>
#include <vector>


/**
* @brief базовый класс, для реализации классов вывода команд 
*
*/
class Observers {
public:
	virtual void print(const std::vector<std::string>&, const std::string) = 0;
	virtual ~Observers() = default;
};

/**
* @brief класс реализующий функцию вывода команд в файл  
*
*/
class FileObserver: public Observers {
	virtual void print(const std::vector<std::string>& comm, const std::string time) {
		std::ofstream file;
		std::string path("bulk" + time + ".log");
		file.open(path);
		for (auto& command : comm) {
			file << command << "\n";
		}
		file.close();
	}

};

/**
* @brief класс реализующий функцию вывода команд в консоль  
*
*/
class TerminalObserver: public Observers {
	virtual void print(const std::vector<std::string>& comm, const std::string) {
		std::cout << "Bulk: ";
		bool first = true;
		for (auto& command : comm) {
			if (!first) { std::cout << ","; }
			std::cout << command;
			first = false;
		}
		std::cout << std::endl;
	}

};
