#if !defined(_EQSCRIPTTEST1_H_)
#define _EQSCRIPTTEST1_H_

#include "Script.hpp"
#include <cereal/types/base_class.hpp>

#include "ScriptTest2.hpp"

class ScriptTest1 : public Script
{
public:
	ScriptTest1();
	virtual ~ScriptTest1();

	virtual bool OnCreate() override;

	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(cereal::base_class<Script>(this));

		archive(CEREAL_NVP(m_test1));
	}
	int m_test1 = 0;
};

#include <cereal/types/polymorphic.hpp>
CEREAL_REGISTER_TYPE(ScriptTest1);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Script, ScriptTest1)

#endif
