methodmap BRDaCustomBoss __nullable__ < BRBaseBoss
{

	/**
	 * Function to do things when the boss starts up. (Post Init.)
	*/
	public void Startup()
	{
		this.SetBossName("THE BOSS THAT DID NOT");
		this.CurrentSuper = 0;
		this.ChargeRatio = 0.2;
		this.BossHealthMax = 10000.0;
		this.BossHealth = 10000.0;
	}

	/**
	 * Function to see if super can be used.
	*/
	public bool CanSuper()
	{
		return this.CurrentSuper >= SUPER_MAX;
	}

	/**
	 * Function to COMMENCE SUPER!
	*/
	public void StartSuper()
	{
		if(this.CanSuper())
		{
			PrintToChatAll("Ey mang I'm just good.");
		}
	}
	
	/**
	 * Function that is ran after taking damage. IM HIT!
	*/
	public bool TakeDamage(int attacker, int inflictor, float damage, int damagetype)
	{
		float AddedCharge = (damage/(this.BossHealthMax*this.ChargeRatio))*(this.BossHealthMax*this.ChargeRatio);
		this.CurrentSuper += RoundFloat(AddedCharge);
		this.BossHealth -= damage;
		PrintToChatAll("IM HIT!");		
		if(this.BossHealth<=0)
		{
			return true;
		}
		return false;
	}
	
	/**
	 * Create BRDaCustomBoss instance from the given client index.
	 *
	 * @param clientIndex	The client index to bind this methodmap to.
	*/
	public BRDaCustomBoss( int clientIndex )
	{
		BRDaCustomBoss Boss = view_as<BRDaCustomBoss>( new BRBaseBoss( clientIndex ) );
		Boss.SetupDataTable();
		Boss.Initialize();
		Boss.Startup();
		return Boss;
	}
	
}