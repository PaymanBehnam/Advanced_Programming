
// Remember your file headers and comments

#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <climits>

using namespace std;

class MyGrid{

public:
    long getNumRows() const;
    long getNumCols() const;

    long getMyX() const;
    void setMyX(long x);
    long getMyY() const;
    void setMyY(long y);

    vector< vector<long> > getGridElements() const;

    MyGrid(long x, long y, long length, long width);
    MyGrid();
    bool loadGridFromFile(const string filename);

    void zeroOutGrid();

    MyGrid operator+(MyGrid const&) const;
    MyGrid operator-(MyGrid const&) const;

    MyGrid operator+(long const&) const;

    friend MyGrid operator+(long const& lhs, MyGrid const& rhs);

    // Addition assignment
    MyGrid& operator+=(MyGrid const&);
    // Increment
    MyGrid& operator++(); // Prefix
    MyGrid operator++(int); // Postfix

    MyGrid& operator--(); // Prefix
    MyGrid operator--(int); // Postfix

    MyGrid operator-() const;

    bool operator==(MyGrid const&) const;

    friend fstream& operator<<(fstream& os, const MyGrid& gridIn);
    void deepCopy(MyGrid secGrid);
    void addGrid(MyGrid const& secGrid);
    void subGrid(MyGrid const& secGrid);

private:
    long myX, myY;
    vector< vector<long> > gridElements;
};
bool isNumber(string str){
    for (unsigned long int  j = 0; j < str.length(); j++)
        if (isdigit(str[j]) == false)
            return false;

    return true;
}
//MyGrid MyGrid(){}

long MyGrid::getMyX() const{
    return myX;
}
void MyGrid::setMyX(long x){
    myX = x;
}
long MyGrid::getMyY() const{
    return myY;
}
void MyGrid::setMyY(long y){
    myY = y;
}
vector< vector<long> > MyGrid::getGridElements() const{
    return gridElements;
}
long MyGrid::getNumRows() const{
    return gridElements.size();

}
long MyGrid::getNumCols() const{
	if(gridElements.size() == 0){
		return 0;
	}
    return gridElements[0].size();
}
void MyGrid::zeroOutGrid(){
    //gridElements(getNumRows(), vector<long> (getNumCols(), 0));
    //gridElements.resize(getNumRows(), std::vector<long>( getNumCols(), 0));
    for (long i = 0; i < getNumRows(); i++) { 
        for (long j = 0; j < getNumCols(); j++) { 
            gridElements[i][j] = 0; 
        } 
    } 
}
MyGrid::MyGrid(long x, long y, long length, long width){
    setMyX(x);
    setMyY(y);
    gridElements.resize(length);
    for (long i = 0; i < length; i++)
        gridElements[i].resize(width);
    zeroOutGrid();
}

MyGrid::MyGrid(){
}

