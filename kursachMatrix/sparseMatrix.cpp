#include "sparseMatrix.h"

std::ostream& operator<<(std::ostream& stream, const SparseMatrix& matrix) {
	std::cout << "row:\tcolumn:\tvalue:" << std::endl;
	for (int i = 0;i < matrix.value.size();i++) {
		std::cout << matrix.row[i]+1 << "\t" << matrix.column[i]+1 << "\t" << matrix.value[i] << std::endl;
	}
	std::cout << "\tsize: " << matrix.rowSize << "x" << matrix.columnSize<<std::endl;
	return stream;
}

void SparseMatrix::compressRow(int newSize) {
	for (int i = this->value.size()-1; i >=0 ;i--) {
		if (this->row[i] > newSize-1) {
			this->value.erase(this->value.begin() + i);
			this->row.erase(this->row.begin() + i);
			this->column.erase(this->column.begin() + i);
		}
	}
}

void SparseMatrix::compressColumn(int newSize) {
	for (int i = this->value.size() - 1; i >= 0;i--) {
		if (this->column[i] > newSize-1) {
			this->value.erase(this->value.begin() + i);
			this->row.erase(this->row.begin() + i);
			this->column.erase(this->column.begin() + i);
		}
	}
}


void SparseMatrix::transform(std::vector<std::vector<double>> nonSparseMatrix) {
	int maxColumnNum = 0;
	for (int i = 0; i < nonSparseMatrix.size();i++) {
		for (int j = 0; j < nonSparseMatrix[i].size();j++) {
			if (maxColumnNum < nonSparseMatrix[i].size())
				maxColumnNum = nonSparseMatrix[i].size();
			if (nonSparseMatrix[i][j] != 0) {
				this->value.push_back(nonSparseMatrix[i][j]);
				this->column.push_back(j);
				this->row.push_back(i);
			}

		}
	}
	this->rowSize = nonSparseMatrix.size();
	this->columnSize = maxColumnNum;
}

void SparseMatrix::setRowSize(int newSize){
	if (this->rowSize >= newSize) {
		this->compressRow(newSize);
	}

	this->rowSize = newSize;

}

void SparseMatrix::setColumnSize(int newSize) {
	if (this->columnSize >= newSize) {
		this->compressColumn(newSize);

	}
	this->columnSize = newSize;

}

//SparseMatrix SparseMatrix::plusM(SparseMatrix) {}
//
//SparseMatrix SparseMatrix::multiplM(SparseMatrix) {}
//
//SparseMatrix SparseMatrix::minusM(SparseMatrix) {}
//
//SparseMatrix SparseMatrix::plusV(SparseMatrix) {}
//
//SparseMatrix SparseMatrix::multiplV(SparseMatrix) {}
//
//SparseMatrix SparseMatrix::minusV(SparseMatrix) {}
//
//SparseMatrix SparseMatrix::genIdentityMatrix(int, int) {}
//
//SparseMatrix SparseMatrix::genZeroMatrix(int, int) {}
//
//void SparseMatrix::delRow(int) {}
//
//void SparseMatrix::delColumn(int) {}
//
//void SparseMatrix::newRow(std::vector<double>) {}
//
//void SparseMatrix::newColumn(std::vector<double>) {}
//
//void SparseMatrix::changeRow(int, int) {}
//
//void SparseMatrix::changeColumn(int, int) {}
//
//int SparseMatrix::maxRow() {}
//
//int SparseMatrix::minRow() {}
//
//int SparseMatrix::maxColumn() {}
//
//int SparseMatrix::minColumn() {}
