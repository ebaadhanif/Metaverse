#pragma once

#include <DISUtils/DataStream.h>
#include <DIS7\msLibMacro.h>


namespace DIS
{
// Used to convey information for one or more AttributeRecords. AttributeRecords conform to the standard variable record format of 6.2.82. Section 6.2.10

// Copyright (c) 2007-2009, MOVES Institute, Naval Postgraduate School. All rights reserved. 
//
// @author DMcG, jkg

// length in bytes for the variable data. This should be a dynamically allocated array.
#define STATIC_ARRAY_LENGTH 128

class EXPORT_MACRO AttributeRecord
{
protected:

    /** This field shall specify the type of the record. It shall be represented by a 32-bit enumeration.*/
    unsigned int _recordType; 

    /** This field shall specify the total length of the Attribute record in octets. It shall be represented by a 16-bit unsigned integer.
    The value of the Attribute Record Length shall be the sum of the sizes of the Record Type field, the Record
    Length field, all Record-Specific fields, and any padding required to end the record on a 64-bit
    boundary. The Attribute Record Length value shall be a multiple of 8. */
    unsigned short      _recordLength;

    /** The variable datum data.*/
    std::vector<char>   _recordSpecificFields;
    unsigned int        _arrayLength;                              //local variable, would not be transmitted


 public:
    AttributeRecord();
    virtual ~AttributeRecord();

    virtual void marshal(DataStream& dataStream) const;
    virtual void unmarshal(DataStream& dataStream);

    unsigned int getRecordType() const; 
    void setRecordType(unsigned int pX); 

    unsigned short getRecordLength() const;
    void setRecordLength(unsigned short pX);

    char* getRecordSpecificFields();
    const char* getRecordSpecificFields() const;
    void setRecordSpecificFields(const char* pX, const unsigned int length);


virtual int getMarshalledSize() const;

     bool operator  ==(const AttributeRecord& rhs) const;
};
}

// Copyright (c) 1995-2009 held by the author(s).  All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
//  are met:
// 
//  * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// * Neither the names of the Naval Postgraduate School (NPS)
//  Modeling Virtual Environments and Simulation (MOVES) Institute
// (http://www.nps.edu and http://www.MovesInstitute.org)
// nor the names of its contributors may be used to endorse or
//  promote products derived from this software without specific
// prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// AS IS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