bool MyGrid::loadGridFromFile(const string filename) {

    string line;
    string token;
    long static numRows, numCols, i, j;
    string term ;
    ifstream infile;
    infile.open(filename, std::ifstream::in);
	if (! infile) {
    	cout << "Error, file couldn't be opened" << endl; 
    	exit(1); 
	} 
    // uint64_t testlongDgt;
    //istringstream isslongDgt;


//    getline(infile, line);
//    istringstream iss0(line);
//    getline(iss0, token, ' ');
//
//    //if (!isNumber(token.c_str())  ||  stoull(token.c_str()) > ULONG_MAX || stoul(token.c_str()) <= 0) {cout<<"kkkkkkkkkkkkkk"<<token.c_str()<<endl;return false;}
//    myX = stoul(token.c_str());
    infile >> myX;
    cout<<"myX ="<<myX<<endl;

//    getline(iss0, token, ' ');
    //cout<<"2hyyyyyy"<<token.c_str()<<endl;

    //if (!isNumber(token.c_str())  ||  stoull(token.c_str()) > ULONG_MAX || stoul(token.c_str()) <= 0) {cout<<"kkkkkkkkkkkkkk"<<token.c_str()<<endl;return false;}
//    myY = stoul(token.c_str());
    infile >> myY;
    cout<<"myY ="<<myY<<endl;
    //cout<<"hyyyyyy1"<<endl;
//    getline(infile, line);
//    istringstream iss1(line);
//    getline(iss1, token, ' ');
    //if (!isNumber(token.c_str())  ||  stoull(token.c_str()) > ULONG_MAX || stoul(token.c_str()) <= 0) {cout<<"kkkkkkkkkkkkkk"<<token.c_str()<<endl;return false;}
    //  cout<<"hyyyyyy2"<<endl;
    infile >> numRows;
//    numRows = stoul(token.c_str());
    cout<<numRows<<endl;

//    getline(iss1, token, ' ');
//    // if (!isNumber(token.c_str())  ||  stoull(token.c_str()) > ULONG_MAX || stoul(token.c_str()) <= 0) {cout<<"kkkkkkkkkkkkkk"<<token.c_str()<<endl;return false;}
//    numCols = stoul(token.c_str());
    infile>>numCols;
    cout<<numCols<<endl;
    if (numRows <=0 || numCols <=0) return false;
    //zeroOutGrid();
    /*
    while (getline(infile, line)){
        istringstream iss(line);
        vector<long> temp;
        while(iss >> term){
            temp.push_back(stoul(term));
            cout << "aliiiiiiiiiiiiiiiiii"<< term<< endl;

        }
        gridElements.push_back(temp);
        for (long j = 0; j < numCols; j++){
           cout << "CCljj"<<long(temp[j]) << endl;
        }

    }
    */

    for (long i = 0; i < numRows; i++){
//        getline(infile, line);
//        istringstream iss(line);

        vector<long> temp;
        for (long j=0;  j <  numCols; j++){
//            iss >> term;
		long term;
            infile>>term;
            temp.push_back(term);
            cout << "aliiiiiiiiiiiiiiiiii"<< term<< endl;

        }

	cout<<"size of gridEle. " <<gridElements.size()<<endl;
        gridElements.push_back(temp);
	cout<<"size of gridEle." <<gridElements.size()<<endl;
        for (long j = 0; j < numCols; j++){
            cout << "hiiis"<<temp[j] << endl;
            cout << "hiiisLLL"<<gridElements[0][j] << endl;
        }
    }

    for (long i = 0; i < numRows; i++){
        for (long j = 0; j < numCols; j++){
            cout << "alooooo"<<long(gridElements[i][j]) << endl;
        }
        cout << endl;
    }

    for (int i = 0; i < numRows; i++) {
        for (
                auto it = gridElements[i].begin();
                it != gridElements[i].end(); it++)
            cout << *it << " ";
        cout << endl;
    }

    return true;



}

void MyGrid::addGrid(MyGrid const& secGrid) {
	for(int i = 0; i < secGrid.getNumRows(); i++){
		for(int j = 0; j < secGrid.getNumCols(); j++){
			//gridElements[this->getNumRows() - (this->getMyY() - secGrid.getMyY()) - secGrid.getNumRows()+i][secGrid.getMyX() - this->getMyX()+j] += secGrid.gridElements[i][j];
            gridElements[this->getMyY() - secGrid.getMyY()+i][secGrid.getMyX() - this->getMyX()+j] += secGrid.gridElements[i][j];
                   
        }
	}
}



void MyGrid::subGrid(MyGrid const& secGrid) {
	for(int i = 0; i < secGrid.getNumRows(); i++){
		for(int j = 0; j < secGrid.getNumCols(); j++){
			//gridElements[this->getNumRows() - (this->getMyY() - secGrid.getMyY()) - secGrid.getNumRows()+i][secGrid.getMyX() - this->getMyX()+j] -= secGrid.gridElements[i][j];
            gridElements[this->getMyY() - secGrid.getMyY()+i][secGrid.getMyX() - this->getMyX()+j] -= secGrid.gridElements[i][j];

        }
	}
}


