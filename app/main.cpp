#include <IInputListener.hpp>
#include <Input.hpp>
#include <Window.hpp>
#include <Game.hpp>

#undef main

class TestObject : public noc::input::UserControllable
{
public:
	void
	SetUpInput(noc::input::Input& input) override
	{
		input.RegisterForActionEvent(this, "jump", noc::input::NOC_KEY_STATE::PRESSED);
	}
};

int
main(int argc, char* argv[])
{
	noc::window::Window mainWindow(1024, 768, "Nocturne");
	noc::window::Window toolsWindow(640, 480, "Tools");
	const std::string   fileDir    = __FILE__;
	const auto          currentDir = fileDir.substr(0, fileDir.find("main.cpp"));

	mainWindow.SetIcon(currentDir + "assets\\Moon.bmp");

	noc::input::Input in;

	while(1)
	{
		in.HandleInput();

		mainWindow.Clear(0.0f, 0.0f, 1.0f, 0.0f);
		mainWindow.SwapBuffers();

		toolsWindow.Clear(0.1f, 0.2f, 0.3f, 0.0f);
		toolsWindow.SwapBuffers();
	}

	return 0;
}