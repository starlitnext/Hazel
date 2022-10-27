#include "Application.h"

class D3D11App : public Application
{
public:
private:

};

Application* CreateApplication()
{
	return new D3D11App();
}

int main(int argc, char** argv)
{
	auto app = CreateApplication();
	app->Initialize();
	app->Run();
	app->ShutDown();

	return 0;
}
