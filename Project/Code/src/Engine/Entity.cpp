#include "Entity.h"
#include <string>
#include "Maths.h"

namespace Engine{
	Entity::Entity(){}
	Entity::~Entity(){}

	Vector3 Entity::getScale(){ return _scale; }
	Vector3 Entity::getPosition(){ return _position; }
	Vector3 Entity::getRotation(){ return _rotation; }

	void Entity::setScale(const Vector3 v3)
	{
		_changed = true;
		_scale = v3;
	}
	void Entity::setPosition(const Vector3 v3)
	{
		_changed = true;
		_position = v3;
	}
	void Entity::setRotation(const Vector3 v3)
	{
		_changed = true;
		_rotation = v3;
	}

	Matrix4 Entity::getTranform()
	{ 
		if (!_changed){
			return _transform;
		}
		else{
			CalculateTransform();
			return _transform;
		}
	}

	void Entity::CalculateTransform()
	{
		Matrix4 scl = Scale(_scale);
		Matrix4 rot = EulerToMatrix(_rotation);
		Matrix4 trn = Translation(_position);
		//_transform =  (scl * rot * trn);
		_transform = (trn * rot * scl);
		_changed = false;
	}

	bool Entity::isVisible(){ return _visible; }
	void Entity::setVisibility(const bool b){ _visible = b; }
	Mesh* Entity::getMesh(){ return _mesh; }
	void Entity::setMesh(Mesh* msh){ _mesh = msh; }
	void Entity::Update(double delta){};
}