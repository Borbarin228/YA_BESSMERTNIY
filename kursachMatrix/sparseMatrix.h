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
	SparseMatrix():row(*new std::vector<int>), column(*new std::vector<int>), value(*new std::vector<double>), rowSize(0), columnSize(0) {};
	~SparseMatrix() { delete& row; delete& column; delete& value;};
	
	void transform(std::vector<std::vector<double>>);
		
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
	friend std::ostream& operator<<(std::ostream& stream, const SparseMatrix&);
private:
	void compressRow(int);
	void compressColumn(int);
};

#endif