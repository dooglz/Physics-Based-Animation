#pragma once
#include <string>
#include <vector>
#include "Maths.h"
#include "Component.h"
namespace Engine{
	class Mesh;
//	class CComponent;
	class Entity{

	protected:
		bool _visible = true;
		std::string _name;
		bool _changed;
		Vector3 _position;
		Vector3 _rotation;
		Vector3 _scale;
		Matrix4 _transform;
		void CalculateTransform();

		std::vector<CComponent*> _components;


	public:
		Entity();
		~Entity();

		Vector3 getScale();
		Vector3 getPosition();
		Vector3 getRotation();
		Matrix4 getTranform();

		//TODO void setTransform(const Matrix4 m4);
		void setScale(const Vector3 v3);
		void setPosition(const Vector3 v3);
		void setRotation(const Vector3 v3);
		bool isVisible();
		void setVisibility(const bool b);
		void SetName(const std::string name){
			_name = name;
		}
		std::string GetName()
		{
			return _name;
		}
		virtual void Update(double delta);
		virtual void Render();

		void AddComponent(CComponent* c);
		void RemoveComponent(CComponent* c);
		std::vector<CComponent*> GetComponents(std::string name);

		template <typename T> 
		T* getComponent()
		{
			std::vector<CComponent*>::iterator it;
			for (std::vector<CComponent*>::iterator it = _components.begin(); it != _components.end(); ++it) {
				//printf("Checking %s against %s \n", typeid(**it).name(), typeid(T).name());
				if (&typeid(**it) == &typeid(T)){
					return static_cast<T*>(*it);
				}
			}
			return NULL;
		}



	};
}