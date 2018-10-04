#include "App.h"

#include "Controller/StartController.h"

int main(int argc, char **argv)
{
	App* app = App::getInstance();
	app->init();
	app->startController(new StartController());
	app->run();	

  return 0;
}

