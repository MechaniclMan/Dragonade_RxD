/*	Renegade Scripts.dll
    Dragonade Infantry Only Crates
	Copyright 2017 Whitedragon, Tiberian Technologies

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/

#include "general.h"
#include "scripts.h"
#include "engine.h"
#include "engine_da.h"
#include "da.h"
#include "da_crate.h"
#include "da_event.h"
#include "da_player.h"
#include "da_gameobj.h"
#include "da_translation.h"
#include "da_vehicle.h"
#include "da_settings.h"
#include "da_disable.h"
#include "PurchaseSettingsDefClass.h"
#include "TeamPurchaseSettingsDefClass.h"
#include "GameObjManager.h"






void Damage_All_Objects_Area_By_Team2(float Damage,const char *Warhead,const Vector3 &Position,float Distance,GameObject *Damager,bool Soldiers,bool Vehicles, bool Buildings, int Team) 
{
	SLNode<SmartGameObj> *x = GameObjManager::SmartGameObjList.Head();
	while (x) 
	{
		SmartGameObj *o = x->Data();
		if (o)
		{
			int Type = o->Get_Player_Type();
			if (Type == Team || Team == 2)
			{
				if (o->As_SoldierGameObj() && Soldiers || o->As_VehicleGameObj() && Vehicles )
				{
					//Console_Output("SmartTeam2: %d Preset: %s\n", Team, Commands->Get_Preset_Name(o));
					Vector3 ObjPosition = Commands->Get_Position(o);
					Vector3 TestPosition = Position;
					if (Commands->Get_Distance(ObjPosition,TestPosition) <= Distance)
					{
						//Console_Output("Distance Match SmartTeam2: %d Preset: %s\n", Team, Commands->Get_Preset_Name(o));
						Commands->Apply_Damage(o,Damage,Warhead,Damager);
					}
				}
			}
		}
		x = x->Next();
	}

	for (SLNode<BuildingGameObj> *z = GameObjManager::BuildingGameObjList.Head(); z; z = z->Next())
	{
		BuildingGameObj *building = z->Data();

		if (building && Buildings)
		{
			if (building->Get_Player_Type() == Team || Team == 2)
			{
				//Console_Output("BuildingTeam2: %d Preset: %s\n", Team, Commands->Get_Preset_Name(building));
				Vector3 ObjPosition = Commands->Get_Position(building);
				Vector3 TestPosition = Position;
				if (Commands->Get_Distance(ObjPosition,TestPosition) <= Distance)
				{
					//Console_Output("Match BuildingTeam2: %d Preset: %s\n", Team, Commands->Get_Preset_Name(building));
					Commands->Apply_Damage(building,Damage,Warhead,Damager);
				}
			}
		}
	}
}


//Nucler Strike in X seconds sounds 
static const char TeamNukeStrikeSounds[7][2][50] = {
	{
		"mxxdsgn_dsgn0033i1evan_snd.wav",
		"mxxdsgn_dsgn0035i1evag_snd.wav" // 60 seconds
	},
	{
		"mxxdsgn_dsgn0032i1evan_snd.wav",
		"mxxdsgn_dsgn0034i1evag_snd.wav" // 50 seconds
	},
	{
		"mxxdsgn_dsgn0031i1evan_snd.wav",
		"mxxdsgn_dsgn0033i1evag_snd.wav" // 40 seconds
	},
	{
		"mxxdsgn_dsgn0030i1evan_snd.wav",
		"mxxdsgn_dsgn0032i1evag_snd.wav" // 30 seconds
	},
	{
		"mxxdsgn_dsgn0029i1evan_snd.wav",
		"mxxdsgn_dsgn0031i1evag_snd.wav" // 20 seconds
	},
	{
		"mxxdsgn_dsgn0028i1evan_snd.wav",
		"mxxdsgn_dsgn0030i1evag_snd.wav" // 10 seconds
	},
	{
		"mxxdsgn_dsgn0027i1evan_snd.wav",
		"mxxdsgn_dsgn0029i1evag_snd.wav" // 5 seconds
	}
};


//Clown Sounds

class  DAClownSoundsObserverClass : public DAGameObjObserverClass 
{
	virtual const char *Get_Name() { 
		return "DAClownSounds"; 
	}

	virtual void Init() 
	{
		//WalkingBombTimer = DASettingsManager::Get_Float("WalkingBombTimer",30.0f);
		Start_Timer(1, 0.01f);
	}

	virtual void Timer_Expired(GameObject *obj,int Number) 
	{
		if(Number == 1)
		{
			DA::Create_2D_Sound("EvilClown2.mp3");
			DA::Create_2D_Sound("laugha.mp3");
			DA::Create_2D_Sound("jks_laughs.mp3");
			Start_Timer(2, 1.0f);
		}
		else if(Number == 2)
		{
			DA::Create_2D_Sound("laughb.mp3");
			DA::Create_2D_Sound("laughc.mp3");
			Start_Timer(3, 1.0f);
		}
		else if(Number == 3)
		{
			DA::Create_2D_Sound("laughd.mp3");
			DA::Create_2D_Sound("jks_giggle.mp3");
			Start_Timer(4, 1.0f);
		}
		else if(Number == 4)
		{
			DA::Create_2D_Sound("laugh6.mp3");
			DA::Create_2D_Sound("laugh5.mp3");
			Start_Timer(5, 2.0f);
		}
		else if(Number == 5)
		{
			DA::Create_2D_Sound("friend.mp3");
			Start_Timer(6, 4.0f);
		}
		else if(Number == 6)
		{
			DA::Create_2D_Sound("laughd.mp3");
			Start_Timer(999, 4.0f);
		}
		else
		{
			Set_Delete_Pending();
		}
	}
};


class  DACrazyClownSoundsObserverClass : public DAGameObjObserverClass 
{
	virtual const char *Get_Name() { 
		return "DAClownSounds"; 
	}

	virtual void Init() 
	{
		//WalkingBombTimer = DASettingsManager::Get_Float("WalkingBombTimer",30.0f);
		Start_Timer(1, 0.01f);
	}

	virtual void Timer_Expired(GameObject *obj,int Number) 
	{
		if(Number == 1)
		{
			DA::Create_2D_Sound("laugh1.mp3");
			Start_Timer(2, 1.0f);
		}
		else if(Number == 2)
		{
			DA::Create_2D_Sound("laugh2.mp3");
			Start_Timer(3, 1.0f);
		}
		else if(Number == 3)
		{
			DA::Create_2D_Sound("laugh3.mp3");
			Start_Timer(4, 1.0f);
		}
		else if(Number == 4)
		{
			DA::Create_2D_Sound("laugh4.mp3");
			Start_Timer(5, 1.0f);
		}
		else if(Number == 5)
		{
			DA::Create_2D_Sound("laugh5.mp3");
			Start_Timer(6, 1.0f);
		}
		else if(Number == 6)
		{
			DA::Create_2D_Sound("laugh6.mp3");
			Start_Timer(7, 1.0f);
		}
		else if(Number == 7)
		{
			DA::Create_2D_Sound("laugh7.mp3");
			Start_Timer(8, 1.0f);
		}
		else if(Number == 8)
		{
			DA::Create_2D_Sound("laugh8.mp3");
			Start_Timer(9, 1.0f);
		}
		else if(Number == 9)
		{
			DA::Create_2D_Sound("laugh9.mp3");
			Start_Timer(10, 1.0f);
		}
		else if(Number == 10)
		{
			DA::Create_2D_Sound("laugha.mp3");
			Start_Timer(11, 1.0f);
		}
		else if(Number == 11)
		{
			DA::Create_2D_Sound("laughb.mp3");
			Start_Timer(12, 1.0f);
		}
		else if(Number == 12)
		{
			DA::Create_2D_Sound("laughc.mp3");
			Start_Timer(13, 1.0f);
		}
		else if(Number == 13)
		{
			DA::Create_2D_Sound("laughd.mp3");
			Start_Timer(14, 1.0f);
		}
		else if(Number == 14)
		{
			DA::Create_2D_Sound("friend.mp3");
			Start_Timer(999, 1.0f);
		}
		else
		{
			Set_Delete_Pending();
		}
	}
};



class  DAWalkingBombObserverClass2 : public DAGameObjObserverClass //before disarm nuke version
{
	int nuke_id;
	GameObject *NukeObject;
	GameObject *NukeCinematic;
	//float WalkingBombTimer;

	virtual const char *Get_Name() { 
		return "DAWalkingBombObserverClass2"; 
	}

	virtual void Init() 
	{
		//WalkingBombTimer = DASettingsManager::Get_Float("WalkingBombTimer",30.0f);
		Start_Timer(111, 0.1f);
	}

	 virtual void Destroyed(GameObject *obj) 
	 {
		 Commands->Destroy_Object(Commands->Find_Object(nuke_id));
	 }

	//stop walking bomb from geting crates
	virtual bool PowerUp_Grant_Request_Event(cPlayer *Player,const PowerUpGameObjDef *PowerUp,PowerUpGameObj *PowerUpObj)
	{
		//DA::Page_Player(Player,"You cannot make purchases while a Walking Bomb.");
		return false;
	}

	virtual void PowerUp_Grant_Event(cPlayer *Player,const PowerUpGameObjDef *PowerUp,PowerUpGameObj *PowerUpObj)
	{
		//DA::Page_Player(Player,"22You cannot make purchases while a Walking Bomb.");
	}

	virtual void Timer_Expired(GameObject *obj,int Number) 
	{
		if(Number == 111) // Attach nuke to face
		{
			GameObject *tmpObj = Commands->Create_Object_At_Bone(Get_Owner(), "Invisible_Object", "c Head");
			Commands->Set_Model(tmpObj,"w_a-10bomb");
			Commands->Attach_To_Object_Bone(tmpObj, Get_Owner(), "c Head");
			nuke_id=Commands->Get_ID(tmpObj);
			NukeObject=tmpObj;
			DA::Create_2D_Sound("nuke_strike_buildup_alt.wav");
			Start_Timer(222, 11.0f);

		}
		else if(Number == 222)
		{
			DA::Create_2D_Sound("nuke_launch.wav"); //cnc nuke launch 
			DA::Create_2D_Sound("nuke_approaching.wav"); //Nuke approching
			Start_Timer(333, 5.0f);
		}

		else if(Number == 333)
		{
			DA::Create_2D_Sound("m00evag_dsgn0096i1evag_snd.wav"); // countdown int
			Start_Timer(444, 4.0f);
		}
		else if(Number == 444) //you have
		{
			DA::Create_2D_Sound("m00evag_dsgn0097i1evag_snd.wav"); // you have
			Start_Timer(30, 1.1f);
		}

		else if(Number == 555)
		{
			DA::Create_2D_Sound("m00evag_dsgn0098i1evag_snd.wav"); // seconds to reach min safe distance 
		}
		else if(Number == 777) // seconds
		{
			DA::Create_2D_Sound("countdown_seconds.wav"); // seconds
		}
		else if(Number == 30)
		{
			DA::Host_Message("The Walking Bomb is going to Explode in 30 Second's." );
			DA::Create_2D_Sound("m00evag_dsgn0073i1evag_snd.wav"); // 30
			Start_Timer(555, 1.0f);
			Start_Timer(25, 5.0f);
		}
		else if(Number == 25)
		{
			DA::Create_2D_Sound("m00evag_dsgn0074i1evag_snd.wav"); // 25
			Start_Timer(20, 5.0f);
			Start_Timer(777, 1.0f);
		}
		else if(Number == 20)
		{
			DA::Create_2D_Sound("m00evag_dsgn0075i1evag_snd.wav"); // 20
			Start_Timer(15, 5.0f);
			Start_Timer(777, 1.0f);
		}
		else if(Number == 15)
		{
			DA::Create_2D_Sound("m00evag_dsgn0076i1evag_snd.wav"); // 15
			Start_Timer(10, 5.0f);
			Start_Timer(1111, 8.8f);
			Start_Timer(777, 1.0f);
		}
		else if(Number == 10)
		{
			DA::Host_Message("The Walking Bomb is going to Explode in 10 Second's." );
			DA::Create_2D_Sound("m00evag_dsgn0077i1evag_snd.wav"); //10
			DA::Create_2D_Sound("nuke_strike_buildup_nocount.wav"); //nuke alarm
			Start_Timer(9, 1.0f);
		}
		else if(Number == 9)
		{
			DA::Create_2D_Sound("m00evag_dsgn0078i1evag_snd.wav"); //9
			Start_Timer(8, 1.0f);
		}
		else if(Number == 8)
		{
			DA::Create_2D_Sound("m00evag_dsgn0079i1evag_snd.wav"); //8
			Start_Timer(7, 1.00f);
		}
		else if(Number == 7)
		{
			DA::Create_2D_Sound("m00evag_dsgn0080i1evag_snd.wav"); //7
			Start_Timer(6, 1.0f);
		}
		else if(Number == 6)
		{
			DA::Create_2D_Sound("m00evag_dsgn0081i1evag_snd.wav"); //6
			Start_Timer(5, 1.0f);
		}
		else if(Number == 5)
		{
			DA::Create_2D_Sound("m00evag_dsgn0082i1evag_snd.wav"); // 5
			Start_Timer(4, 1.0f);
		}
		else if(Number == 4)
		{
			DA::Create_2D_Sound("m00evag_dsgn0083i1evag_snd.wav"); // 4
			Start_Timer(3, 1.5f);
		}
		else if(Number == 3)
		{
			DA::Create_2D_Sound("m00evag_dsgn0084i1evag_snd.wav"); // 3
			Start_Timer(2, 1.0f);
		}
		else if(Number == 2)
		{
			DA::Create_2D_Sound("m00evag_dsgn0085i1evag_snd.wav"); // 2
			Start_Timer(1, 1.0f);
		}
		else if(Number == 1)
		{
			DA::Create_2D_Sound("m00evag_dsgn0086i1evag_snd.wav"); // 1
			Start_Timer(0, 1.0f);
		}
		else if(Number == 0)
		{
			DA::Create_2D_Sound("m00evag_dsgn0087i1evag_snd.wav"); // 0
			Start_Timer(1000, 0.1f);
		}
		else if(Number == 1111) // Nuke Cinematic
		{
			Vector3 pos = Commands->Get_Position(Get_Owner());
			pos.Z+=10;
			GameObject *nuke = Commands->Create_Object("Generic_Cinematic",pos);
			Commands->Set_Model(nuke,"XG_AG_Nuke");
			Commands->Attach_Script(nuke,"JFW_PlayAnimation_DestroyObject","Nuke_Missle.Nuke_Missle");
		}
		else if(Number == 1000 ) //kill player
		{
		    if ( NukeObject )
				Commands->Destroy_Object(NukeObject);
			if (Get_Vehicle(Get_Owner())) 
			{
				Commands->Apply_Damage(Get_Vehicle(Get_Owner()), 99999.0f, "None", 0);
				Start_Timer(1001, 0.1f);
			}
			
			Commands->Apply_Damage(Get_Owner(), 99999.0f, "None", 0);
		}
		else if(Number == 1001 ) //delay killing player in vehicle
		{
			Commands->Apply_Damage(Get_Owner(), 99999.0f, "None", 0);
		}
	}

	virtual void Kill_Received(ArmedGameObj *Killer,float Damage,unsigned int Warhead,float Scale,DADamageType::Type Type) 
	{
		if ( !Is_Player(Killer) )
			Killer = 0;
		int Team = Get_Player_Type(Get_Owner());
		if ( Team == 0 )
			Team = 1;
		else if ( Team == 1 )
			Team = 0;
		Commands->Create_Object("Beacon_Nuke_Strike_Anim_Post",Commands->Get_Position(Get_Owner()));
		Commands->Create_Explosion("Explosion_NukeBeacon",Commands->Get_Position(Get_Owner()),0);
		DA::Create_2D_Sound("nuke_strike_fire.wav");
		Damage_All_Objects_Area_By_Team2(2500.0f,"None",Commands->Get_Position(Get_Owner()),18.0f,0,true,true,true,Team);
		Commands->Give_Points(Get_Owner(),100.0f,false);
		Commands->Shake_Camera(Commands->Get_Position(Get_Owner()), 1000.000f, 0.10f, 1.0f);
		Commands->Destroy_Object(Commands->Find_Object(nuke_id));
		//Get_Owner()->Set_Delete_Pending();
		Set_Delete_Pending();
	}
};


class  DAWalkingBombObserverClass : public DAGameObjObserverClass 
{
	int nuke_id;
	GameObject *NukeObject;
	GameObject *NukeCinematic;
	//float WalkingBombTimer;
	bool BombArmed;
	int BeepTimer;
	int ComTimer;
	int Team;
	StringClass TeamName;
	StringClass OtherTeam;

	virtual const char *Get_Name() { 
		return "DAWalkingBombObserverClass"; 
	}

	virtual void Init() 
	{
		//WalkingBombTimer = DASettingsManager::Get_Float("WalkingBombTimer",30.0f);
		BeepTimer = 0;
		ComTimer = 0;
		BombArmed = false;
		Start_Timer(100, 0.1f);
	}

	 virtual void Destroyed(GameObject *obj) 
	 {
		 Commands->Destroy_Object(Commands->Find_Object(nuke_id));
	 }

	//stop walking bomb from geting crates
	virtual bool PowerUp_Grant_Request_Event(cPlayer *Player,const PowerUpGameObjDef *PowerUp,PowerUpGameObj *PowerUpObj)
	{
		//DA::Page_Player(Player,"You cannot make purchases while a Walking Bomb.");
		return false;
	}

	virtual void PowerUp_Grant_Event(cPlayer *Player,const PowerUpGameObjDef *PowerUp,PowerUpGameObj *PowerUpObj)
	{
		//DA::Page_Player(Player,"22You cannot make purchases while a Walking Bomb.");
	}

	virtual void Timer_Expired(GameObject *obj,int Number) 
	{
		if(Number == 100) // Attach nuke to face
		{
			BombArmed = false;
			GameObject *tmpObj = Commands->Create_Object_At_Bone(Get_Owner(), "Invisible_Object", "c Head");
			Commands->Set_Model(tmpObj,"w_a-10bomb");
			Commands->Attach_To_Object_Bone(tmpObj, Get_Owner(), "c Head");
			nuke_id=Commands->Get_ID(tmpObj);
			NukeObject=tmpObj;

			DA::Create_2D_Sound_Team( 0, TeamNukeStrikeSounds[0][0] ); // 60 Seconds
			DA::Create_2D_Sound_Team( 1, TeamNukeStrikeSounds[0][1] ); // 60 Seconds
			DA::Create_2D_Sound("computer-alarm_klaxon_001.wav");
			DA::Host_Message("You have 60 second's to destroy the Walking Bomb before it becomes Armed." );
			Start_Timer(200, 10.0f);
			Start_Timer(999, 1.0f);
			Start_Timer(101, 5.0f);
		}

		else if(Number == 101) // Uplink established 
		{
			DA::Create_2D_Sound("00-n004e.wav");
			Start_Timer(102, 15.0f);
		}
		else if(Number == 102) // Scanning
		{
			DA::Create_2D_Sound("00-n022e.wav");
		}

		else if(Number == 200) // 50 Seconds
		{
			DA::Create_2D_Sound_Team( 0, TeamNukeStrikeSounds[1][0] );
			DA::Create_2D_Sound_Team( 1, TeamNukeStrikeSounds[1][1] ); 
			Start_Timer(300, 10.0f);

		}
		else if(Number == 300) // 40 seconds
		{
			DA::Create_2D_Sound_Team( 0, TeamNukeStrikeSounds[2][0] );
			DA::Create_2D_Sound_Team( 1, TeamNukeStrikeSounds[2][1] ); 
			Start_Timer(400, 10.0f);
		}
		else if(Number == 400) // 30 Seconds
		{
			DA::Create_2D_Sound_Team( 0, TeamNukeStrikeSounds[3][0] );
			DA::Create_2D_Sound_Team( 1, TeamNukeStrikeSounds[3][1] ); 
			DA::Host_Message("Hurry you have 30 second's to destroy the Walking Bomb before it becomes Armed." );
			Start_Timer(500, 10.0f);
		}
		else if(Number == 500) // 20 seconds
		{
			DA::Create_2D_Sound_Team( 0, TeamNukeStrikeSounds[4][0] );
			DA::Create_2D_Sound_Team( 1, TeamNukeStrikeSounds[4][1] ); 
			Start_Timer(600, 10.0f);
		}
		else if(Number == 600) // 10 seconds
		{
			DA::Create_2D_Sound_Team( 0, TeamNukeStrikeSounds[5][0] );
			DA::Create_2D_Sound_Team( 1, TeamNukeStrikeSounds[5][1] ); 
			Start_Timer(700, 5.0f);
		}
		else if(Number == 700) // 5 seconds
		{
			DA::Create_2D_Sound_Team( 0, TeamNukeStrikeSounds[6][0] );
			DA::Create_2D_Sound_Team( 1, TeamNukeStrikeSounds[6][1] ); 
			Start_Timer(111, 5.0f);
		}
		else if(Number == 111) // Armed Nuke
		{
			BombArmed = true;
			Team = Commands->Get_Player_Type(Get_Owner());
			if ( Team == 0 )
			{
				TeamName = "Nod";
				OtherTeam = "GDI";
			}
			else
			{
				TeamName = "GDI";
				OtherTeam = "Nod";
			}

			DA::Host_Message("The Walking Bomb is now Armed run %s.", OtherTeam );
			DA::Create_2D_Sound("nuke_strike_buildup_alt.wav");
			Start_Timer(222, 11.0f);
			Start_Timer(888, 1.0f);

		}
		else if(Number == 222)
		{
			DA::Create_2D_Sound("nuke_launch.wav"); //cnc nuke launch 
			Start_Timer(333, 5.0f);
			Start_Timer(2224, 2.0f);
		}
		else if(Number == 2224)
		{
			DA::Create_2D_Sound("nuke_approaching.wav"); //Nuke approching
		}

		else if(Number == 333)
		{
			DA::Create_2D_Sound("m00evag_dsgn0096i1evag_snd.wav"); // countdown int
			Start_Timer(444, 4.0f);
		}
		else if(Number == 444) //you have
		{
			DA::Create_2D_Sound("m00evag_dsgn0097i1evag_snd.wav"); // you have
			Start_Timer(30, 1.1f);
		}

		else if(Number == 555)
		{
			DA::Create_2D_Sound("m00evag_dsgn0098i1evag_snd.wav"); // seconds to reach min safe distance 
		}
		else if(Number == 777) // seconds
		{
			DA::Create_2D_Sound("countdown_seconds.wav"); // seconds
		}
		else if(Number == 888) // nuke beep
		{
			//DA::Create_2D_Sound( "com_nuke_beep.wav" ); 
			//Create_3D_WAV_Sound_At_Bone_Player( Get_Owner(),"com_nuke_beep.wav",  )
			BeepTimer++;
			Commands->Create_3D_WAV_Sound_At_Bone("com_nuke_beep.wav",Get_Owner(),"c Head");
			if ( BeepTimer < 45 )
				Start_Timer(888, 1.5f);
			
		}
		else if(Number == 999) // com loop
		{
			DA::Create_2D_Sound( "comloop12.wav" ); 
			ComTimer++;
			if ( ComTimer < 30 )
				Start_Timer(999, 2.0f);
		}

		else if(Number == 30)
		{
			DA::Host_Message("The Walking Bomb is going to Explode in 30 Second's." );
			DA::Create_2D_Sound("m00evag_dsgn0073i1evag_snd.wav"); // 30
			Start_Timer(555, 1.0f);
			Start_Timer(25, 5.0f);
		}
		else if(Number == 25)
		{
			DA::Create_2D_Sound("m00evag_dsgn0074i1evag_snd.wav"); // 25
			Start_Timer(20, 5.0f);
			Start_Timer(777, 1.0f);
		}
		else if(Number == 20)
		{
			DA::Create_2D_Sound("m00evag_dsgn0075i1evag_snd.wav"); // 20
			Start_Timer(15, 5.0f);
			Start_Timer(777, 1.0f);
		}
		else if(Number == 15)
		{
			DA::Create_2D_Sound("m00evag_dsgn0076i1evag_snd.wav"); // 15
			Start_Timer(10, 5.0f);
			Start_Timer(1111, 8.8f);
			Start_Timer(777, 1.0f);
		}
		else if(Number == 10)
		{
			DA::Host_Message("The Walking Bomb is going to Explode in 10 Second's." );
			DA::Create_2D_Sound("m00evag_dsgn0077i1evag_snd.wav"); //10
			DA::Create_2D_Sound("nuke_strike_buildup_nocount.wav"); //nuke alarm
			Start_Timer(9, 1.0f);
		}
		else if(Number == 9)
		{
			DA::Create_2D_Sound("m00evag_dsgn0078i1evag_snd.wav"); //9
			Start_Timer(8, 1.0f);
		}
		else if(Number == 8)
		{
			DA::Create_2D_Sound("m00evag_dsgn0079i1evag_snd.wav"); //8
			Start_Timer(7, 1.00f);
		}
		else if(Number == 7)
		{
			DA::Create_2D_Sound("m00evag_dsgn0080i1evag_snd.wav"); //7
			Start_Timer(6, 1.0f);
		}
		else if(Number == 6)
		{
			DA::Create_2D_Sound("m00evag_dsgn0081i1evag_snd.wav"); //6
			Start_Timer(5, 1.0f);
		}
		else if(Number == 5)
		{
			DA::Create_2D_Sound("m00evag_dsgn0082i1evag_snd.wav"); // 5
			Start_Timer(4, 1.0f);
		}
		else if(Number == 4)
		{
			DA::Create_2D_Sound("m00evag_dsgn0083i1evag_snd.wav"); // 4
			Start_Timer(3, 1.5f);
		}
		else if(Number == 3)
		{
			DA::Create_2D_Sound("m00evag_dsgn0084i1evag_snd.wav"); // 3
			Start_Timer(2, 1.0f);
		}
		else if(Number == 2)
		{
			DA::Create_2D_Sound("m00evag_dsgn0085i1evag_snd.wav"); // 2
			Start_Timer(1, 1.0f);
		}
		else if(Number == 1)
		{
			DA::Create_2D_Sound("m00evag_dsgn0086i1evag_snd.wav"); // 1
			Start_Timer(0, 1.0f);
		}
		else if(Number == 0)
		{
			DA::Create_2D_Sound("m00evag_dsgn0087i1evag_snd.wav"); // 0
			Start_Timer(1000, 0.1f);
		}
		else if(Number == 1111) // Nuke Cinematic
		{
			Vector3 pos = Commands->Get_Position(Get_Owner());
			pos.Z+=10;
			GameObject *nuke = Commands->Create_Object("Generic_Cinematic",pos);
			Commands->Set_Model(nuke,"XG_AG_Nuke");
			Commands->Attach_Script(nuke,"JFW_PlayAnimation_DestroyObject","Nuke_Missle.Nuke_Missle");
		}
		else if(Number == 1000 ) //kill player
		{
		    if ( NukeObject )
				Commands->Destroy_Object(NukeObject);
			if (Get_Vehicle(Get_Owner())) 
			{
				Commands->Apply_Damage(Get_Vehicle(Get_Owner()), 99999.0f, "None", 0);
				Start_Timer(1001, 0.1f);
			}
			
			Commands->Apply_Damage(Get_Owner(), 99999.0f, "None", 0);
		}
		else if(Number == 1001 ) //delay killing player in vehicle
		{
			Commands->Apply_Damage(Get_Owner(), 99999.0f, "None", 0);
		}
	}

	virtual void Kill_Received(ArmedGameObj *Killer,float Damage,unsigned int Warhead,float Scale,DADamageType::Type Type) 
	{
		if ( !BombArmed )
		{
			DA::Create_2D_Sound("amb_powerdown.wav");  
			DA::Create_2D_Sound("00-n016e.wav");
			DA::Host_Message("The Walking Bomb was killed before the bomb was armed. Disaster Avoided." );
			Commands->Destroy_Object(Commands->Find_Object(nuke_id));
			Set_Delete_Pending();
			return;
		}

		if ( !Is_Player(Killer) )
			Killer = 0;
		int Team = Get_Player_Type(Get_Owner());
		if ( Team == 0 )
			Team = 1;
		else if ( Team == 1 )
			Team = 0;
		Commands->Create_Object("Beacon_Nuke_Strike_Anim_Post",Commands->Get_Position(Get_Owner()));
		Commands->Create_Explosion("Explosion_NukeBeacon",Commands->Get_Position(Get_Owner()),0);
		DA::Create_2D_Sound("nuke_strike_fire.wav");
		Damage_All_Objects_Area_By_Team2(2500.0f,"None",Commands->Get_Position(Get_Owner()),22.0f,0,true,true,true,Team);
		Commands->Give_Points(Get_Owner(),100.0f,false);
		Commands->Shake_Camera(Commands->Get_Position(Get_Owner()), 1000.000f, 0.10f, 1.0f);
		Commands->Destroy_Object(Commands->Find_Object(nuke_id));
		//Get_Owner()->Set_Delete_Pending();
		Set_Delete_Pending();
	}
};






















/********************************************************************************************************************************/

