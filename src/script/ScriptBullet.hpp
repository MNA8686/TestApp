#if !defined(_EQSCRIPTBULLET_H_)
#define _EQSCRIPTBULLET_H_

#if 0
#include "Script.hpp"
//#include <cereal/types/base_class.hpp>

class ScriptBullet : public Script
{
public:
	ScriptBullet();
	virtual ~ScriptBullet();

	virtual bool OnCreate() override;
	virtual bool FixedUpdate() override;
	std::shared_ptr<SpriteRenderer> RegisterSpriteRenderer();
	std::shared_ptr<LineRenderer> RegisterLineRenderer();
	std::shared_ptr<RectRenderer> RegisterRectRenderer();
	std::shared_ptr<CircleRenderer> RegisterCircleRenderer();
	std::shared_ptr<TextRenderer> RegisterTextRenderer();

	std::shared_ptr<Sprite> m_sprite;
	std::shared_ptr<SpriteRenderer> m_spriteRenderer;
	std::shared_ptr<LineRenderer> m_lineRenderer;
	std::shared_ptr<RectRenderer> m_rectRenderer;
	std::shared_ptr<CircleRenderer> m_circleRenderer;
	std::shared_ptr<TextRenderer> m_textRenderer;

	void SetBullet(FixedDec x, FixedDec y, int32_t angle, FixedDec speed);

	long m_angle = 0;
	long m_speed = 0;

	static bool m_shotSound;

#if 0
	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(cereal::base_class<Script>(this));
		archive(CEREAL_NVP(m_angle));
		archive(CEREAL_NVP(m_speed));
		archive(CEREAL_NVP(m_spriteRenderer));
		archive(CEREAL_NVP(m_rectRenderer));
		archive(CEREAL_NVP(m_lineRenderer));
		archive(CEREAL_NVP(m_circleRenderer));
	}
#endif

	// test
	std::shared_ptr<Sprite> m_font;
};

//#include <cereal/types/polymorphic.hpp>
//CEREAL_REGISTER_TYPE(ScriptBullet);
//CEREAL_REGISTER_POLYMORPHIC_RELATION(Script, ScriptBullet)
#endif

#endif
