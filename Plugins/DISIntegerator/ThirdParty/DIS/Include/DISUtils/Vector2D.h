#pragma once

#include <math.h>

#include <ostream>
#include <DIS7\msLibMacro.h>

class EXPORT_MACRO Vector2D
{
public:

	// ----------------------------------------- generic 2d vector operations

	// two-dimensional Cartesian coordinates
	float x, y;

	float vAngle;
	float vLen;

	// constructors
	Vector2D(void) : x(0.0f), y(0.0f) { vAngle = 0.0f; vLen = 0.0f; }
	Vector2D(float X, float Y) : x(X), y(Y) { vAngle = 0.0f; vLen = 0.0f; }

	/// <summary>
	/// <para> Function to set x component of vector </para>
	/// </summary>
	///	<param name ="val"> x component </param>
	/// <returns> returns nothing </returns>
	void setX(float val) { x = val; }

	/// <summary>
	/// <para> Function to set y component of vector </para>
	/// </summary>
	///	<param name ="val"> y component </param>
	/// <returns> returns nothing </returns>
	void setY(float val) { y = val; }

    // vector addition
    Vector2D operator+ (const Vector2D& v) const {return Vector2D (x+v.x, y+v.y);}

    // vector subtraction
    Vector2D operator- (const Vector2D& v) const {return Vector2D (x-v.x, y-v.y);}

    // unary minus
    Vector2D operator- (void) const {return Vector2D (-x, -y);}

    // vector times scalar product (scale length of vector times argument)
    Vector2D operator* (const float s) const {return Vector2D (x * s, y * s);}

    // vector divided by a scalar (divide length of vector by argument)
    Vector2D operator/ (const float s) const {return Vector2D (x / s, y / s);}

	/// <summary>
	/// <para> Function to calculate dot product between two vectors </para>
	/// </summary>
	///	<param name ="v"> vector to do dot product with </param>
	/// <returns> returns floating dot product value </returns>
    float dot (const Vector2D& v) const {return (x * v.x) + (y * v.y);}
		
	/// <summary>
	/// <para> Function to calculate mangitude of this vector </para>
	/// </summary>
	/// <returns> returns floating length value </returns>
    float length (void) const {return sqrt(lengthSquared ());}

	/// <summary>
	/// <para> Function to calculate mangitude squared of this vector </para>
	/// </summary>
	/// <returns> returns floating length squared value </returns>
    float lengthSquared (void) const {return this->dot (*this);}

	/// <summary>
	/// <para> Function to normalize this vector </para>
	/// </summary>
	/// <returns> returns nothing </returns>
    void normalized (void) const
    {
        // skip divide if length is zero
        const float len = length ();
        (len>0) ? (*this)/len : (*this);
    }

	/// <summary>
	/// <para> Function to normalize this vector </para>
	/// </summary>
	/// <returns> returns nothing </returns>
	void normalize()
	{
		// skip divide if length is zero
		const float len = length();
		if (len > 0) {
			x = x / len;
			y = y / len;
		}
	}

	/// <summary>
	/// <para> Function to set angle of this vector </para>
	/// </summary>
	///	<param name ="angle"> the angle value to set in radians </param>
	/// <returns> returns nothing </returns>
	void setAngle(float angle) { this->vAngle = angle; float len = length(); x = cos(angle) * len; y = sin(angle) * len; }

	/// <summary>
	/// <para> Function to get angle of this vector </para>
	/// </summary>
	/// <returns> returns angle value in radian </returns>
	float angle() 
	{ 
		return atan2f(y, x); 
	}

    // assignment
    Vector2D operator= (const Vector2D& v) {x=v.x; y=v.y; return *this;}

	/// <summary>
	/// <para> Function to set x and y component of vector </para>
	/// </summary>
	///	<param name ="_x"> x component </param>
	///	<param name ="_y"> y component </param>
	/// <returns> returns this vector </returns>
    Vector2D set (const float _x, const float _y)
    {x = _x; y = _y; return *this;}

    // +=
    Vector2D operator+= (const Vector2D& v) {return *this = (*this + v);}

    // -=
    Vector2D operator-= (const Vector2D& v) {return *this = (*this - v);}

    // *=
    Vector2D operator*= (const float& s) {return *this = (*this * s);}

    // /=
    Vector2D operator/=( float d ) { return *this = (*this / d);  }
        
    // equality/inequality
	bool operator== (const Vector2D& v) const { return x == v.x && y == v.y; }
    bool operator!= (const Vector2D& v) const {return !(*this == v);}


	/// <summary>
	/// <para> Function to get right perpendicular of this vector </para>
	/// </summary>
	/// <returns> returns Vector2D </returns>
	Vector2D GetPerpendicularRt()
	{
		return Vector2D(y, -x);
	}

	/// <summary>
	/// <para> Function to get left perpendicular of this vector </para>
	/// </summary>
	/// <returns> returns Vector2D </returns>
	Vector2D GetPerpendicularLt()
	{
		return Vector2D(-y, x);
	}





	//Special Cases

	/// <summary>
	/// <para> Function to perform addition with another vector </para>
	/// </summary>
	///	<param name ="Vec1"> the vector to add </param>
	/// <returns> returns this vector after addition </returns>
	Vector2D Add(Vector2D Vec1)
	{
		x += Vec1.x;
		y += Vec1.y;

		return *this;
	}

	/// <summary>
	/// <para> Function to perform subtraction with another vector </para>
	/// </summary>
	///	<param name ="Vec1"> the vector to subtract </param>
	/// <returns> returns this vector after subtraction </returns>
	Vector2D Subtract(Vector2D Vec1)
	{
		x -= Vec1.x;
		y -= Vec1.y;

		return *this;
	}

	/// <summary>
	/// <para> Function to perform multiplication with floating value </para>
	/// </summary>
	///	<param name ="num"> the floating value to multiply with </param>
	/// <returns> returns this vector after multiplication </returns>
	Vector2D Multiply(float num)
	{
		x *= num;
		y *= num;

		return *this;
	}

	/// <summary>
	/// <para> Function to perform division with floating value </para>
	/// </summary>
	///	<param name ="num"> the floating value to divide with </param>
	/// <returns> returns this vector after division </returns>
	Vector2D Divide(float num)
	{
		x /= num;
		y /= num;

		return *this;
	}
};