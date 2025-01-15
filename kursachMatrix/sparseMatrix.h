#ifndef sparseMatrix_H
#define sparceMatrix_H

#include <iostream>
#include <vector>

class SparseMatrix {
private:
	std::vector<int> row;
	std::vector<int> column;
	std::vector<double> value;
	int rowSize;
	int columnSize;
public:
	SparseMatrix();
	~SparseMatrix();
	
	SparseMatrix transform(std::vector<std::vector<double>>);
	//input это будет перегрузка оператора()
	//вывод перегрузкой <<
	void setRowSize(int);
	void setColumnSize(int);

	SparseMatrix plusM(SparseMatrix);
	SparseMatrix multiplM(SparseMatrix);
	SparseMatrix minusM(SparseMatrix);

	SparseMatrix plusV(SparseMatrix);
	SparseMatrix multiplV(SparseMatrix);
	SparseMatrix minusV(SparseMatrix);

	SparseMatrix genIdentityMatrix(int, int);
	SparseMatrix genZeroMatrix(int, int);
	void delRow(int);
	void delColumn(int);
	void newRow(std::vector<double>);
	void newColumn(std::vector<double>);
	void changeRow(int, int);
	void changeColumn(int, int);
	int maxRow();
	int minRow();
	int maxColumn();
	int minColumn();
};

#endif