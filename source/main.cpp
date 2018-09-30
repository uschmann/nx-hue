#include <string.h>
#include <stdio.h>

#include <switch.h>

#include "HttpClient.h"
#include "HttpResponse.h"
#include "Hue/Hue.h"


int main(int argc, char **argv)
{
	gfxInitDefault();
	consoleInit(NULL);

	socketInitializeDefault();
	nxlinkStdio();
  	printf("printf output now goes to nxlink server\n");

	Hue* hue = new Hue();
	hue->setUser("");
	hue->setIp("192.168.1.204");

	hue->setGroupOnState(groups->at(0).id, false);

	// Main loop
	while(appletMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		// Your code goes here

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

		if (kDown & KEY_PLUS) break; // break in order to return to hbmenu

		gfxFlushBuffers();
		gfxSwapBuffers();
		gfxWaitForVsync();
	}

	socketExit();
	gfxExit();
	return 0;
}

