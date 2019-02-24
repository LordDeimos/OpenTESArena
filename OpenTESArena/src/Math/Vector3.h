#ifndef VECTOR3_H
#define VECTOR3_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <type_traits>
#include <unordered_map>

class Random;

template <class T>
class Vector3i
{
public:
	static_assert(std::is_integral<T>::value, "Vector3i<T> must be integral type.");

	T x, y, z;

	Vector3i(T x, T y, T z);
	Vector3i();

	T &operator[](size_t index);
	const T &operator[](size_t index) const;
	bool operator==(const Vector3i<T> &v) const;
	bool operator!=(const Vector3i<T> &v) const;
	Vector3i<T> operator+(const Vector3i<T> &v) const;

	// Only signed integers can use negation.
	template <class C = T>
	typename std::enable_if<std::is_signed<C>::value, Vector3i<T>>::type operator-() const
	{
		return Vector3i<T>(-this->x, -this->y, -this->z);
	}

	Vector3i<T> operator-(const Vector3i<T> &v) const;
	Vector3i<T> operator*(T m) const;
	Vector3i<T> operator*(const Vector3i<T> &v) const;
	Vector3i<T> operator/(T m) const;
	Vector3i<T> operator/(const Vector3i<T> &v) const;

	std::string toString() const;
};

template <class T>
class Vector3f
{
public:
	static_assert(std::is_floating_point<T>::value, "Vector3f<T> must be floating-point type.");

	static const Vector3f<T> Zero;
	static const Vector3f<T> UnitX;
	static const Vector3f<T> UnitY;
	static const Vector3f<T> UnitZ;

	T x, y, z;

	Vector3f(T x, T y, T z);
	Vector3f();
	Vector3f(const Vector3f<double>& old);
	Vector3f(const Vector3f<float>& old);

	static Vector3f<T> randomDirection(Random &random);
	static Vector3f<T> randomPointInSphere(const Vector3f<T> &center, T radius, Random &random);
	static Vector3f<T> randomPointInCuboid(const Vector3f<T> &center, T width, T height,
		T depth, Random &random);
	static Vector3f<T> fromRGB(uint32_t rgb);

	T &operator[](size_t index);
	const T &operator[](size_t index) const;
	bool operator==(const Vector3f<T> &v) const;
	bool operator!=(const Vector3f<T> &v) const;
	Vector3f<T> operator+(const Vector3f<T> &v) const;
	Vector3f<T> operator-() const;
	Vector3f<T> operator-(const Vector3f<T> &v) const;
	Vector3f<T> operator*(T m) const;
	Vector3f<T> operator*(const Vector3f<T> &v) const;
	Vector3f<T> operator/(T m) const;
	Vector3f<T> operator/(const Vector3f<T> &v) const;

	std::string toString() const;
	uint32_t toRGB() const;
	double getYAngleRadians() const;
	T lengthSquared() const;
	T length() const;
	Vector3f<T> normalized() const;
	bool isNormalized() const;
	T dot(const Vector3f<T> &v) const;
	Vector3f<T> cross(const Vector3f<T> &v) const;
	Vector3f<T> reflect(const Vector3f<T> &normal) const;
	Vector3f<T> lerp(const Vector3f<T> &end, T percent) const;
	Vector3f<T> slerp(const Vector3f<T> &end, T percent) const;
	Vector3f<T> clamped(T low, T high) const;
	Vector3f<T> clamped() const;
	Vector3f<T> componentMin(const Vector3f<T> &v) const;
	Vector3f<T> componentMax(const Vector3f<T> &v) const;
};

// Unit vector definitions (can't be in .cpp file on Clang).
template <class T>
const Vector3f<T> Vector3f<T>::Zero(
	static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(0.0));

template <class T>
const Vector3f<T> Vector3f<T>::UnitX(
	static_cast<T>(1.0), static_cast<T>(0.0), static_cast<T>(0.0));

template <class T>
const Vector3f<T> Vector3f<T>::UnitY(
	static_cast<T>(0.0), static_cast<T>(1.0), static_cast<T>(0.0));

template <class T>
const Vector3f<T> Vector3f<T>::UnitZ(
	static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(1.0));

// The template instantiations are at the end of the .cpp file.
// - size_t vector types cause issues with GCC 4.8.4 32-bit (identical to unsigned int).
typedef Vector3i<char> Char3;
typedef Vector3i<unsigned char> Uchar3;
typedef Vector3i<short> Short3;
typedef Vector3i<unsigned short> Ushort3;
typedef Vector3i<int> Int3;
typedef Vector3i<unsigned int> Uint3;

typedef Vector3f<float> Float3;
typedef Vector3f<double> Double3;

// Hash definition for unordered_map<Int3, ...>.
namespace std
{
	template <>
	struct hash<Int3>
	{
		size_t operator()(const Int3 &v) const
		{
			// Multiply with some prime numbers before xor'ing.
			return static_cast<size_t>(v.x ^ (v.y * 41) ^ (v.z * 199));
		}
	};
}

#endif
