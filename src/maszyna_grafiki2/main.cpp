#include <iostream>
#include "system\sys_mgr.h"
#include "cLight.h"
#define SYSTEM_X 5

#if SYSTEM_X == PLATFORM_WIN32 || SYSTEM_X == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{
    try
    {
			unsigned long x = 2;

			main_system::get();

			
			graphSys::getI().getSignalMachine()->send(SIG_GRAPHMACHINE,SIG_GRAPHSYS_INIT,NULL);
			graphSys::getI().getSignalMachine()->send(SIG_GRAPHMACHINE,SIG_GRAPHSYS_WIN_CREATE,new std::string("GraphMain!"),NULL);
			graphSys::getI().getSignalMachine()->send(SIG_GRAPHMACHINE,SIG_GRAPHSYS_SCENE_INIT,new std::string("scene2.xml"),NULL);
			graphSys::getI().getSignalMachine()->send(SIG_GRAPHMACHINE,SIG_GRAPHSYS_SET_CAMERA,new std::string("Cam1"),NULL);
			graphSys::getI().getSignalMachine()->send(SIG_GRAPHMACHINE,SIG_GRAPHSYS_BG_COLOR,new float(0.2), new float(0.2), new float(0.9),NULL);
			


			//graphSys::getI().fl.fInitEngine=1;
			//graphSys::getI().fl.fCreateWindow=1;
	

			//graphSys::getI().fl.fStartInit=1;
			//graphSys::getI().fl.fCameraSet=true;
			//graphSys::getI().fl.fChangeBgColor=true;
			//graphSys::getI().fl.fRenderFrame=true;
			
			for (unsigned long i=0; i<100000; i++)
				main_system::get().loop();
			getchar();
    }
    catch(Ogre::Exception& e)
    {
#if SYSTEM_X == PLATFORM_WIN32 || SYSTEM_X == OGRE_PLATFORM_WIN32
        MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        fprintf(stderr, "An exception has occurred: %s\n",
            e.getFullDescription().c_str());
#endif
    }

    return 0;
}