class DARandomCharacterCrateClass : public DACrateClass {
	virtual void Settings_Loaded() {
		DACrateClass::Settings_Loaded();

		//Characters
		Characters.Delete_All();
		for (int Team = 0;Team < 2;Team++) { //Add all purchasable characters into vector.
			for (int Type = 0;Type < 7;Type++) {
				PurchaseSettingsDefClass *PT = PurchaseSettingsDefClass::Find_Definition((PurchaseSettingsDefClass::TYPE)Type,(PurchaseSettingsDefClass::TEAM)Team);
				if (PT) {
					for (int i = 0;i < 10;i++) {
						SoldierGameObjDef *Def = (SoldierGameObjDef*)Find_Definition(PT->Get_Definition(i));
						if (Def && Def->Get_Class_ID() == CID_Soldier) {
							DynamicVectorClass<const SoldierGameObjDef*> Chars;
							Chars.Add(Def);
							Def = (SoldierGameObjDef*)Find_Definition(PT->Get_Alt_Definition(i,0));
							if (Def && Def->Get_Class_ID() == CID_Soldier) {
								Chars.Add(Def);
							}
							Def = (SoldierGameObjDef*)Find_Definition(PT->Get_Alt_Definition(i,1));
							if (Def && Def->Get_Class_ID() == CID_Soldier) {
								Chars.Add(Def);
							}
							Def = (SoldierGameObjDef*)Find_Definition(PT->Get_Alt_Definition(i,2));
							if (Def && Def->Get_Class_ID() == CID_Soldier) {
								Chars.Add(Def);
							}
							Characters.Add(Chars);
						}
					}
				}
			}
		}
	}

