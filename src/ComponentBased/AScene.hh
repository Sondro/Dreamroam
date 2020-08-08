#pragma once

#include <vector>

#include "glm/glm.hpp"
#include <RenderingSystem/MeshHandlers/GeometryStore.hh>
#include <RenderingSystem/TextureHandlers/TextureStore.hh>
#include "entt/entt.hpp"

namespace DCore
{
	namespace ComponentSystem
	{
		typedef entt::entity EntityHandle;

		using namespace DCore::Textures;
		using namespace DCore::Meshes;
		class Entity;

		/// <summary>
		/// This class is abstract and has to be inherited.
		/// It provides the standard functions as start() or update().
		/// Use your instance of this class in combination with the SceneHandler to define your world.
		/// Note: You can create new entities using CreateEntity().
		/// </summary>
		class AScene
		{
		public:
			/// <summary>
			/// Creates the rendering device instance.
			/// </summary>
			AScene();

			~AScene();

			/// <summary>
			/// This is called right after the sceneHandler switches to the new scene.
			/// Use this to register your gameObjects, textures and components.
			/// </summary>
			virtual void start() {};

			/// <summary>
			/// This is called for each frame while the scene is loaded.
			/// Can be used to call all entity systems.
			/// Note: This function should not be used to run the games logic. However, at the current time this is all you got.
			/// </summary>
			/// <param name="dt">Delta Time of the frame in seconds</param>
			virtual void update(double dt) {};

			/// <summary>
			/// This is called right before this scene is destroyed. Use this to deconstruct any game objects and handlers.
			/// </summary>
			virtual void destroy() {};

			/// <summary>
			/// Creates and registers a new entity for your scene.
			/// Please note that you need to keep the returned entity when you want to update it in the scene.
			/// The preferred version for updating entities however should be the system feature.
			/// </summary>
			/// <param name="name">The name of the enity in the scene. This will be stored in the TagComponent on the entity.</param>
			/// <returns>A new entity instance.</returns>
			Entity CreateEntity(const std::string& name = std::string());

		protected:
			/// <summary>
			/// The device which is used to render the scene.
			/// This will be used for a number of initialization procedures.
			/// </summary>
			lava::SharedDevice mDevice;

			/// <summary>
			/// This GeometryStore is used to load meshes and push them to the GPU.
			/// </summary>
			std::shared_ptr<GeometryStore> mGeometryStore;

			/// <summary>
			/// This TextureStore is used to load textures and push them to the GPU.
			/// </summary>
			std::shared_ptr<TextureStore> mTextureStore;

		private:
			/// <summary>
			/// We need this in order to access the registry for registering new components on an entity.
			/// </summary>
			friend class Entity;

			/// <summary>
			/// The SceneHandler must have access to the registry for rendering and sorting objects.
			/// </summary>
			friend class SceneHandler;

			/// <summary>
			/// The registry for entities in the scene.
			/// </summary>
			entt::registry m_Registry;

			// TODO make this a system based approach
			/*void gameObjectAwake();
			void gameObjectStart();
			void gameObjectUpdate(double dt);
			void gameObjectLateUpdate();
			void gameObjectDestroy();*/

			/// <summary>
			/// Returns the texture layout of the scenes current texture store.
			/// </summary>
			/// <returns>The texture layout of the texture store</returns>
			const lava::SharedDescriptorSetLayout GetCurrentSceneTextureStoreTextureLayout();
		};
	}
}