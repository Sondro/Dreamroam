#pragma once
#include <ComponentBased/AComponent.hh>
#include <RenderObjects/Geometry.hh>
#include <RenderObjects/Texture.hh>

class RenderComponent : public AComponent
{
public:
  RenderComponent(){};
  std::shared_ptr<Geometry> geometryObj = nullptr;

  bool isTransparent = false;
  float alpha = 1.0f;

  bool hasTexture = false;
  std::shared_ptr<Texture> textureObj = nullptr;

  bool active = true;

  bool isThrowingShadow = true;
};