	virtual bool Can_Activate(cPlayer *Player) {
		return Characters.Count() > 1;
	}

	virtual void Activate(cPlayer *Player) {
		Reselect:
		int Rand = Get_Random_Int(0,Characters.Count()); //Get random character.
		DynamicVectorClass<const SoldierGameObjDef*> &Chars = Characters[Rand];
		if (Chars.ID(&Player->Get_GameObj()->Get_Definition()) != -1) { //Don't pick the character they already are.
			goto Reselect;
		}
		Rand = Get_Random_Int(0,Chars.Count()); //Get random skin of that character.
		const SoldierGameObjDef *Character = Chars[Rand];
		Player->Get_GameObj()->Re_Init(*Character);
		Player->Get_GameObj()->Post_Re_Init();
		DA::Page_Player(Player,"You have been transformed into %s by the Random Character Crate.",a_or_an_Prepend(DATranslationManager::Translate(Character)));
	}
	DynamicVectorClass<DynamicVectorClass<const SoldierGameObjDef*>> Characters;
};

Register_Crate(DARandomCharacterCrateClass,"Random Character",DACrateType::INFANTRY);

/********************************************************************************************************************************/

class DARandomVehicleCrateClass : public DACrateClass {
	virtual void Settings_Loaded() {
		DACrateClass::Settings_Loaded();

		//Vehicles
		Vehicles.Delete_All();
		if (Find_Vehicle_Factory(0) && Find_Vehicle_Factory(1)) {
			for (int Team = 0;Team < 2;Team++) { //Add all purchasable vehicles into vector.
				for (int Type = 0;Type < 7;Type++) {
					PurchaseSettingsDefClass *PT = PurchaseSettingsDefClass::Find_Definition((PurchaseSettingsDefClass::TYPE)Type,(PurchaseSettingsDefClass::TEAM)Team);
					if (PT) {
						for (int i = 0;i < 10;i++) {
							VehicleGameObjDef *Def = (VehicleGameObjDef*)Find_Definition(PT->Get_Definition(i));
							if (Def && Def->Get_Class_ID() == CID_Vehicle && (Def->Get_Type() != VEHICLE_TYPE_FLYING || Is_Map_Flying()) && Def->Get_Type() != VEHICLE_TYPE_BOAT && Def->Get_Type() != VEHICLE_TYPE_SUB) {
								DynamicVectorClass<const VehicleGameObjDef*> Vehs;
								Vehs.Add(Def);
								Def = (VehicleGameObjDef*)Find_Definition(PT->Get_Alt_Definition(i,0));
								if (Def && Def->Get_Class_ID() == CID_Vehicle && (Def->Get_Type() != VEHICLE_TYPE_FLYING || Is_Map_Flying()) && Def->Get_Type() != VEHICLE_TYPE_BOAT && Def->Get_Type() != VEHICLE_TYPE_SUB) {
									Vehs.Add(Def);
								}
								Def = (VehicleGameObjDef*)Find_Definition(PT->Get_Alt_Definition(i,1));
								if (Def && Def->Get_Class_ID() == CID_Vehicle && (Def->Get_Type() != VEHICLE_TYPE_FLYING || Is_Map_Flying()) && Def->Get_Type() != VEHICLE_TYPE_BOAT && Def->Get_Type() != VEHICLE_TYPE_SUB) {
									Vehs.Add(Def);
								}
								Def = (VehicleGameObjDef*)Find_Definition(PT->Get_Alt_Definition(i,2));
								if (Def && Def->Get_Class_ID() == CID_Vehicle && (Def->Get_Type() != VEHICLE_TYPE_FLYING || Is_Map_Flying()) && Def->Get_Type() != VEHICLE_TYPE_BOAT && Def->Get_Type() != VEHICLE_TYPE_SUB) {
									Vehs.Add(Def);
								}
								Vehicles.Add(Vehs);
							}
						}
					}
				}
			}
			bool Recon = true;
			bool SSM = true;
			for (int i = 0;i < Vehicles.Count();i++) {
				DynamicVectorClass<const VehicleGameObjDef*> &Vehs = Vehicles[i];
				for (int x = 0;x < Vehs.Count();x++) {
					if (stristr(Vehs[x]->Get_Name(),"Recon_Bike") || stristr(DATranslationManager::Translate(Vehs[x]),"Recon Bike")) {
						Recon = false;
					}
					if (stristr(Vehs[x]->Get_Name(),"SSM") || stristr(DATranslationManager::Translate(Vehs[x]),"Surface")) {
						SSM = false;
					}
				}
			}
			if (Recon) { //Add the stock Recon Bike if the map doesn't have its own.
				VehicleGameObjDef *Def = (VehicleGameObjDef*)Find_Named_Definition("CnC_Nod_Recon_Bike");
				if (Def) {
					DynamicVectorClass<const VehicleGameObjDef*> Vehs;
					Vehs.Add(Def);
					Vehicles.Add(Vehs);
				}
			}
			if (SSM) { //Add the stock SSM Launcher if the map doesn't have its own.
				VehicleGameObjDef *Def = (VehicleGameObjDef*)Find_Named_Definition("Nod_SSM_Launcher_Player"); //Special case for SSM.
				if (Def) {
					DynamicVectorClass<const VehicleGameObjDef*> Vehs;
					Vehs.Add(Def);
					Vehicles.Add(Vehs);
				}
			}
		}
		
		//Drop point
		DASettingsManager::Get_Vector3(Position[0],"Nod_Vehicle_Drop",Vector3());
		DASettingsManager::Get_Vector3(Position[1],"GDI_Vehicle_Drop",Vector3());
		Facing[0] = DASettingsManager::Get_Float("Nod_Vehicle_Drop_Facing",0.0f);
		Facing[1] = DASettingsManager::Get_Float("GDI_Vehicle_Drop_Facing",0.0f);
	}

