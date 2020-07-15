#pragma once

class CPlayer;

class CDebugGui
{

	CPlayer* pPlayer;

	static bool m_IsDebug;

public:
	static void Initialize();
	static void Finalize();
	static void Update();
	static void Begin();
	static void End();
	static bool IsDebug();
};