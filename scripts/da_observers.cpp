

#include "general.h"
#include "engine.h"
#include "engine_da.h"
#include "da.h"
#include "da_settings.h"
#include "da_translation.h"
#include "da_vehicle.h"
#include "da_log.h"
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
		Damage_All_Objects_Area_By_Team2(2500.0f,"None",Commands->Get_Position(Get_Owner()),18.0f,0,true,true,true,Team);
		Commands->Give_Points(Get_Owner(),100.0f,false);
		Commands->Shake_Camera(Commands->Get_Position(Get_Owner()), 1000.000f, 0.10f, 1.0f);
		Commands->Destroy_Object(Commands->Find_Object(nuke_id));
		//Get_Owner()->Set_Delete_Pending();
		Set_Delete_Pending();
	}
};