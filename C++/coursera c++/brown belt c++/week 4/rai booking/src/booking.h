


namespace RAII{

template<typename Provider>
class Booking{
private:
	Provider* prv=nullptr;

public:
	Booking(Provider* provider, int&):prv(provider){}

	Booking(const Booking&) = delete;
	Booking& operator=(const Booking&) = delete;

	Booking(Booking&& obj):prv(obj.prv){
		obj.prv=nullptr;
	}
    Booking& operator=(Booking&& obj){
    	if(this!=&obj){
    		prv=obj.prv;
    		obj.prv=nullptr;
    	}
    	return *this;
    }

	~Booking(){
	if(prv){
		prv->CancelOrComplete(*this);
	}
	}
};
}


