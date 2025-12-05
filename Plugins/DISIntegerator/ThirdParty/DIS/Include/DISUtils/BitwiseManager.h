#pragma once
#include <DIS7\msLibMacro.h>

namespace DIS 
{
	class EXPORT_MACRO CBitwiseManager
	{
		public:
			CBitwiseManager();
			~CBitwiseManager();

			static unsigned short SetBit(unsigned short data, unsigned short pos, short flag);
			static unsigned int	SetNthBit(unsigned int data, int pos, short flag);

			static int ClearNthBit(int data, int pos);
			static bool	IsNthBitSet(unsigned short data, int pos);
			static int ToggleNthBit(int data, int pos);

			static unsigned long long CombineTwoIntegers(unsigned long upperBitsData, unsigned long lowerBitsData);
			static void	SplitTwoIntegers(unsigned long long combinedValue, unsigned long& upperBitsData, unsigned long& lowerBitsData);

			static short GetBitValue(unsigned short number, int n);
			static short GetNthBitValue(unsigned int number, int n);

			static void ExractBitsFromTwoBitNumber(short number, short& bit1, short& bit2);
			static short ExractTwoBitNumberFromBits(short bit1, short bit2);

			static void ExractBitsFromThreeBitNumber(int number, short& bit1, short& bit2, short& bit3);
			static short ExractThreeBitNumberFromBits(short bit1, short bit2, short bit3);

			static void SplitDigits(int number, int arr[4]);
			static int CombineDigitsToFormNumber(int* numArr, int size);

			static int ConvertfromBinaryToDecimal(int* arr, int size);
			static void ConvertFromDecimalToBinary(unsigned int number, int arr[11]);
	};
}