MyGrid MyGrid::operator+(MyGrid const& secGrid) const{
	long newX = min(this->getMyX(), secGrid.getMyX());
	long newY = max(this->getMyY(), secGrid.getMyY());
	long length = newY - min(this->getMyY()-this->getNumRows(), secGrid.getMyY() - secGrid.getNumRows());
	long width = max(this->getMyX()+this->getNumCols(), secGrid.getMyX() + secGrid.getNumCols()) - newX;

    fstream outFile("temp.txt", fstream::out);
    outFile << *this << endl;

    MyGrid newGrid(newX, newY, length, width);
	cout <<"newX = " <<newGrid.getMyX()<<endl;
cout <<"newY = " <<newGrid.getMyY()<<endl;
cout <<"nRows = " <<newGrid.getNumRows()<<endl;
cout <<"nCols = " <<newGrid.getNumCols()<<endl;
    for (long i = 0; i < newGrid.getNumRows(); i++){
        for (long j = 0; j < newGrid.getNumCols() ; j++){
            cout << newGrid.gridElements[i][j];
            cout << ' ';
        }
        cout << endl;
    }
	newGrid.addGrid(secGrid);
	cout <<"newX = " <<newGrid.getMyX()<<endl;
cout <<"newY = " <<newGrid.getMyY()<<endl;
cout <<"nRows = " <<newGrid.getNumRows()<<endl;
cout <<"nCols = " <<newGrid.getNumCols()<<endl;
    for (long i = 0; i < newGrid.getNumRows(); i++){
        for (long j = 0; j < newGrid.getNumCols() ; j++){
            cout << newGrid.gridElements[i][j];
            cout << ' ';
        }
        cout << endl;
    }
	newGrid.addGrid(*this);
	cout <<"newX = " <<newGrid.getMyX()<<endl;
cout <<"newY = " <<newGrid.getMyY()<<endl;
cout <<"nRows = " <<newGrid.getNumRows()<<endl;
cout <<"nCols = " <<newGrid.getNumCols()<<endl;
    for (long i = 0; i < newGrid.getNumRows(); i++){
        for (long j = 0; j < newGrid.getNumCols() ; j++){
            cout << newGrid.gridElements[i][j];
            cout << ' ';
        }
        cout << endl;
    }
    //outFile << newGrid << endl;
    //NewGrid.zeroOutGrid();
    //cout <<"NewGrid.gridElements[i][j]"<<NewGrid.gridElements[0][0] <<endl;


    return newGrid;

    //this.myX < secGrid.getMyX() ? NewGrid.setMyX(myX): NewGrid.setMyX(secGrid.getMyX());
    //this.myY > secGrid.getMyY() ? NewGrid.setMyY(myY): NewGrid.setMyY(secGrid.getMyY());

}

MyGrid MyGrid::operator-(MyGrid const& secGrid) const{
    	long newX = min(this->getMyX(), secGrid.getMyX());
	long newY = max(this->getMyY(), secGrid.getMyY());
	long length = newY - min(this->getMyY()-this->getNumRows(), secGrid.getMyY() - secGrid.getNumRows());
	long width = max(this->getMyX()+this->getNumCols(), secGrid.getMyX() + secGrid.getNumCols()) - newX;

    fstream outFile("temp.txt", fstream::out);
    outFile << *this << endl;

    MyGrid newGrid(newX, newY, length, width);
	cout <<"newX = " <<newGrid.getMyX()<<endl;
cout <<"newY = " <<newGrid.getMyY()<<endl;
cout <<"nRows = " <<newGrid.getNumRows()<<endl;
cout <<"nCols = " <<newGrid.getNumCols()<<endl;
    for (long i = 0; i < newGrid.getNumRows(); i++){
        for (long j = 0; j < newGrid.getNumCols() ; j++){
            cout << newGrid.gridElements[i][j];
            cout << ' ';
        }
        cout << endl;
    }
	newGrid.subGrid(secGrid);
	cout <<"newX = " <<newGrid.getMyX()<<endl;
cout <<"newY = " <<newGrid.getMyY()<<endl;
cout <<"nRows = " <<newGrid.getNumRows()<<endl;
cout <<"nCols = " <<newGrid.getNumCols()<<endl;
    for (long i = 0; i < newGrid.getNumRows(); i++){
        for (long j = 0; j < newGrid.getNumCols() ; j++){
            cout << newGrid.gridElements[i][j];
            cout << ' ';
        }
        cout << endl;
    }
	newGrid.addGrid(*this);
	cout <<"newX = " <<newGrid.getMyX()<<endl;
cout <<"newY = " <<newGrid.getMyY()<<endl;
cout <<"nRows = " <<newGrid.getNumRows()<<endl;
cout <<"nCols = " <<newGrid.getNumCols()<<endl;
    for (long i = 0; i < newGrid.getNumRows(); i++){
        for (long j = 0; j < newGrid.getNumCols() ; j++){
            cout << newGrid.gridElements[i][j];
            cout << ' ';
        }
        cout << endl;
    }

    return newGrid;

    //this.myX < secGrid.getMyX() ? NewGrid.setMyX(myX): NewGrid.setMyX(secGrid.getMyX());
    //this.myY > secGrid.getMyY() ? NewGrid.setMyY(myY): NewGrid.setMyY(secGrid.getMyY());

}






