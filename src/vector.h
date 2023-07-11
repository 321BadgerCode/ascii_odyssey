#pragma once

namespace ao{
	template<typename T=int>
	class vector{
	public:
		T x;
		T y;
		T z;

		vector(T x_val=0,T y_val=0,T z_val=0):x(x_val),y(y_val),z(z_val){}
		vector<T> operator+(const vector<T>& other) const {
			return vector<T>(x+other.x,y+other.y,z+other.z);
		}
		vector<T> operator-(const vector<T>& other) const {
			return vector<T>(x-other.x, y-other.y,z-other.z);
		}
		vector<T> operator*(T scalar) const {
			return vector<T>(x*scalar,y*scalar,z*scalar);
		}
		vector<T> operator/(T scalar) const {
			return vector<T>(x/scalar,y/scalar,z/scalar);
		}
		T operator [](int index) const {
			switch(index){
				case(0):return x;break;
				case(1):return y;break;
				case(2):return z;break;
				default:return x;break;
			}
		}
		operator string() const {
			return 	"("+to_string(x)+","+
				to_string(y)+","+
				to_string(z)+")";
		}
	};
};