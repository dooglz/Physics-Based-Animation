#include "Component.h"

namespace Engine{
	class Entity;
	class CComponent{

	protected:
		//Parent Entity
		Entity* Ent;
		bool _active;
		const std::string _token;
	public:
		CComponent(const std::string token) :_token(token){ _active = true; }
		~CComponent(){};
		virtual void Update(double delta){};
		virtual void Render(){};
		bool Active(){ return _active; }
		void setActive(bool b){ _active = b; }
		void SetParent(Entity* p);
		std::string GetToken(){ return _token; }
	};

}