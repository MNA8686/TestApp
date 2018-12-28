#include "Script.hpp"

// ----- include begin -----
#include "ScriptPlayer.hpp"
#include "ScriptBullet.hpp"
#include "ScriptTest1.hpp"
#include "ScriptTest2.hpp"
#include "ScriptMain.hpp"
// ----- include end -----

static const std::vector<stScriptTbl> g_scriptTbl =
{
	// ----- table begin -----
	EQ_SCRIPT_DEFINE(ScriptPlayer),
	EQ_SCRIPT_DEFINE(ScriptBullet),
	EQ_SCRIPT_DEFINE(ScriptTest1),
	EQ_SCRIPT_DEFINE(ScriptTest2),
	EQ_SCRIPT_DEFINE(ScriptMain),
	// ----- table end -----
};

const std::vector<stScriptTbl>& GetScriptTbl()
{
	return g_scriptTbl;
}