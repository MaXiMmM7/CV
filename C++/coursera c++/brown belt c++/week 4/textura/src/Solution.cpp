#include "Common.h"
#include "utility"
#include <iostream>

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`
//enum class ShapeType { Rectangle, Ellipse };




class Shape:public IShape {
public:
  Shape(ShapeType s_t):type_(s_t){}
//  ~Shape() = default;
  // Возвращает точную копию фигуры.
  // Если фигура содержит текстуру, то созданная копия содержит ту же самую
  // текстуру. Фигура и её копия совместно владеют этой текстурой.

  std::unique_ptr<IShape> Clone() const override;

  void SetPosition(Point) override;
  Point GetPosition() const override;


  void SetSize(Size) override;
  Size GetSize() const override;

  void SetTexture(std::shared_ptr<ITexture>) override;
  ITexture* GetTexture() const override;



  // Рисует фигуру на указанном изображении
  void Draw(Image&) const override;

  private:
  Point position_;
  Size size_;
  std::shared_ptr<ITexture> texture_;
  ShapeType type_;
};


//////////////////////////////////
std::unique_ptr<IShape> Shape::Clone() const{
	  auto t=*this;
	  return make_unique<Shape>(t);
}
void Shape::SetPosition(Point p){
	  position_=p;
	  //cout << "position: " << position_.x << " " << position_.y << endl;
}

Point Shape::GetPosition() const{
	return position_;
}
void Shape::SetSize(Size s){
	  size_=s;
	 // cout << "size: " << size_.width << " " << size_.height << endl;
}

Size Shape::GetSize() const {
	  return size_;
}

void Shape::SetTexture(std::shared_ptr<ITexture> t){
	  texture_=move(t);
	  if(texture_!=nullptr){
	  //cout << "texture_size: " << texture_->GetSize().width << " " <<texture_->GetSize().height << endl;
	  }
	  }

ITexture* Shape::GetTexture() const{
	  return texture_.get();
}

void Shape::Draw(Image& im) const{
	  if(position_.x<static_cast<int>(im[0].size()) && position_.y<static_cast<int>(im.size()) ){
		//int x_start=position_.x;
		//int y_start=position_.y;

		//cout << endl << "Draw starts" <<(position_.y+size_.height) << endl;
		for (int y=position_.y;y<(position_.y+size_.height);y++ ){

			if(y<static_cast<int>(im.size())){
				//cout << "y is : " << y << endl;
				for (int x=position_.x;x<(position_.x+size_.width);x++ ){
					//cout << "x= " << x << "  y=  " << y << endl;
					if(x<static_cast<int>(im[0].size())){
						if(type_==ShapeType::Rectangle||IsPointInEllipse({x-position_.x,y-position_.y},size_)){
							if(texture_!=nullptr){
							//cout << "Texture createria " << ((y-position_.y)<texture_->GetSize().height) << endl;
							}
							if(texture_!=nullptr&&((y-position_.y)<texture_->GetSize().height) && ((x-position_.x)<texture_->GetSize().width)){
							//cout << "We work with texture!   " << (x-position_.x) << (y-position_.y) << endl;
							im[y][x]=texture_->GetImage()[y-position_.y][x-position_.x];
						}
						else{
							im[y][x]='.';
						}
					}

				}
			}
		}
	  }
	  }
  }



// Напишите реализацию функции
unique_ptr<IShape> MakeShape(ShapeType shape_type) {
	if(shape_type==ShapeType::Rectangle){
		return make_unique<Shape>(ShapeType::Rectangle);
	}
	return make_unique<Shape>(ShapeType::Ellipse);
}
