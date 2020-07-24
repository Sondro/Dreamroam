#include <ComponentBased/SceneHandler.hh>
#include <Scenes/DreamroamScene.hh>

int main(int argc, char** argv)
{
	auto mSceneHandler = SceneHandler::getInstance();
	mSceneHandler->addScene(std::make_shared<DreamroamScene>());
	mSceneHandler->run();
	return 0;
}