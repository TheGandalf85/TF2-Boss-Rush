
const CMonsterResource INVALID_RES_ENTITY = view_as<CMonsterResource>( INVALID_ENT_REFERENCE );

methodmap CMonsterResource __nullable__
{
	
	public CMonsterResource( int entIndex )
	{
		if ( !IsValidEntity( entIndex ) )
			return INVALID_RES_ENTITY;

		// to support logical ents, which are passed through certain forwards and callbacks as ent refs (!) rather than indexes
		// we have to first convert the reference to an actual index. this will no-op when given an index rather than a ref
		entIndex = EntRefToEntIndex( entIndex );

		return view_as<CMonsterResource>( EntIndexToEntRef( entIndex ) );
	}
	
	/**
	 * Gets the entity index of this entity instance.
	 * If the entity is invalid, INVALID_ENT_REFERENCE is returned instead.
	*/
	property int Index
	{
		public get() { return EntRefToEntIndex( view_as<int>( this ) ); }
	}
	/**
	 * Gets the entity reference of this entity instance.
	*/
	property int Ref
	{
		public get() { return view_as<int>( this ); }
	}

	/**
	 * Gets a value indicating if this entity is valid or not.
	*/
	property bool IsValid
	{
		public get() { return IsValidEntity( this.Ref ); }
	}
	
	property int ResourceBossHealth
	{
		public get() { return GetEntProp( this.Ref, Prop_Send, "m_iBossHealthPercentageByte", 4, 0 ); }
		public set( int val )
		{
			if(val < 1) val = 1;
			SetEntProp( this.Ref, Prop_Send, "m_iBossHealthPercentageByte", val, 4, 0 );
		}
	}
}

public CMonsterResource BR_GenerateHealthBar( int index )
{
	CMonsterResource BR_HealthBar;
	int ent = FindEntityByClassname(-1, "monster_resource")
	if (ent > 0)
	{
		BR_HealthBar = view_as<CMonsterResource>(ent);
	}	
	else
	{
		BR_HealthBar = new CMonsterResource(CreateEntityByName("monster_resource"));
		DispatchSpawn(BR_HealthBar.Index);
	}
	//PrintToChatAll("%i", BR_HealthBar.Index)
	return BR_HealthBar;
}