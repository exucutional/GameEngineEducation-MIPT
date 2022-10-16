#include "ScriptSystem.h"
#include "ScriptProxy.h"

CScriptSystem::CScriptSystem()
{
    return;
}

void CScriptSystem::Update()
{
    ;
}

std::unique_ptr<IScriptProxy> CScriptSystem::CreateProxy(const char* filename)
{

    return std::make_unique<CScriptProxy>();
}

void CScriptSystem::ProcessScript(IScriptProxy* scriptProxy)
{
    ;
}