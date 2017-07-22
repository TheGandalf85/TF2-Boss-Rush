
#include <sourcemod>
#include <sdktools>
#include <sdkhooks>

#define DEBUG_MODE

#define GAME_TF2
#include <thelpers/thelpers>
#undef GAME_TF2

#define NAME_LENGTH 64
#define CMD_LENGTH 256

#define VSH_TableSize 32

StringMap VSHBaseBoss_ActiveData[MAXPLAYERS+1];

public void OnPluginStart()
{
	#if defined DEBUG_MODE
		RegAdminCmd("sm_setasboss", Command_SetAsBoss, ADMFLAG_SLAY);
		RegAdminCmd("sm_getbossname", Command_GetBossName, ADMFLAG_SLAY);
		RegAdminCmd("sm_setbosshp", Command_SetBossHP, ADMFLAG_SLAY);
	#endif
}

#include <bossrush/boss>
#include <bossrush/bossinclude>

#if defined DEBUG_MODE
	public Action Command_SetAsBoss(int client, int args)
	{
		char arg1[32];
		GetCmdArg(1, arg1, sizeof(arg1));
		
		
		VSHBaseBoss Boss = new VSHDaCustomBoss( client );
		char BName[NAME_LENGTH];
		Boss.GetBossName(BName);
		PrintToChat(client, "You are boss now. Your name is %s.", BName)
		return Plugin_Handled;
	}

	public Action Command_GetBossName(int client, int args)
	{
		char arg1[32];
		GetCmdArg(1, arg1, sizeof(arg1));
		
		VSHBaseBoss Boss = view_as<VSHBaseBoss>(client);
		char BossName[NAME_LENGTH];
		Boss.GetBossName(BossName);
		PrintToChat(client, BossName);
		return Plugin_Handled;
	}

	public Action Command_SetBossHP(int client, int args)
	{
		char arg1[32];
		GetCmdArg(1, arg1, sizeof(arg1));
		
		VSHBaseBoss Boss = view_as<VSHBaseBoss>(client);
		Boss.BossHealth = StringToFloat(arg1)
		PrintToChat(client, "You now have %f HP left.", StringToFloat(arg1));
		return Plugin_Handled;
	}
#endif

public void OnMapStart()
{
	ResetVSHBaseBoss();
}

public void ResetVSHBaseBoss()
{
	for(int i=1;i<MAXPLAYERS+1;++i)
	{
		CloseHandle(VSHBaseBoss_ActiveData[i]);
		SDKUnhook(i, SDKHook_PostThink, VSH_BossThink);
	}
}