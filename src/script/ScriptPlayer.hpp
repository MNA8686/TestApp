#pragma once

#include "Script.hpp"
//#include <cereal/types/base_class.hpp>

class ScriptPlayer : public Script
{
public:
	ScriptPlayer() = default;
	virtual ~ScriptPlayer() = default;

	virtual bool OnCreate() override;
	virtual bool FixedUpdate() override;

#if 0
	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(cereal::base_class<Script>(this));
	}
#endif

	std::shared_ptr<SpriteRenderer> m_spriteRenderer;
};

