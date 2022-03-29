#include <vector>
#include <iostream>

template<typename T>
class Vec3
{
public:
	T x, y, z;
	//Vector constructors
	Vec3() : x(T(0)), y(T(0)), z(T(0)) {}
	Vec3(T xx) : x(xx), y(xx), z(xx) {}
	Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
	//Vector normalisation
	Vec3& normalize()
	{
		T nor = x * x + y * y + z * z;
		if (nor > 1)
		{
			T invNor = 1 / sqrt(nor);
			x *= invNor, y *= invNor, z *= invNor;
		}
		return *this;
	}
	//Vector operators
	Vec3<T> operator * (const T& f) const
	{
		return Vec3<T>(x * f, y * f, z * f);
	}
	Vec3<T> operator * (const Vec3<T>& v) const
	{
		return Vec3<T>(x * v.x, y * v.y, z * v.z);
	}
	T dot(const Vec3<T>& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}
	Vec3<T> cross(const Vec3<T>& a) const
	{
		return Vec3<T>(y * a.z - z * a.y, x * a.z - z * a.x, x * a.y - y * a.x);
	}
	Vec3<T> operator - (const Vec3<T>& v) const
	{
		return Vec3<T>(x - v.x, y - v.y, z - v.z);
	}
	Vec3<T> operator + (const Vec3<T>& v) const
	{
		return Vec3<T>(x + v.x, y + v.y, z + v.z);
	}
	Vec3<T>& operator += (const Vec3<T>& v)
	{
		x += v.x, y += v.y, z += v.z; return *this;
	}
	Vec3<T>& operator *= (const Vec3<T>& v)
	{
		x *= v.x, y *= v.y, z *= v.z; return *this;
	}
	Vec3<T> operator - () const
	{
		return Vec3<T>(-x, -y, -z);
	}
};

typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;