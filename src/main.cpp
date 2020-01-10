#include <iostream>
#include <memory>
#include "Observers.h"
#include "Command.h"


int main(int args, char * argv[]) {
	Command command_log(std::atoi(argv[1]));
	command_log.subscribe(std::make_unique<FileObserver>());
	command_log.subscribe(std::make_unique<TerminalObserver>());
	command_log.add_command();

	return 0;
}