	virtual bool Can_Activate(cPlayer *Player) { //No drop points or vehicles on this map.
		return (Vehicles.Count() && (Position[0].X || Position[0].Y || Position[0].Z) && (Position[1].X || Position[1].Y || Position[1].Z));
	}
	
	virtual void Activate(cPlayer *Player) {
		int Rand = Get_Random_Int(0,Vehicles.Count()); //Get random vehicle.
		DynamicVectorClass<const VehicleGameObjDef*> Vehs = Vehicles[Rand];
		Rand = Get_Random_Int(0,Vehs.Count());
		const VehicleGameObjDef *Def = Vehs[Rand]; //Get random skin of that vehicle.
		VehicleGameObj *Vehicle = (VehicleGameObj*)Create_Object(Def,Vector3());
		Vehicle->Lock_Vehicle(Player->Get_GameObj(),44.0f);
		DAVehicleManager::Air_Drop_Vehicle(Player->Get_Player_Type(),Vehicle,Position[Player->Get_Player_Type()],Facing[Player->Get_Player_Type()]);
		Player->Get_GameObj()->Set_Position(Position[Player->Get_Player_Type()]);
		Fix_Stuck_Objects(Position[Player->Get_Player_Type()],10.0f,15.0f);
		DA::Host_Message("Looks like %ls just got a random vehicle. Go them!",Get_Wide_Team_Name(Player->Get_Player_Type()));
		DA::Page_Player(Player,"You have received %s from the Random Vehicle Crate. It will be dropped at your position momentarily.",a_or_an_Prepend(DATranslationManager::Translate(Def)));
	}

