#include "Entity.h"
#include <string>
#include "Maths.h"
#include "Component.h"

namespace Engine{
	Entity::Entity(){
		_scale = Vector3(1.0f);
		_position = Vector3(0.0f);
		_rotation = Vector3(0.0f);
		CalculateTransform();
	}

	Entity::~Entity(){
		for (std::vector<CComponent*>::iterator it = _components.begin(); it != _components.end(); ++it) {
			delete (*it);
		}
	}

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


	void Entity::Update(double delta){
		//printf("eTICK: %f\n", delta * 100);
		for (std::vector<CComponent*>::iterator it = _components.begin(); it != _components.end(); ++it) {
			(*it)->Update(delta);
		}
	};

	void Entity::Render(){
		//printf("eTICK: %f\n", delta * 100);
		for (std::vector<CComponent*>::iterator it = _components.begin(); it != _components.end(); ++it) {
			(*it)->Render();
		}
	};

	void Entity::AddComponent(CComponent* c)
	{
		_components.push_back(c);
		c->SetParent(this);
	}

	void Entity::RemoveComponent(CComponent* c)
	{
		std::vector<CComponent*>::iterator position = std::find(_components.begin(), _components.end(), c);
		if (position != _components.end()) {
			_components.erase(position);
		}
	}

	std::vector<CComponent*> Entity::GetComponents(std::string name)
	{
		std::vector<CComponent*> c;
		if (_components.size() < 1){ return c; }
		std::vector<CComponent*>::iterator it;
		for (std::vector<CComponent*>::iterator it = _components.begin(); it != _components.end(); ++it) {
			if ((*it)->GetToken() == name){
				c.push_back((*it));
			}
		}
		return c;
	}



}