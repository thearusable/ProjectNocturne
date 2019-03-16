#include <Window.hpp>

#undef main

int
main(int argc, char* argv[])
{
	noc::window::Window window(1024, 768, "Editor");
	const std::string fileDir = __FILE__;
	const auto currentDir = fileDir.substr(0, fileDir.find("main.cpp"));

	window.SetIcon(currentDir + "assets\\Moon.bmp");

	while (1)
	{
		//SDL_Event e;
		//SDL_PollEvent(&e);
	}

	return 0;
}