	DynamicVectorClass<DynamicVectorClass<const VehicleGameObjDef*>> Vehicles;
	Vector3 Position[2];
	float Facing[2];
};

Register_Crate(DARandomVehicleCrateClass,"Random Vehicle",DACrateType::INFANTRY);

/********************************************************************************************************************************/

class DAArmsDealerCrateClass : public DACrateClass {
	virtual void Settings_Loaded() {
		DACrateClass::Settings_Loaded();

		//Add all main weapons to vector.
		Weapons.Delete_All();
		for (int Team = 0;Team < 2;Team++) {
			for (int Type = 0;Type < 7;Type++) {
				PurchaseSettingsDefClass *PT = PurchaseSettingsDefClass::Find_Definition((PurchaseSettingsDefClass::TYPE)Type,(PurchaseSettingsDefClass::TEAM)Team);
				if (PT) {
					for (int i = 0;i < 10;i++) {
						SoldierGameObjDef *Def = (SoldierGameObjDef*)Find_Definition(PT->Get_Definition(i));
						if (Def && Def->Get_Class_ID() == CID_Soldier) {
							WeaponDefinitionClass *Weapon = (WeaponDefinitionClass*)Find_Definition(Def->WeaponDefID);
							if (Weapon) {
								Weapons.Add(Weapon);
							}
							Def = (SoldierGameObjDef*)Find_Definition(PT->Get_Alt_Definition(i,0));
							if (Def && Def->Get_Class_ID() == CID_Soldier) {
								Weapon = (WeaponDefinitionClass*)Find_Definition(Def->WeaponDefID);
								if (Weapon) {
									Weapons.Add(Weapon);
								}
							}
							Def = (SoldierGameObjDef*)Find_Definition(PT->Get_Alt_Definition(i,1));
							if (Def && Def->Get_Class_ID() == CID_Soldier) {
								Weapon = (WeaponDefinitionClass*)Find_Definition(Def->WeaponDefID);
								if (Weapon) {
									Weapons.Add(Weapon);
								}
							}
							Def = (SoldierGameObjDef*)Find_Definition(PT->Get_Alt_Definition(i,2));
							if (Def && Def->Get_Class_ID() == CID_Soldier) {
								Weapon = (WeaponDefinitionClass*)Find_Definition(Def->WeaponDefID);
								if (Weapon) {
									Weapons.Add(Weapon);
								}
							}
						}
					}
				}
			}
		}
	}
	
