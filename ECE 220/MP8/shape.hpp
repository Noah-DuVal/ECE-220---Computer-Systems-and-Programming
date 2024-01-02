#ifndef SHAPE_H_
#define SHAPE_H_

#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>
#include <fstream>
#include <iomanip>

using namespace std;

// Base class
// Please implement Shape's member functions
// constructor, getName()
class Shape
{
public:
	// Base class' constructor should be called in derived classes'
	// constructor to initizlize Shape's private variable
	Shape(string name)
	{

	name_ = name;

	}

	string getName()
	{

/*
ifstream ifs ("", std::ifstream::in);
ifs >> name_; 
ifs.close();
*/
		return name_;
	}

	virtual double getArea() const = 0;
	virtual double getVolume() const = 0;

private:
	string name_;
};

// Rectangle
// Please implement the member functions of Rectangle:
// constructor, getArea(), getVolume(), operator+, operator-

template <class T>
class Rectangle : public Shape
{
public:
	Rectangle(double width = 0, double length = 0) : Shape("Rectangle")
	{

	width_ = width;
	length_ = length;

	}

	double getArea() const
	{
	int a;
	a = width_*length_;
	
		return (double) (a);
	}

	double getVolume() const
	{
		return 0;
	}

	Rectangle operator+(const Rectangle &rec)
	{
            double l, w;
            l = this->length_ + rec.length_;
            w = this->width_ + rec.width_;
            
            return Rectangle(l, w);
	}

	Rectangle operator-(const Rectangle &rec)
	{
            double l, w;
	l = this->length_ - rec.length_;
	w = this->width_ - rec.width_;

            l = max(0.0, l);
            w = max(0.0, w);
            
            return Rectangle(l, w);
	}

	double getWidth() const
	{
		return width_;
	}

	double getLength() const
	{
		return length_;
	}

private:
	double width_;
	double length_;
};

// Circle
// Please implement the member functions of Circle:
// constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape
{
public:
	Circle(double radius) : Shape("Circle")
	{

	radius_ = radius;

	}

	double getArea() const
	{
		return (pow(radius_,2) * M_PI);
	}

	double getVolume() const
	{
		return 0;
	}

	Circle operator+(const Circle &cir)
	{
		double r;

		r = this->radius_ + cir.radius_;

		return Circle(r);
	}

	Circle operator-(const Circle &cir)
	{
		double r;

		r = max(0.0,this->radius_ - cir.radius_);


		return Circle(r);
	}

	double getRadius() const
	{
		return radius_;
	}

private:
	double radius_;
};

// Sphere
// Please implement the member functions of Sphere:
// constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape
{
public:
	Sphere(double radius) : Shape("Sphere")
	{

	radius_ = radius;

	}

	double getVolume() const
	{
		return ((4.0/3.0) * pow(radius_,3) * M_PI);
	}

	double getArea() const
	{
		return (4*M_PI * pow(radius_,2));
	}

	Sphere operator+(const Sphere &sph)
	{
		double r;

		r = this->radius_ + sph.radius_;

		return Sphere(r);
	}

	Sphere operator-(const Sphere &sph)
	{
		double r;

		r = max(0.0,this->radius_ - sph.radius_);

		return Sphere(r);
	}

	double getRadius() const
	{
		return radius_;
	}

private:
	double radius_;
};

// Rectprism
// Please implement the member functions of RectPrism:
// constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape
{
public:
	RectPrism(double width, double length, double height) : Shape("RectPrism")
	{

	width_ = width;
	length_ = length;
	height_ = height;

	}

	double getVolume() const
	{
		return (length_*width_*height_);
	}

	double getArea() const
	{
		return (2*((length_*width_) + (length_*height_) + (height_*width_)));
	}

	RectPrism operator+(const RectPrism &rectp)
	{
		double l,w,h;

            l = this->length_ + rectp.length_;
            w = this->width_ + rectp.width_;
            h = this->height_ + rectp.height_;

		return RectPrism(l,w,h);
	}

	RectPrism operator-(const RectPrism &rectp)
	{
		double l,w,h;

            l = max(0.0,this->length_ - rectp.length_);
            w = max(0.0,this->width_ - rectp.width_);
            h = max(0.0,this->height_ - rectp.height_);

		return RectPrism(l,w,h);
	}

	double getWidth() const
	{
		return width_;
	}

	double getLength() const
	{
		return length_;
	}

	double getHeight() const
	{
		return height_;
	}

private:
	double length_;
	double width_;
	double height_;
};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
static list<Shape *> CreateShapes(char *file_name)
{
	//@@Insert your code here

	list<Shape *> myShape;
	return myShape;
}

// call getArea() of each object
// return the max area
static double MaxArea(list<Shape *> shapes)
{
	double ma;
	ma = 0.0;

/*

	ma = 0;
	ma += Rectangle::getArea();
	ma += Circle().getArea();
	ma += Sphere::getArea();
	ma += RectPrism::getArea();
		
*/	

//for (list<Shape *>::iterator it =shapes.begin(); it != shapes.end(); it++) {
  //  ma += (*it)->getArea();
//}


	return ma;
}

// call getVolume() of each object
// return the max volume
static double MaxVolume(list<Shape *> shapes)
{
	return -0.0;
}
#endif
