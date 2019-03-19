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
		window.Clear(0.0f, 0.0f, 1.0f, 0.0f);
		window.SwapBuffers();
	}

	return 0;
}