	virtual bool Can_Activate(cPlayer *Player) {
		return (Weapons.Count() && Player->Get_GameObj()->Get_Weapon_Bag()->Get_Count() < 30);
	}

	virtual void Activate(cPlayer *Player) {
		WeaponBagClass *Bag = Player->Get_GameObj()->Get_Weapon_Bag();
		for (int i = 0;i < Weapons.Count();i++) {
			Bag->Add_Weapon(Weapons[i],999);
		}
		DA::Page_Player(Player,"You have been given all weapons by the Arms Dealer Crate.");
	}

	DynamicVectorClass<WeaponDefinitionClass*> Weapons;
};

Register_Crate(DAArmsDealerCrateClass,"Arms Dealer",DACrateType::INFANTRY);

/********************************************************************************************************************************/



class DAClownCrateClass : public DACrateClass 
{
	virtual void Settings_Loaded() {
		DACrateClass::Settings_Loaded();
	}
	
	virtual bool Can_Activate(cPlayer *Player) { //Prevent crate from triggering if already in effect.
		//return !RxDMap;
		return !Player->Get_GameObj()->Find_Observer("DAClownsCrateClass");;
	}

	virtual void Activate(cPlayer *Player) 
	{
		if ( RxDMap() )
		{
			int number = rand()%36 + 1;
			char clown[10];
			if( number < 10 )
				sprintf(clown,"clw0%d",number);
			else
				sprintf(clown,"clw%d",number);
			Console_InputF("setmodel %d %s",Player->Get_Id(), clown);
			Player->Get_GameObj()->Add_Observer(new DAClownSoundsObserverClass());

			DA::Page_Player(Player,"You have been turned into a Clown.");
		}
	}
};
Register_Crate(DAClownCrateClass,"Clown",DACrateType::INFANTRY);


