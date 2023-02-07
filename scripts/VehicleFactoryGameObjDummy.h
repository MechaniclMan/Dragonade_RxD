

#ifndef VEHICLE_FACTORY_GAME_OBJ_DUMMY_H
#define VEHICLE_FACTORY_GAME_OBJ_DUMMY_H

#include "general.h"
#include "engine.h"
#include "BuildingGameObj.h"
#include "ReferencerClass.h"
#include "Matrix3D.h"

class VehicleFactoryGameObjDummy : public BuildingGameObj
{
public:
    virtual    void                            Init(void) {}

    ReferencerClass    Vehicle;
    Matrix3D                CreationTM;
    OBBoxClass            GeneratingRegion;
    float                    GenerationTime;
    int                    GeneratingVehicleID;
    bool                    IsBusy;
    bool                IsDisabled;
    ReferencerClass    Purchaser;
    int                    LastDeliveryPath;
    int                 LastFlyingDeliveryPath;
    float                    EndTimer;
    static int MaxVehiclesPerTeam;
}; // 08CC
#endif // !VEHICLE_FACTORY_GAME_OBJ_DUMMY_H