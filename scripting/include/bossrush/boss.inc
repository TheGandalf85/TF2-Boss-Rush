
#define SUPER_MAX 1000
#define HPBAR_MAX 255

methodmap BRBaseBoss __nullable__ < CTFPlayer
{

	/**
	 * Function to get the boss' table keymap.
	*/
	public StringMap GetKeyMap()
	{
		return BRBaseBoss_ActiveData[this.Index];
	}
	
	/**
	 * Function to set the boss' table keymap.
	*/
	public void SetKeyMap(StringMap keymap)
	{
		BRBaseBoss_ActiveData[this.Index] = keymap;
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
	 * Gets the Heathbar that is the child of the boss.
	*/
	property int HealthBarEnt
	{
		public get() { return view_as<int>(this.GetKeyValue("healthbarentity")); }
		public set( int val ) { this.SetKeyValue("healthbarentity",val); }
	}
	
	public void UpdateHealthBar(float Health, float MaxHealth)
	{
		if(this.HealthBarEnt > 0)
		{
			CMonsterResource HealthBar = view_as<CMonsterResource>(this.HealthBarEnt);
			HealthBar.ResourceBossHealth = RoundFloat(((Health+0.001)/MaxHealth)*HPBAR_MAX);
		}
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
	 * Gets the amount of Boss Health the boss currently has.
	*/
	property float BossHealth
	{
		public get() { return view_as<float>(this.GetKeyValue("bosshealth")); }
		public set( float val )
		{
			if(val < 0.0) val = 0.0;
			this.SetKeyValue("bosshealth",val);
			this.UpdateHealthBar(val, this.BossHealthMax);
			this.Health = RoundFloat(val);
		}
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
	 * Function that is ran when the BRBaseBoss instance is created.
	*/
	public void Initialize()
	{
		SDKHook(this.Index, SDKHook_PostThink, BR_BossThink);
		SDKHook(this.Index, SDKHook_OnTakeDamageAlive, BR_BossTakeDamage);
		CMonsterResource HealthBar = BR_GenerateHealthBar(this.Index)
		this.HealthBarEnt = HealthBar.Index;
		HealthBar.ResourceBossHealth = 255;
	}
	
	/**
	 * Function that is ran after taking damage.
	*/
	public bool TakeDamage(int attacker, int inflictor, float damage, int damagetype)
	{	
		float AddedCharge = ((damage/(this.BossHealthMax*this.ChargeRatio))*(this.BossHealthMax*this.ChargeRatio))*0.495;
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
	 * Create a BRBaseBoss instance from the given client index.
	 *
	 * @param clientIndex	The client index to bind this methodmap to.
	*/
	public BRBaseBoss( int clientIndex )
	{
		BRBaseBoss Boss = view_as<BRBaseBoss>( new CTFPlayer( clientIndex ) );
		Boss.SetupDataTable();
		Boss.Initialize();
		return Boss;
	}
	
}

public Action BR_BossTakeDamage(int victim, int &attacker, int &inflictor, float &damage, int &damagetype)
{
	BRBaseBoss Boss = view_as<BRBaseBoss>(victim);
	if(Boss.TakeDamage(attacker, inflictor, damage, damagetype))
	{
		damage=float(Boss.Health);
	}
	else
	{
		damage=1.0;
		Boss.Health = RoundFloat(Boss.BossHealth);
	}
	return Plugin_Changed;
}

public void BR_BossThink(int index)
{
	BRBaseBoss Boss = view_as<BRBaseBoss>(index);
	Boss.Think()
}

public void BR_DestroyBoss(int index)
{
	SDKUnhook(index, SDKHook_PostThink, BR_BossThink);
	SDKUnhook(index, SDKHook_OnTakeDamageAlive, BR_BossTakeDamage);
	CloseHandle(BRBaseBoss_ActiveData[index]);
}