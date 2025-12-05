#pragma once
#include <DIS7\EntityStatePdu.h>
#include <DISUtils\PDUType.h>
#include <DIS7\Pdu.h>
#include <DISUtils\DataStream.h>
#include <DISUtils\Endian.h>

//#include"DISTime.h"
#include<vector>
#include<iterator>
//#include"DISTime.h"
#include<math.h>

namespace DIS {
	constexpr int SMALLEST_PDU_OCTET = 1472;
	constexpr int  OCTET = 8;

	using namespace std;
	class CPDUBundle
	{
	public:
		vector<DIS::Pdu*> m_PduVec;
		vector<DIS::Pdu> vecpdu;
		//CDISTime DISTime;

		int m_BundleSize{ 0 };
		DIS::DataStream m_dataStream{ DIS::Endian::LITTLE };
		int m_expectedPduPaddingBytes{ 0 };

		~CPDUBundle();
		static	CPDUBundle* GetInstance();

		//For Sending
		bool AddPdu(DIS::Pdu *pdu);
		//Ended

		//For Receiving
		void ConvertDataStreamToPduVector();
		//Ended

		void SendPduBundle();

	private:
		CPDUBundle();
		static CPDUBundle* m_pduBundle;


		//For Sending
		int CalculatePduLength();
		bool ComparePduTimeStamp(unsigned int currentPDUTime); // Already defined in DISTime class (Include DISTime class in project)
		bool IsVoicePdu(DIS::Pdu *pdu);
		void AddPduInBundle(DIS::Pdu *pdu);
		//void sendPduBundle();
		//Ended

		//For Receiving
		void ExtractPdu();
		void SendToIncomingMessageProcessor();
		//Ended


		void ClearPDUBundle();

		//incomingMessageProcessor
	};
}

