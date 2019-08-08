#pragma once

#include "Script.hpp"
//#include <cereal/types/base_class.hpp>

class ScriptMain : public Script
{
public:
	ScriptMain() = default;
	virtual ~ScriptMain() = default;

	virtual bool OnCreate() override;
	virtual bool FixedUpdate() override;

#if 0
	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(cereal::base_class<Script>(this));
	}
#endif
};

//#include <cereal/types/polymorphic.hpp>
//CEREAL_REGISTER_TYPE(ScriptMain);
//CEREAL_REGISTER_POLYMORPHIC_RELATION(Script, ScriptMain)