MyGrid MyGrid::operator+(long const& value) const{
    //MyGrid* ptr =  const_cast <MyGrid *> (this);
    MyGrid AddGrid(this->getMyX(), this->getMyY(), this->getNumRows(), this->getNumCols() );

    for (long i = 0; i < this->getNumRows(); i++)
        for (long j = 0; j < this->getNumCols() ; j++)
            //ptr->gridElements[i][j] = gridElements[i][j] + value;
            AddGrid.gridElements[i][j] = gridElements[i][j] + value;
    return AddGrid;
    //return *this;
}
MyGrid operator+(long const& lhs, MyGrid const& rhs){
    //MyGrid* ptr =  const_cast <MyGrid *> (this);
    MyGrid AddGrid(11, 27, rhs.getNumRows(), rhs.getNumCols() );
    cout <<"ayyy2"<< endl;
    for (long i = 0; i < rhs.getNumRows(); i++)
        for (long j = 0; j < rhs.getNumCols() ; j++)
            AddGrid.gridElements[i][j] = lhs+rhs.gridElements[i][j];
    //gridElements[i][j] = ptr->gridElements[i][j] + lhs;

    return AddGrid;
}

void MyGrid::deepCopy(MyGrid secGrid){
	this->myX = secGrid.myX;
    this->myY = secGrid.myY;
    for(long i = 0; i < secGrid.getNumRows(); i++){
		vector<long> temp;
		for(long j = 0; j < secGrid.getNumCols(); j++){
			temp.push_back(secGrid.gridElements[i][j]);
            //cout <<"PyyyyyyyyyyyyyyygridElements[ii][jj]"<<gridElements[i][j] <<endl;
		}
		gridElements.push_back(temp);
	}
}


MyGrid& MyGrid::operator+=(MyGrid const& secGrid){
    cout <<"Beh1"<< endl;
    cout << this->getNumRows()<< endl;
	if(this->getNumRows() == 0||this->getNumCols() == 0){
		deepCopy(secGrid);
	} else {
    for (long i = 0; i < this->getNumRows(); i++){
        cout <<"Beh2"<< endl;

        for (long j = 0; j < this->getNumCols() ; j++){
            cout <<"gridElements[ii][jj]"<<gridElements[i][j] <<endl;

            gridElements[i][j] = gridElements[i][j] + secGrid.gridElements[i][j];
            cout <<"gridElements[ii][jj]"<<gridElements[i][j] <<endl;
            cout <<"secGrid.gridElements[ii][jj]"<<secGrid.gridElements[i][j] <<endl;
        }
      }
    }
    return *this;
}


MyGrid& MyGrid::operator++(){ // Prefix
    for (long i = 0; i < this->getNumRows(); i++)
        for (long j = 0; j < this->getNumCols() ; j++)
            gridElements[i][j] = gridElements[i][j]+1;
    return *this;

}
MyGrid MyGrid::operator++(int){ // Postfix
    MyGrid temp = *this;  
    for (long i = 0; i < this->getNumRows(); i++)
        for (long j = 0; j < this->getNumCols() ; j++)
            gridElements[i][j] = gridElements[i][j]+1;

    return temp;

}

