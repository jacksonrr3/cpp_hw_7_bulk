#pragma once
#include <fstream>
#include <vector>

class Observers {
public:
	virtual void print(const std::vector<std::string>&, const std::string) = 0;
	virtual ~Observers() = default;
};

class FileObserver: public Observers {
	virtual void print(const std::vector<std::string>& comm, const std::string time) {
		std::ofstream file;
		std::string path("bulk" + time + ".log");
		file.open("C:\\test\\"+ path);
		for (auto& command : comm) {
			file << command << "\n";
		}
		file.close();
	}

};


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
