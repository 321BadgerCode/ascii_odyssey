//potato
#pragma once

using namespace std;

namespace color{
	typedef const uint8_t clr_t;

	class type{
	public:
		static clr_t bold=1;
		static clr_t dim=2;
		static clr_t italic=3;
		static clr_t under_line=4;
		static clr_t blink=5;
		static clr_t invisible=8;
		static clr_t strike_through=9;
		static clr_t under_line_bold=21;
		static clr_t fg=38;
		static clr_t bg=48;
		static clr_t over_line=53;
	};
	struct rgb;
	string set_clr(const string text,const rgb* color,clr_t type=type::fg);
	struct rgb{
		uint8_t r;
		uint8_t g;
		uint8_t b;

		/**
		 * @brief set 'rgb' to clr..
		 *
		 */
		rgb(uint8_t r2,uint8_t g2,uint8_t b2):r(r2),g(g2),b(b2){}
		operator int*() const {
			return new int[3]{r,g,b};
		}
		operator string() const {
			return 	set_clr("rgb",this)+"("+
				set_clr(to_string(r),new rgb(0xff,0x0,0x0))+","+
				set_clr(to_string(g),new rgb(0x0,0xff,0x0))+","+
				set_clr(to_string(b),new rgb(0x0,0x0,0xff))+")";
		}
		/**
		 * @brief get lerping of clr..
		 *
		 * @link https://www.alanzucconi.com/2016/01/06/colour-interpolation/
		 *
		 */
		rgb* get_lerp(const rgb* a1,const float k=1){
			return new rgb(
				r + ((a1->r - r) * k),
				g + ((a1->g - g) * k),
				b + ((a1->b - b) * k)
			);
		}
	};

	//ROYGBIV & common colors.
	rgb* black=new rgb(0x0,0x0,0x0);
	rgb* red=new rgb(0xff,0x0,0x0);
	rgb* orange=new rgb(0xff,0x88,0x0);
	rgb* yellow=new rgb(0xff,0xff,0x0);
	rgb* green=new rgb(0x0,0xff,0x0);
	rgb* blue=new rgb(0x0,0x0,0xff);
	rgb* indigo=new rgb(0x44,0x0,0x88);
	rgb* violet=new rgb(0xff,0x88,0xff);
	rgb* white=new rgb(0xff,0xff,0xff);

	rgb* grey=new rgb(0xf0,0xf0,0xf0);
	rgb* cyan=new rgb(0x0,0xff,0xff);
	rgb* magenta=new rgb(0xff,0x0,0xff);

	string begin2="\33[";
	string end2="\33[0m";

	//functions to set the color of text.
	string set_clr(const string text,clr_t type,clr_t color){
		string b1="";

		if(type==type::fg||type==type::bg){b1=begin2+to_string(type)+";5;"+to_string(color)+"m"+text+end2;}
		else{b1=begin2+to_string(type)+"m"+text+end2;}

		return b1;
	}
	string set_clr(const string text,const rgb* color,clr_t type){
		string b1="";

		if(type==type::fg||type==type::bg){b1=begin2+to_string(type)+";2;"+to_string(color->r)+";"+to_string(color->g)+";"+to_string(color->b)+"m"+text+end2;}
		else{b1=begin2+to_string(type)+"m"+text+end2;}

		return b1;
	}
};