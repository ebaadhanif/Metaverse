#pragma once

#include <math.h>

#include <ostream>

#include <DISUtils/Vector2D.h>
#include <DIS7\msLibMacro.h>

class EXPORT_MACRO Vector3D
{
public:

    // ----------------------------------------- generic 3d vector operations

    // three-dimensional Cartesian coordinates
    float x, y, z;

    // constructors
    Vector3D (void): x( 0.0f ), y( 0.0f ), z( 0.0f ) {}
    Vector3D (float X, float Y, float Z) : x( X ), y( Y ), z( Z ) {}

	Vector3D(Vector2D vec2D, float z) : x(vec2D.x), y(vec2D.y), z(z) {}

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

	/// <summary>
	/// <para> Function to set z component of vector </para>
	/// </summary>
	///	<param name ="val"> z component </param>
	/// <returns> returns nothing </returns>
	void setZ(float val) { z = val; }

    // vector addition
    Vector3D operator+ (const Vector3D& v) const {return Vector3D (x+v.x, y+v.y, z+v.z);}

    // vector subtraction
    Vector3D operator- (const Vector3D& v) const {return Vector3D (x-v.x, y-v.y, z-v.z);}

    // unary minus
    Vector3D operator- (void) const {return Vector3D (-x, -y, -z);}

    // vector times scalar product (scale length of vector times argument)
    Vector3D operator* (const float s) const {return Vector3D (x * s, y * s, z * s);}

    // vector divided by a scalar (divide length of vector by argument)
    Vector3D operator/ (const float s) const {return Vector3D (x / s, y / s, z / s);}

	//convert to vector2d
	Vector2D toVector2D() { return Vector2D(this->x, this->y); }

	/// <summary>
	/// <para> Function to calculate dot product between two vectors </para>
	/// </summary>
	///	<param name ="v"> vector to do dot product with </param>
	/// <returns> returns floating dot product value </returns>
    float dot (const Vector3D& v) const {return (x * v.x) + (y * v.y) + (z * v.z);}
		
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
	/// <returns> returns normalized Vector3D </returns>
    Vector3D normalized (void) const
    {
        // skip divide if length is zero
        const float len = length ();
        return (len>0) ? (*this)/len : (*this);
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
			z = z / len;
		}
	}

	/// <summary>
	/// <para> Function to get cross product between two vectors (A x B), and store result in this vector </para>
	/// </summary>
	///	<param name ="a"> Vector A </param>
	///	<param name ="b"> Vector B </param>
	/// <returns> returns nothing </returns>
    void cross(const Vector3D& a, const Vector3D& b)
    {
        *this = Vector3D ((a.y * b.z) - (a.z * b.y),
                        (a.z * b.x) - (a.x * b.z),
                        (a.x * b.y) - (a.y * b.x));
    }

    // assignment
    Vector3D operator= (const Vector3D& v) {x=v.x; y=v.y; z=v.z; return *this;}

	/// <summary>
	/// <para> Function to set x, y and z component of vector </para>
	/// </summary>
	///	<param name ="_x"> x component </param>
	///	<param name ="_y"> y component </param>
	///	<param name ="_z"> z component </param>
	/// <returns> returns this vector </returns>
    Vector3D set (const float _x, const float _y, const float _z)
    {x = _x; y = _y; z = _z; return *this;}

    // +=
    Vector3D operator+= (const Vector3D& v) {return *this = (*this + v);}

    // -=
    Vector3D operator-= (const Vector3D& v) {return *this = (*this - v);}

    // *=
    Vector3D operator*= (const float& s) {return *this = (*this * s);}

        
    Vector3D operator/=( float d ) { return *this = (*this / d);  }
        
    // equality/inequality
    bool operator== (const Vector3D& v) const {return x==v.x && y==v.y && z==v.z;}
    bool operator!= (const Vector3D& v) const {return !(*this == v);}
};