
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;



double MinValue(int n, double A,  double B){
	double min = A;
	double h_1 = A;
	double h;
	for( int i = 2; i < n; i++) {
		h = (n - i) / (n - i + 1.) * abs(h_1) + 1 / ( n - i + 1.) * B - n + i;


		//

	//	cout << " h = " << h << " h_1 = " << h_1 << ";   ";
		//

		if(abs(h) < 0.000000000001){
			h = abs(h);
		}

		h_1 = h;

		if(h < min){
			min = h;
		}
	}

	//
	//cout << "min = " << min <<  endl;
	//
	return min;
}







double Process( int n, double A){
	double e = 0.0000000001;
	double B;
	double top = A;
	double min = A;
	double bottom = 0.;
	//double min1,min2;
	double min_before = 2*A;
	int counter = 0;

	while( MinValue(n, top, A) < 0.){
		top = 2. * top;
	}

//	while( abs(min - min_before) > e ){ // negative check
	while( abs(min) > e ){ // negative check
		B = (top + bottom) / 2. ;

		min_before = min;
		min = MinValue(n, A, B);

		if( min == min_before){
			counter++;
		}else{
			counter = 0;
		}
		//

		//cout << "B = " << B  << " min =  " << min << endl;

		//
		if( min >= 0){
			top = B;
		}else{
			bottom = B;
		}

		if(counter > 10){
			break;
		}
	}

	return B;
}




int main() {

	ifstream input("input.txt");
	int n;
	double A;
	input >> n >> A;

	//
	//cout << n << " " << A << endl;
	//
	double B = Process(n , A);
	ofstream output("output.txt");
    //cout << B << endl;
	output << fixed << setprecision(20) <<  B;


	return 0;
}



/*
double Process( int n, double A){
	double e = 0.0000001;
	//double delta = e;
//	vector<double> garland(n);
	double B;
	double top = A;
	double min = A;
	double bottom = 0.;
	//double min1,min2;
	double min_before = 2*A;

	//
	cout << "min = " << min << " min_before = " << min_before << endl;
	//

	while( abs(min - min_before) > e ){ // negative check
		B = (top + bottom) / 2. ;
		min_before = min;
		min = MinValue(n, A, B);
		//min1 = MinValue(n, A, (B + delta));
		//min2 = MinValue(n, A, (B - delta));
//
		//break;
	//

		if( min >= 0){
			top = B;
		}else{
			bottom = B;
		}

			//
				//cout << " min1 = " << min1 << " min2 = " << min2
					//	<< " top = " << top << " bottom = " << bottom  << " B = " <<  B << endl;
				//
		//
						cout << " min = " << min << " min_before = " << min_before
								<< " top = " << top << " bottom = " << bottom  << " B = " <<  B << endl;
						//
	}

	return B;
}
*/
