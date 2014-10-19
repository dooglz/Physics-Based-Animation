#pragma once
#include <string>
#include "Maths.h"

namespace Engine{
	class Mesh;

	class Entity{

	protected:
		bool _visible = true;
		std::string _name;
		bool _changed;
		Vector3 _position;
		Vector3 _rotation;
		Vector3 _scale;
		Matrix4 _transform;
		Mesh* _mesh;
		void CalculateTransform();

	public:
		Entity();
		~Entity();
		Mesh* getMesh();
		void setMesh(Mesh* msh);
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

		void Update(double delta);
	};
}