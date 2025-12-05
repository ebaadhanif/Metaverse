#pragma once

#include <DIS7/EntityID.h>
#include <DIS7/OneByteChunk.h>
#include <vector>
#include <DIS7/RadioCommunicationsFamilyPdu.h>
#include <DISUtils/DataStream.h>
#include <DIS7/msLibMacro.h>
#include <DISEnums/radio_tx_encoding.h>
#include <DISEnums/TDLType.h>
#include <DIS7/IntercomSignalPdu.h>
namespace DIS
{
class EXPORT_MACRO IntercomSignalMessage
{
protected:
	IntercomSignalPdu pdu;
 public:
    IntercomSignalMessage();
    virtual ~IntercomSignalMessage();

    const EntityID&  getIntercomEntityID() const; 
    void setIntercomEntityID(const EntityID &entityIntercomID);

    unsigned short getIntercomCommunicationsDeviceID() const;
    void setIntercomCommunicationsDeviceID(unsigned short intercomID);

	DIS::ENUMS::radio_tx_encoding::EncodingType getIntercomEncodingType() const;
    void setIntercomEncodingType(DIS::ENUMS::radio_tx_encoding::EncodingType et);

	DIS::ENUMS::radio_tx_encoding::EncodingClass getIntercomEncodingClass() const;
	void setIntercomEncodingClass(DIS::ENUMS::radio_tx_encoding::EncodingClass ec);

	DIS::ENUMS::TDLType getIntercomTdlType() const;
    void setIntercomTdlType(DIS::ENUMS::TDLType tdlType);

    unsigned int getIntercomSampleRate() const;
    void setIntercomSampleRate(unsigned int sampleRate);

    unsigned short getIntercomDataLength() const;

    unsigned short getIntercomSamples() const;
    void setIntercomSamples(unsigned short samples);

    const std::vector<OneByteChunk>& getIntercomData() const;
    void setIntercomData(const std::vector<OneByteChunk>&    vecData);
};
}

