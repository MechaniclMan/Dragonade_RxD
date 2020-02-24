/*	Renegade Scripts.dll
    Dragonade Vehicle Purchase Queue Game Feature
	Copyright 2017 Whitedragon, Tiberian Technologies

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/

#ifndef INCLUDE_DAVEHICLEQUEUE
#define INCLUDE_DAVEHICLEQUEUE

#include "da_event.h"
#include "da_gamefeature.h"
#include "VehicleFactoryGameObj.h"

class DAVehicleQueueGameFeatureClass : public DAEventClass, public DAGameFeatureClass {
private:
	struct DAVehicleQueueStruct {
		DAVehicleQueueStruct(cPlayer *Player,const VehicleGameObjDef *Vehicle,float Cost) {
			this->Vehicle = Vehicle;
			this->Player = Player;
			this->Cost = Cost;
		};
		cPlayer *Player;
		const VehicleGameObjDef *Vehicle;
		float Cost;
		
	private:
		DAVehicleQueueStruct();
	};

	virtual void Init();
	~DAVehicleQueueGameFeatureClass();
	virtual void Level_Loaded_Event();
	virtual int Vehicle_Purchase_Request_Event(BaseControllerClass *Base,cPlayer *Player,float &Cost,const VehicleGameObjDef *Item);
	virtual bool Request_Vehicle_Event(VehicleFactoryGameObj *Factory,const VehicleGameObjDef *Vehicle,cPlayer *Player,float Delay);
	virtual void Team_Change_Event(cPlayer *Player);
	virtual void Player_Leave_Event(cPlayer *Player);
	virtual void Object_Created_Event(GameObject *obj);
	virtual void Kill_Event(DamageableGameObj *Victim,ArmedGameObj *Killer,float Damage,unsigned int Warhead,float Scale,DADamageType::Type Type);
	bool VQ_Chat_Command(cPlayer *Player,const DATokenClass &Text,TextMessageEnum ChatType);
	virtual void Timer_Expired(int Number,unsigned int Team);

	void Spawn_Vehicle(int Team,DAVehicleQueueStruct *Q);
	void Spawn_Vehicle(int Team,cPlayer *Player,const VehicleGameObjDef *Vehicle,float Cost);
	void Clear(int Team);
	void Add(int Team,cPlayer *Player,const VehicleGameObjDef *Vehicle,float Cost,bool Head = false);
	bool Remove(int Team,cPlayer *Player);
	void Send_Positions(int Team);

	inline bool Is_Building(int Team) {
		return !!Building[Team];
	}
	
private:
	DAVehicleQueueStruct *Building[2];
	DynamicVectorClass<DAVehicleQueueStruct*> Queue[2];
};

#endif