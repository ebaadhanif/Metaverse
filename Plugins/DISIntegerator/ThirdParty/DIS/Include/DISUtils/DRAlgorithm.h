#pragma once

#include <DIS7/EulerAngles.h>
#include <DIS7/Vector3Double.h>
#include <DIS7/Vector3Float.h>
#include <DISUtils/DISDefinitions.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/operation.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <DIS7/msLibMacro.h>

namespace DIS
{
#define DIS_PI 3.141592654
	static double MIN_ROTATION_RATE = 0.2 * DIS_PI / 180.0;

	class EXPORT_MACRO CDRAlgorithm
	{

	protected:
		Vector3Double _entityLocation;
		EulerAngles _entityOrientation;
		EulerAngles _entityBodyOrientation;
		Vector3Float _entityLinearVelocity;
		Vector3Float _entityLinearAcceleration;
		Vector3Float _entityAngularVelocity;

	public:
		CDRAlgorithm(void);
		~CDRAlgorithm(void);

		virtual void Render(float changeDelta, unsigned short applicationType) = 0;
		virtual void Interpolate(float changeDelta, double lerpFactor, Vector3Double startPoint, Vector3Double controlPoint, Vector3Double predictedPoint) = 0;

		// Setter Funtions for Entity State Data
		void SetEntityLocation(Vector3Double);
		void SetEntityLinearVelocity(Vector3Float velocity);
		void SetEntityOrientation(EulerAngles orientation);
		void SetEntityLinearAcceleration(Vector3Float acceleration);
		void SetEntityAngularVelocity(Vector3Float angularVelocity);

		// Getter Functions for Entity State Data
		Vector3Double GetEntityLocation(GeodeticCoordinates& geodeticCoordinates);
		Vector3Double GetEntityGeocentricLocation();
		Vector3Float GetEntityLinearVelocity();
		EulerAngles GetEntityOrientation(GeodeticCoordinates geodeticPosition);
		EulerAngles GetEntityGeocentricOrientation();
		Vector3Float GetEntityLinearAcceleration();
		Vector3Float GetEntityAngularVelocity();

		EulerAngles  GetEntityBodyOrientation() {
			return _entityBodyOrientation;
		};

		Vector3Double CalculateBezierPoint(double lerpTime, Vector3Double startPoint, Vector3Double controlPoint, Vector3Double endPoint);

	protected:
		// Calulcation Functions for DR Algorithms
		void SetWW(boost::numeric::ublas::matrix<double>& ww);
		void SetSkewOmega(boost::numeric::ublas::matrix<double>& skewOmega);
		void SetInitOrient(boost::numeric::ublas::matrix<double>& initOrient);
		void MakeR1(float changeDelta, boost::numeric::ublas::matrix<double>& R1);
		void MakeR2(float changeDelta, boost::numeric::ublas::matrix<double>& R2);
		void MakeThisDR(boost::numeric::ublas::matrix<double>& DR, float changeDelta);
		void ExtractEulerAngles(EulerAngles& eulerAngles, boost::numeric::ublas::matrix<double> DRR);
	};
}