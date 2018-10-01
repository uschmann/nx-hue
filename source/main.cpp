#include "App.h"

int main(int argc, char **argv)
{
	App* app = App::getInstance();
	app->init();
	app->run();	

  return 0;
}

