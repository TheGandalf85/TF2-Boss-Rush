
#define SUPER_MAX 1000

methodmap VSHBaseBoss __nullable__ < CTFPlayer
{

	/**
	 * Function to get the boss' table keymap.
	*/
	public StringMap GetKeyMap()
	{
		return VSHBaseBoss_ActiveData[this.Index];
	}
	
	/**
	 * Function to set the boss' table keymap.
	*/
	public void SetKeyMap(StringMap keymap)
	{
		VSHBaseBoss_ActiveData[this.Index] = keymap;
	}
	
	/**
	 * Function to get a value from the boss' table keymap.
	 *
	 * @param index			The index containing the value.
	*/
	public any GetKeyValue(char key[NAME_LENGTH])
	{
		any output = false;
		this.GetKeyMap().GetValue(key,output);
		return output;		
	}
	
	/**
	 * Function to get a value from the boss' table keymap as a string.
	 *
	 * @param index			The index containing the value.
	 * @param buffer		The buffer to store the string.
	*/
	public void GetKeyValueString(char key[NAME_LENGTH], char buffer[NAME_LENGTH])
	{
		this.GetKeyMap().GetString(key, buffer, NAME_LENGTH);
	}
	
	/**
	 * Function to set a value to the boss' table keymap.
	 *
	 * @param index			The index to set the value.
	 * @param value			Any value to set the index to.
	*/
	public bool SetKeyValue(char key[NAME_LENGTH], any value)
	{
		return this.GetKeyMap().SetValue(key, value, true)
	}
	
	/**
	 * Function to set a value to the boss' table keymap.
	 *
	 * @param index			The index to set the value.
	 * @param string		String to set the index to.
	*/
	public bool SetKeyValueString(char key[NAME_LENGTH], char string[NAME_LENGTH])
	{
		return this.GetKeyMap().SetString(key, string, true)
	}
	
	/**
	 * Gets the amount of Super the boss currently has.
	*/
	property int CurrentSuper
	{
		public get() { return view_as<int>(this.GetKeyValue("cursuper")); }
		public set( int val ) { this.SetKeyValue("cursuper",val); }
	}
	
	/**
	 * Gets the amount of Boss Health the boss currently has.
	*/
	property float BossHealth
	{
		public get() { return view_as<float>(this.GetKeyValue("bosshealth")); }
		public set( float val ) { this.SetKeyValue("bosshealth",val); }
	}
	
	/**
	 * Gets the max amount of Boss Health the boss can have.
	*/
	property float BossHealthMax
	{
		public get() { return view_as<float>(this.GetKeyValue("bosshealthmax")); }
		public set( float val ) { this.SetKeyValue("bosshealthmax",val); }
	}
	
	/**
	 * Gets the amount of Super the boss gains every percentage of health lost.
	*/
	property float ChargeRatio
	{
		public get() { return view_as<float>(this.GetKeyValue("superchargeratio")); }
		public set( float val ) { this.SetKeyValue("superchargeratio",val); }
	}
	
	/**
	 * Gets the string reference containing the name of the boss.
	 *
	 * @param buffer				The buffer to send the name to
	*/
	public void GetBossName(char buffer[NAME_LENGTH])
	{
		this.GetKeyValueString("bossname", buffer)
	}
	
	/**
	 * Sets the name of the boss.
	 *
	 * @param bname				The string to change the boss' name to.
	*/
	public void SetBossName(char bname[NAME_LENGTH])
	{
		this.SetKeyValueString("bossname", bname)
	}
	
	/**
	 * Function that is ran when the VSHBaseBoss instance is created.
	*/
	public void Initialize()
	{
		SDKHook(this.Index, SDKHook_PostThink, VSH_BossThink);
		SDKHook(this.Index, SDKHook_OnTakeDamageAlive, VSH_BossTakeDamage);
	}
	
	/**
	 * Function that is ran after taking damage.
	*/
	public bool TakeDamage(int attacker, int inflictor, float damage, int damagetype)
	{	
		float AddedCharge = (damage/(this.BossHealthMax*this.ChargeRatio))*(this.BossHealthMax*this.ChargeRatio);
		this.CurrentSuper += RoundFloat(AddedCharge);
		this.BossHealth -= damage;
		PrintToChatAll("%f HP. Gained %i Charge. Now you have %i Total Charge.", this.BossHealth, RoundFloat(AddedCharge), this.CurrentSuper);		
		if(this.BossHealth<=0)
		{
			return true;
		}
		return false;
	}
	
	/**
	 * Function that is ran after every Think Call.
	*/
	public void Think()
	{
	
	}
	
	/**
	 * Function to set up the boss data table.
	*/
	public void SetupDataTable()
	{
		StringMap KeyMap = CreateTrie();
		this.SetKeyMap(KeyMap);
	}

	/**
	 * Create a VSHBaseBoss instance from the given client index.
	 *
	 * @param clientIndex	The client index to bind this methodmap to.
	*/
	public VSHBaseBoss( int clientIndex )
	{
		VSHBaseBoss Boss = view_as<VSHBaseBoss>( new CTFPlayer( clientIndex ) );
		Boss.SetupDataTable();
		Boss.Initialize();
		return Boss;
	}
	
}

public Action VSH_BossTakeDamage(int victim, int &attacker, int &inflictor, float &damage, int &damagetype)
{
	VSHBaseBoss Boss = view_as<VSHBaseBoss>(victim);
	if(Boss.TakeDamage(attacker, inflictor, damage, damagetype))
	{
		damage=float(Boss.Health);
	}
	else
	{
		damage=0.0;
	}
	return Plugin_Changed;
}

public void VSH_BossThink(int index)
{
	VSHBaseBoss Boss = view_as<VSHBaseBoss>(index);
	Boss.Think()
}