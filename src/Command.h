/**
\file
\brief Заголовочный файл с описанием классов
Данный файл содержит в себе определения основного класса, используемого в программе
*/



#pragma once
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <algorithm>
#include <ctime>
#include <sstream>
#include "Observers.h"

/**
* @brief Основной класс, реализующий функционал считывания команд из стандартного ввода и распределения на блоки команд
*
*/
class Command {
	std::vector<std::unique_ptr<Observers>> _obs;
	std::vector<std::string> _comm;
	
	int _block_size;
	int _comm_counter=0;
	std::string _time;

public:
	Command(int N):_block_size(N) {}

	void subscribe(std::unique_ptr<Observers>&& obs) {
		_obs.emplace_back(std::move(obs));
	}

	void setTime() {
		std::time_t temp_time;
		temp_time=std::time(0);
		std::stringstream ss;
		ss << temp_time;
		ss >> _time;
	}

	void notify() {
		for (auto& u: _obs) {
			u->print(_comm, _time);
		}
		_comm.clear();
		_time.clear();
	}

	void add_command_bracket() {
		int bracket_counter = 1;
		std::string s;
		while (std::getline(std::cin, s)) {
			if (std::cin.eof()) { return; }

			if (s[0] == '{') {
				++bracket_counter;
				continue;
			}

			else if (s[0] == '}') {
				--bracket_counter;
				if (!bracket_counter) {
					notify();
					return;
				}
			}

			else {
				if (_comm.empty()) { setTime(); }
				_comm.push_back(s);
			}
		}
	}

		void add_command() {
		std::string s;
		while (std::getline(std::cin, s)) {
			if (std::cin.eof()) {
				//notify();
				break;
			}
			if (s[0] == '{') {
				if (_comm_counter) { 
					notify(); 
					_comm_counter = 0;
				}
				add_command_bracket();
			}
			else {
				if (_comm.empty()) { setTime(); }
				_comm.push_back(s);
				++_comm_counter;
				if (_comm_counter == _block_size) {
					notify();
					_comm_counter = 0;
				}
			}
		}
		if (_comm_counter) { notify(); }
	}
};

