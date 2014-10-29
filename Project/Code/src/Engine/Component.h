#pragma once
#include <string>

namespace Engine{
	class Entity;
	class CComponent{

	protected:
		//Parent Entity
		Entity* Ent;
		bool _active;
		const std::string _token;
	public:
		CComponent(Entity* Parent, const std::string token) :_token(token){ Ent = Parent;  _active = true; }
		~CComponent(){};
		virtual void Update(double delta){};
		virtual void Render(){};
		bool Active(){ return _active; }
		void setActive(bool b){ _active = b; }
		std::string GetToken(){ return _token; }
	};

}