#include "App.h"

#include "Controller/GroupController.h"

int main(int argc, char **argv)
{
	App* app = App::getInstance();
	app->init();

	GroupController * controller = new GroupController();
	app->startController(controller);
	app->run();	

  return 0;
}

