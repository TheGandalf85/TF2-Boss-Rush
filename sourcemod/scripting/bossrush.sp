
#include <sourcemod>
#include <sdktools>
#include <sdkhooks>

#define DEBUG_MODE

#define GAME_TF2
#include <thelpers/thelpers>
#undef GAME_TF2

#define NAME_LENGTH 64
#define CMD_LENGTH 256

#define BR_TableSize 32

StringMap BRBaseBoss_ActiveData[MAXPLAYERS+1];

public void OnPluginStart()
{
	#if defined DEBUG_MODE
		RegAdminCmd("sm_setasboss", Command_SetAsBoss, ADMFLAG_SLAY);
		RegAdminCmd("sm_getbossname", Command_GetBossName, ADMFLAG_SLAY);
		RegAdminCmd("sm_setbosshp", Command_SetBossHP, ADMFLAG_SLAY);
		RegAdminCmd("sm_getbarhp", Command_GetBarHP, ADMFLAG_SLAY);
	#endif
	HookEvent("teamplay_round_start", BR_OnRoundStart, EventHookMode_PostNoCopy);
}

#include <bossrush/healthbar>
#include <bossrush/boss>
#include <bossrush/bossinclude>

#if defined DEBUG_MODE
	public Action Command_SetAsBoss(int client, int args)
	{
		char arg1[32];
		GetCmdArg(1, arg1, sizeof(arg1));
		
		
		BRBaseBoss Boss = new BRDaCustomBoss( client );
		char BName[NAME_LENGTH];
		Boss.GetBossName(BName);
		PrintToChat(client, "You are boss now. Your name is %s.", BName)
		return Plugin_Handled;
	}

	public Action Command_GetBossName(int client, int args)
	{
		char arg1[32];
		GetCmdArg(1, arg1, sizeof(arg1));
		
		BRBaseBoss Boss = view_as<BRBaseBoss>(client);
		char BossName[NAME_LENGTH];
		Boss.GetBossName(BossName);
		PrintToChat(client, BossName);
		return Plugin_Handled;
	}

	public Action Command_SetBossHP(int client, int args)
	{
		char arg1[32];
		GetCmdArg(1, arg1, sizeof(arg1));
		
		BRBaseBoss Boss = view_as<BRBaseBoss>(client);
		Boss.BossHealth = StringToFloat(arg1)
		PrintToChat(client, "You now have %f HP left.", StringToFloat(arg1));
		return Plugin_Handled;
	}

	public Action Command_GetBarHP(int client, int args)
	{
		char arg1[32];
		GetCmdArg(1, arg1, sizeof(arg1));
		
		BRBaseBoss Boss = view_as<BRBaseBoss>(client);
		CMonsterResource HPBar = view_as<CMonsterResource>(Boss.HealthBarEnt)
		PrintToChat(client, "%i", HPBar.ResourceBossHealth);
		return Plugin_Handled;
	}
#endif

public void OnMapStart()
{
	ResetBRBaseBoss();
}

public void BR_OnRoundStart(Event event, const char[] name, bool dontBroadcast)
{
	ResetBRBaseBoss();
}

public void ResetBRBaseBoss()
{
	for(int i=1;i<MAXPLAYERS+1;++i)
	{
		BR_DestroyBoss(i)
	}
}