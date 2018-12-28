#if !defined(_EQSCRIPTTEST2_H_)
#define _EQSCRIPTTEST2_H_

#include "Script.hpp"
#include <cereal/types/base_class.hpp>

class ScriptTest2 : public Script
{
public:
	ScriptTest2();
	virtual ~ScriptTest2();

	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(cereal::base_class<Script>(this));

		archive(CEREAL_NVP(m_test2));
	}
	int m_test2 = 0;
};

#include <cereal/types/polymorphic.hpp>
CEREAL_REGISTER_TYPE(ScriptTest2);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Script, ScriptTest2)

#endif
