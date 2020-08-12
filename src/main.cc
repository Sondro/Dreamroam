#include "main.h"

#include <ComponentBased/SceneHandler.hh>
#include <RenderingSystem/RenderingSystem.hh>
#include <Scenes/DreamroamScene.hh>
#include <Utils/Debug/Profiling.hh>

using namespace DCore::Example;
int main(int argc, char** argv) {
    DR_PROFILE_BEGIN_SESSION("Startup", "profiling-startup.json");

    auto mSceneHandler = SceneHandler::getInstance();
    mSceneHandler->addScene(std::make_shared<DreamroamScene>());

    DR_PROFILE_BEGIN_SESSION("Run", "profiling-run.json");
    mSceneHandler->run();
    return 0;
}