MyGrid& MyGrid::operator--(){ // Prefix
    for (long i = 0; i < this->getNumRows(); i++)
        for (long j = 0; j < this->getNumCols() ; j++)
            gridElements[i][j] = gridElements[i][j]-1 ;
    return *this;


}
MyGrid MyGrid::operator--(int){ // Postfix
    MyGrid temp = *this;  
    for (long i = 0; i < this->getNumRows(); i++)
        for (long j = 0; j < this->getNumCols() ; j++)
            gridElements[i][j] = gridElements[i][j] -1;

    return temp;

}

MyGrid MyGrid::operator-() const{
    cout<<"Ajab0"<<endl;
    cout<<getNumRows()<<endl;
    cout<<this->getNumCols()<<endl;
    MyGrid MulNegGrid(this->getMyX(), this->getMyY(), this->getNumRows(), this->getNumCols());
    //MyGrid MulNegGrid;
    cout<<"Ajab1"<<endl;
    for (long i = 0; i < this->getNumRows(); i++)
        for (long j = 0; j < this->getNumCols(); j++){
            cout<<"Ajab00"<<endl;
            cout<<"gridElements[i][j]"<<-1*gridElements[i][j]<<endl;

            MulNegGrid.gridElements[i][j] = -1 * gridElements[i][j];
            cout<<"MulNegGrid->gridElements[i][j]"<<MulNegGrid.gridElements[i][j]<<endl;

            cout<<"Ajab2"<<endl;
        }
    return MulNegGrid;
}

bool MyGrid::operator==(MyGrid const& secGrid) const{

    if (getNumRows()== secGrid.getNumRows() &&  getNumCols()== secGrid.getNumCols() && this->myX == secGrid.myX &&  this->myY == secGrid.myY){
        for (long i = 0; i < this->getNumRows(); i++)
            for (long j = 0; j < this->getNumCols() ; j++)
                if (gridElements[i][j] != secGrid.gridElements[i][j])
                    return false;
        return true;
    }
    else{
        return false;
    }
}

fstream& operator<<(fstream& os, const MyGrid& gridIn){
    os << gridIn.getMyX();
	cout<< gridIn.getMyX()<<endl;
    os << ' ';
    os << gridIn.getMyY();
cout<< gridIn.getMyY()<<endl;
    os << '\n';
    os << gridIn.getNumRows();
cout<< gridIn.getNumRows()<<endl;
    os << ' ';
    os << gridIn.getNumCols();
cout<< gridIn.getNumCols()<<endl;
    os << '\n';
    for (long i = 0; i < gridIn.getNumRows(); i++){
        for (long j = 0; j < gridIn.getNumCols() ; j++){
            os << gridIn.gridElements[i][j];
            os << ' ';
        }
        os << '\n';
    }
    return os;
}






int main(int argc, char* argv[])
{
    fstream outFile("Lab2Output.txt", fstream::out);

    vector<MyGrid> vecGrids;
    MyGrid tmpGrid;

    vecGrids.resize(argc);
    for (int ii = 1; ii < argc; ii++)
    {
        if (!vecGrids[ii-1].loadGridFromFile(argv[ii]))
        {
            outFile << "Failed to load file: " << argv[ii] << endl;
        }
    }

    if (argc >= 3)
    {
        tmpGrid += vecGrids[1];
        outFile << tmpGrid << endl;

        tmpGrid = vecGrids[0] + vecGrids[1];
        outFile << tmpGrid << endl;

        tmpGrid = vecGrids[0] - vecGrids[1];
        outFile << tmpGrid << endl;

        tmpGrid = vecGrids[0] + 10;
        outFile << tmpGrid << endl;

        tmpGrid = 10 + vecGrids[1] + 10;
        outFile << tmpGrid << endl;

        outFile << tmpGrid++ << endl;
        outFile << ++tmpGrid << endl;

        outFile << tmpGrid-- << endl;
        outFile << --tmpGrid << endl;


        outFile << -tmpGrid << endl;

        if (vecGrids[0] == vecGrids[1])
        {
            outFile << "The first two grids are equal" << endl;
        }
        else
        {
            outFile << "The first two grids are not equal" << endl;
        }

        outFile << "The first grid has " << vecGrids[0].getNumRows() << " rows and " << vecGrids[0].getNumCols() << " cols." << endl;

        vecGrids[0].zeroOutGrid();
        outFile << vecGrids[0] << endl;

    }

    outFile.close();

}