class DAClownsCrateClass : public DACrateClass 
{
	virtual void Settings_Loaded() {
		DACrateClass::Settings_Loaded();

	}
	
	virtual bool Can_Activate(cPlayer *Player) { //Prevent crate from triggering if already in effect.
		//return !RxDMap(), 
		return !Player->Get_GameObj()->Find_Observer("DAClownsCrateClass");;
	}

	virtual void Activate(cPlayer *Player) 
	{
		if ( RxDMap() )
		{
			for (SLNode<cPlayer>* PlayerIter = Get_Player_List()->Head(); (PlayerIter != NULL); PlayerIter = PlayerIter->Next())
			{
				cPlayer *p = PlayerIter->Data();
				if (p->IsActive && Get_GameObj(p->Get_Id()))
				{	
					//if ( PData[p->Get_Id()]->Spectating ) { continue; }
					int number = rand()%36 + 1;
					char clown[10];
					if( number < 10 )
						sprintf(clown,"clw0%d",number);
					else
						sprintf(clown,"clw%d",number);
					Console_InputF("setmodel %d %s",p->Get_Id(), clown);
				}
			}
			Player->Get_GameObj()->Add_Observer(new DACrazyClownSoundsObserverClass());
			DA::Page_Player(Player,"You got the evil clown crate.");
		}
	}
};
Register_Crate(DAClownsCrateClass,"Clowns",DACrateType::INFANTRY);


class DAWalkingBombCrateClass : public DACrateClass 
{
	virtual void Settings_Loaded() {
		DACrateClass::Settings_Loaded();
	}
	
	virtual bool Can_Activate(cPlayer *Player) { //Prevent crate from triggering if already in effect.
		//return !RxDMap();
		return !Player->Get_GameObj()->Find_Observer("DAWalkingBombCrateClass");
	}

	virtual void Activate(cPlayer *Player) 
	{
		Player->Get_GameObj()->Add_Observer(new DAWalkingBombObserverClass());
		Commands->Set_Is_Visible(Player->Get_GameObj(),false);
		//DA::Host_Message("%ls has been turned into a Walking Bomb. Kill him before he explodes.", Player->Get_Name() );
		DA::Page_Player(Player,"You just got the Walking Bomb Crate.");
		DA::Host_Message("Oh no! %ls has been turned into a Walking Bomb. May God have mercy on his soul.", Player->Get_Name() );
	}
};
Register_Crate(DAWalkingBombCrateClass,"Walking Bomb",DACrateType::INFANTRY);


class DADemolitionKitCrateClass : public DACrateClass {
	virtual bool Can_Activate(cPlayer *Player) {
		return (Find_Named_Definition("CnC_Weapon_MineTimed_Player_2Max") && Player->Get_GameObj()->Get_Weapon_Bag()->Get_Count() < 30);
	}

	virtual void Activate(cPlayer *Player) 
	{

		WeaponBagClass *Bag = Player->Get_GameObj()->Get_Weapon_Bag();
		DefinitionClass *x = Find_Named_Definition("CnC_Weapon_MineTimed_RxD");
		if ( RxDMap() && x)
		{
			Bag->Add_Weapon("Weapon_MineProximity_RxD",999);
			Bag->Add_Weapon("CnC_Weapon_MineRemote_RxD",999);
			Bag->Add_Weapon("CnC_Weapon_MineRemote_RxD_2Max",999);
			Bag->Add_Weapon("CnC_Weapon_MineTimed_RxD",999);
			Bag->Add_Weapon("CnC_Weapon_MineTimed_RxD_2Max",999);
		}
		else
		{
			Bag->Add_Weapon("Weapon_MineProximity_Player",999);
			Bag->Add_Weapon("CnC_Weapon_MineRemote_Player",999);
			Bag->Add_Weapon("CnC_Weapon_MineRemote_Player_2Max",999);
			Bag->Add_Weapon("CnC_Weapon_MineTimed_Player",999);
			Bag->Add_Weapon("CnC_Weapon_MineTimed_Player_2Max",999);
		}

		DA::Page_Player(Player,"You have received 3 Timed C4, 3 Remote C4, and 6 Proximity C4 from the Demolition Kit Crate. Use them wisely.");
	}
};

Register_Crate(DADemolitionKitCrateClass,"Demolition Kit",DACrateType::INFANTRY);

/********************************************************************************************************************************/

class DAAdrenalineCrateObserverClass : public DAGameObjObserverClass {
	virtual const char *Get_Name() { 
		return "DAAdrenalineCrateObserverClass"; 
	}

	virtual void Init() {
		((SoldierGameObj*)Get_Owner())->Set_Max_Speed(((SoldierGameObj*)Get_Owner())->Get_Max_Speed()*2);
		Start_Timer(1,Get_Random_Float(60.0f,90.0f)); //End
	}

	virtual void Timer_Expired(GameObject *obj,int Number) {
		((SoldierGameObj*)Get_Owner())->Set_Max_Speed(((SoldierGameObj*)Get_Owner())->Get_Max_Speed()/2);
		Set_Delete_Pending();
	}
};

class DAAdrenalineCrateClass : public DACrateClass {
	virtual bool Can_Activate(cPlayer *Player) { //Prevent crate from triggering if already in effect.
		return !Player->Get_GameObj()->Find_Observer("DAAdrenalineCrateObserverClass");
	}

	virtual void Activate(cPlayer *Player) {
		Player->Get_GameObj()->Add_Observer(new DAAdrenalineCrateObserverClass);
		DA::Page_Player(Player,"The Adrenaline Crate has temporarily doubled your run speed.");
	}
};

Register_Crate(DAAdrenalineCrateClass,"Adrenaline",DACrateType::INFANTRY);

/********************************************************************************************************************************/

class DATiberiumMutantCrateObserverClass : public DAGameObjObserverClass 
{
	StringClass Preset;

	virtual const char *Get_Name() { 
		return "DATiberiumMutantCrateObserverClass"; 
	}

