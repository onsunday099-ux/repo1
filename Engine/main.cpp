#include "logger.h"
#include "engine.h"
#include <iostream>
int main(int argc, char* argv[]) 
{

	logger::Logger::SetLevel(0);

	logger::CreateLogFile();
	
	engine::Engine app;
	if (app.Init()) {
			
		app.Run();

	}


	

	return 0;
}