#pragma once

#include <DIS7/EntityID.h>
#include <DIS7/EventIdentifier.h>
#include <DIS7/SystemIdentifier.h>
#include <DIS7/FundamentalOperationalData.h>
#include <DIS7/LayerHeader.h>
#include <DIS7/BeamData.h>
#include <DIS7/SecondaryOperationalData.h>
#include <DIS7/IFFFundamentalParameterData.h>
#include <DIS7/Vector3Float.h>
#include <DIS7/DistributedEmissionsFamilyPdu.h>
#include <vector>
#include <DISUtils/DataStream.h>
#include <DIS7\msLibMacro.h>


namespace DIS
{
//This PDU is written according SISO Standard, the link is on below:
//https://www.sisostds.org/DesktopModules/Bring2mind/DMX/API/Entries/Download?Command=Core_Download&EntryId=36292&PortalId=0&TabId=105
//Another good document for DIS v6 and v7 is:
//https://www.sisostds.org/DesktopModules/Bring2mind/DMX/API/Entries/Download?Command=Core_Download&EntryId=29289&PortalId=0&TabId=105

// @author semihkurt , 09/04/2021

class EXPORT_MACRO IFFPdu : public DistributedEmissionsFamilyPdu
{
protected:
  /** ID of the entity emitting */
  EntityID _emittingEntityID; 

  /** ID of event */
  EventIdentifier _eventID;

  Vector3Float _relativeAntennaLocation;

  SystemIdentifier _systemID;

  unsigned char _systemDesignator;

  unsigned char _systemSpecificData;

  FundamentalOperationalData _fundamentalOperationalData;

 public:
    IFFPdu();
    virtual ~IFFPdu();

    virtual void marshal(DataStream& dataStream) const;
    virtual void unmarshal(DataStream& dataStream);

    EntityID& getEmittingEntityID(); 
    const EntityID&  getEmittingEntityID() const; 
    void setEmittingEntityID(const EntityID    &pX);

    EventIdentifier& getEventID(); 
    const EventIdentifier&  getEventID() const; 
    void setEventID(const EventIdentifier    &pX);

    Vector3Float& getRelativeAntennaLocation(); 
    const Vector3Float&  getRelativeAntennaLocation() const; 
    void setRelativeAntennaLocation(const Vector3Float    &pX);

    SystemIdentifier& getSystemID();
    const SystemIdentifier& getSystemID() const;
    void setSystemID(const SystemIdentifier  &pX);

    unsigned char getSystemDesignator() const;
    void setSystemDesignator(unsigned char pX);

    unsigned char getSystemSpecificData() const;
    void setSystemSpecificData(unsigned char pX);

    FundamentalOperationalData& getFundamentalOperationalData();
    const FundamentalOperationalData& getFundamentalOperationalData() const;
    void setFundamentalOperationalData(const FundamentalOperationalData    &pX);
 
virtual int getMarshalledSize() const;

     bool operator  ==(const IFFPdu& rhs) const;
};
}

