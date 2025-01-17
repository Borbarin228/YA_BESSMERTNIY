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

	SparseMatrix(int x = 0) : row(*new std::vector<int>), column(*new std::vector<int>), value(*new std::vector<double>), rowSize(x), columnSize(x) {};
	~SparseMatrix() { delete& row; delete& column; delete& value;};
	
	void transform(std::vector<std::vector<double>>);
		
	void setRowSize(int);
	void setColumnSize(int);

	SparseMatrix* plusM(SparseMatrix*);
	SparseMatrix* multiplM(SparseMatrix*);
	SparseMatrix* minusM(SparseMatrix*);

	SparseMatrix* plusV(double);
	SparseMatrix* multiplV(double);
	SparseMatrix* minusV(double);

	SparseMatrix* genIdentityMatrix(int);
	void delRow(int);
	void delColumn(int);
	void newRow(std::vector<double>, int);
	void newColumn(std::vector<double>, int);
	void changeRow(int, int);
	void changeColumn(int, int);
	int maxRow();
	int minRow();
	int maxColumn();
	int minColumn();
	friend std::ostream& operator<<(std::ostream& stream, const SparseMatrix&);
	double getValue(int, int);
	std::vector<double> getRow(int);
	std::vector<double> getColumn(int);
private:
	void compressRow(int);
	void compressColumn(int);
	int findIndex(int, int);
	double multiplCells(std::vector<double>, std::vector<double>);
};

#endif