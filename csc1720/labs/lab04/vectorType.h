/*
Matt Burton
csc1720
2/2/21
csc1720/labs/lab04/vectorType.h

a class forstoring and manipulating vectors
*/

#ifndef VECTOR_TYPE
#define VECTOR_TYPE

class vectorType
{
	private:
		double x;
		double y;
		double z;
	public:
		void setComps(double, double, double);
		void printVector() const;
		double calcMagnitude();
		vectorType scalarMultiply(double);
		double getX() const;
		double getY() const;
		double getZ() const;
		vectorType(double, double, double);
		vectorType();
};

#endif