	virtual void Init() 
	{
		DefinitionClass *x = Find_Named_Definition("CNC_Weapon_ChemSprayer_RxD");
		if ( RxDMap() && x ) { Preset = "CNC_Weapon_ChemSprayer_RxD"; }
		else { Preset = "CNC_Weapon_ChemSprayer_Player"; }
		WeaponBagClass *Bag = ((SoldierGameObj*)Get_Owner())->Get_Weapon_Bag();
		Bag->Clear_Weapons();
		Bag->Add_Weapon(Preset,999);
		Bag->Select_Index(1);
		const_cast<Matrix3D&>(((SoldierGameObj*)Get_Owner())->Get_Transform()).Adjust_Z_Translation(1.0f); //Fix stuck in ground.
		Start_Timer(1,1.0f);

	}

	virtual void Timer_Expired(GameObject *obj,int Number) {
		Start_Timer(1,1.0f);
		DefenseObjectClass *Defense = ((SoldierGameObj*)Get_Owner())->Get_Defense_Object(); //Small health regen.
		if (Defense->Get_Health_Max() == Defense->Get_Health()) {
			Defense->Add_Shield_Strength(1.0f);
		}
		else {
			Defense->Add_Health(1.0f);
		}
		Set_Bullets(Get_Owner(),Preset,100);
		//Set_Bullets(Get_Owner(),"CNC_Weapon_ChemSprayer_Player",100); //Infinite ammo, no reload.
		Vector3 Position;
		Get_Owner()->Get_Position(&Position);
		for (SLNode<SoldierGameObj> *x = GameObjManager::SoldierGameObjList.Head();x;x = x->Next()) { //AOE damage.
			if (x->Data()->Get_Player_Type() != ((SoldierGameObj*)Get_Owner())->Get_Player_Type() && Commands->Get_Distance(Position,x->Data()->Get_Position()) < 5.0f) {
				Commands->Apply_Damage(x->Data(),1.0f,"TiberiumRaw",Get_Owner());
			}
		}
	}

	virtual bool Vehicle_Entry_Request(VehicleGameObj *Vehicle,int &Seat) {
		return false; //Can't enter vehicles.
	}

	virtual bool Add_Weapon_Request(const WeaponDefinitionClass *Weapon) {
		return !_stricmp(Weapon->Get_Name(),Preset); //Can only use chem sprayer.
	}
	
	virtual bool Damage_Received_Request(ArmedGameObj *Damager,float &Damage,unsigned int &Warhead,float Scale,DADamageType::Type Type) {
		if (Type == DADamageType::SQUISH || Type == DADamageType::FALL) {
			return false; //Can't be squished and doesn't take fall damage.
		}
		else if (Type != DADamageType::REPAIR) {
			Damage *= 0.5f; //Only takes half damage.
		}
		return true;
	}

	virtual void Kill_Received(ArmedGameObj *Killer,float Damage,unsigned int Warhead,float Scale,DADamageType::Type Type) {
		Get_Owner()->Set_Delete_Pending(); //Fix bug where the player won't respawn when they die because the visceroid doesn't have a death animation.
	}
};

class DATiberiumMutantCrateClass : public DACrateClass {
	virtual void Settings_Loaded() {
		DACrateClass::Settings_Loaded();

		//Setup Visceroid preset. The already existing presets can't be used because they don't have hands.
		SoldierGameObjDef *Mutant = (SoldierGameObjDef*)Find_Named_Definition("CnC_GDI_Mutant_2SF_Templar");
		SoldierGameObjDef *Visceroid = (SoldierGameObjDef*)Find_Named_Definition("CnC_Visceroid");
		if (Mutant && Visceroid) {
			Mutant->WeaponDefID = 0;
			Mutant->ScriptNameList.Delete_All();
			Mutant->ScriptParameterList.Delete_All();
			DefenseObjectDefClass *Defense = &const_cast<DefenseObjectDefClass&>(Mutant->Get_DefenseObjectDef());
			int Skin = ArmorWarheadManager::Get_Armor_Type("SkinMutant");
			Defense->Skin = Skin;
			Defense->ShieldType = Skin;
			Defense->HealthMax = 500.0f;
			Defense->Health = 500.0f;
			Defense->ShieldStrengthMax = 0.0f;
			Defense->DamagePoints = 0.05f;
			Defense->DeathPoints = 100.0f;
			Mutant->PhysDefID = Visceroid->PhysDefID;
		}
	}

	virtual bool Can_Activate(cPlayer *Player) { //Prevent crate from triggering if already in effect.
		return (!Player->Get_GameObj()->Find_Observer("DATiberiumMutantCrateObserverClass") && Find_Named_Definition("CnC_GDI_Mutant_2SF_Templar"));
	}

	virtual void Activate(cPlayer *Player) {
		SoldierGameObj *Soldier = Player->Get_GameObj();
		Player->Get_DA_Player()->Reset_Creation_Time();
		Soldier->Set_Delete_Pending();
		SoldierGameObj *Visceroid = Create_Commando(Player,"CnC_GDI_Mutant_2SF_Templar",Soldier->Get_Transform());
		Visceroid->Add_Observer(new DATiberiumMutantCrateObserverClass);
		DA::Host_Message("A %ls player has been mutated by the Tiberium Mutant Crate!",Get_Wide_Team_Name(Player->Get_Player_Type()));
	}
};

Register_Crate(DATiberiumMutantCrateClass,"Tiberium Mutant",DACrateType::INFANTRY);

/********************************************************************************************************************************/

class DAHumanSiloCrateObserverClass : public DAGameObjObserverClass {
	virtual const char *Get_Name() { 
		return "DAHumanSiloCrateObserverClass"; 
	}

	virtual void Init() {
		Total = 0;
	}

	virtual void Damage_Received(ArmedGameObj *Damager,float Damage,unsigned int Warhead,float Scale,DADamageType::Type Type) {
		if (Type == DADamageType::TIBERIUM || Warhead == 9 || Warhead == 10 || Warhead == 11) { //Tiberium based warheads.
			Give_Credits_Team(((SoldierGameObj*)Get_Owner())->Get_Player_Type(),Damage/2);
			Total += Damage;
			DefenseObjectClass *Defense = ((SoldierGameObj*)Get_Owner())->Get_Defense_Object();
			if (Total >= (Defense->Get_Health_Max()+Defense->Get_Shield_Strength_Max())) { //Wear off after taking tiberium damage equal to character's health.
				Set_Delete_Pending();
			}
		}
	}

	float Total;
};

class DAHumanSiloCrateClass : public DACrateClass {
	virtual bool Can_Activate(cPlayer *Player) { //Prevent crate from triggering if already in effect.
		return !Player->Get_GameObj()->Find_Observer("DAHumanSiloCrateObserverClass");
	}
	virtual void Activate(cPlayer *Player) {
		Player->Get_GameObj()->Add_Observer(new DAHumanSiloCrateObserverClass);
		DA::Page_Player(Player,"You picked up the Human Silo Crate. Any tiberium damage you take will be converted into credits for your team.");
	}
};

Register_Crate(DAHumanSiloCrateClass,"Human Silo",DACrateType::INFANTRY);

/********************************************************************************************************************************/






