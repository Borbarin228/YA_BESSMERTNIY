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

int SparseMatrix::findIndex(int r, int c) {
	for (int i = 0;i < this->row.size();i++) {
		if (this->column[i] == c && this->row[i] == r) {
			return i;
		}
	}
	return -1;
}

SparseMatrix SparseMatrix::plusM(SparseMatrix secOperand) {
	SparseMatrix* sparseMatrix = new SparseMatrix();
	if ((this->columnSize == secOperand.columnSize) && (this->rowSize == secOperand.rowSize)) {
		
		for (int i = 0;i < this->columnSize;i++) {
			
			for (int j = 0;j < this->columnSize;j++) {
				int result = 0;
				int leftOpIndex = this->findIndex(i, j), rightOpIndex = secOperand.findIndex(i, j);
				if (leftOpIndex > -1 && rightOpIndex> -1) {
					result = this->value[leftOpIndex]+secOperand.value[rightOpIndex];
					sparseMatrix->row.push_back(i);
					sparseMatrix->column.push_back(j);
					sparseMatrix->value.push_back(result);
				}
				else if (leftOpIndex == -1 && rightOpIndex > -1) {
					result = secOperand.value[rightOpIndex];
					sparseMatrix->row.push_back(i);
					sparseMatrix->column.push_back(j);
					sparseMatrix->value.push_back(result);
				}				
				else if (leftOpIndex > -1 && rightOpIndex == -1) {
					result = this->value[leftOpIndex];
					sparseMatrix->row.push_back(i);
					sparseMatrix->column.push_back(j);
					sparseMatrix->value.push_back(result);
				}
			}
		}

		return *sparseMatrix;
	}
	else {
		throw new std::exception("incorrect operation execution");
	}
}

SparseMatrix SparseMatrix::multiplM(SparseMatrix secOperand) {


	std::vector<std::vector<double>> result;
	if (this->columnSize != secOperand.rowSize) {
		throw new std::exception("incorrect row or column length for  operation");
	}
	for (int i = 0; i < this->rowSize;i++) {
		for (int j = 0; j < secOperand.columnSize; j++) {
			result[j].push_back(multiplCells(this->getRow(i), secOperand.getRow(j)));
		}
	}
	SparseMatrix tmp = SparseMatrix();
	tmp.transform(result);
	return tmp;

}

SparseMatrix SparseMatrix::minusM(SparseMatrix secOperand) {

	SparseMatrix* sparseMatrix = new SparseMatrix();
	if ((this->columnSize == secOperand.columnSize) && (this->rowSize == secOperand.rowSize)) {

		for (int i = 0;i < this->columnSize;i++) {

			for (int j = 0;j < this->columnSize;j++) {
				int result = 0;
				int leftOpIndex = this->findIndex(i, j), rightOpIndex = secOperand.findIndex(i, j);
				if (leftOpIndex > -1 && rightOpIndex > -1) {
					result = this->value[leftOpIndex] - secOperand.value[rightOpIndex];
					sparseMatrix->row.push_back(i);
					sparseMatrix->column.push_back(j);
					sparseMatrix->value.push_back(result);
				}
				else if (leftOpIndex == -1 && rightOpIndex > -1) {
					result = -secOperand.value[rightOpIndex];
					sparseMatrix->row.push_back(i);
					sparseMatrix->column.push_back(j);
					sparseMatrix->value.push_back(result);
				}
				else if (leftOpIndex > -1 && rightOpIndex == -1) {
					result = this->value[leftOpIndex];
					sparseMatrix->row.push_back(i);
					sparseMatrix->column.push_back(j);
					sparseMatrix->value.push_back(result);
				}
			}
		}

		return *sparseMatrix;
	}
	else {
		throw new std::exception("incorrect operation execution");
	}

}

SparseMatrix SparseMatrix::plusV(double x) {
	SparseMatrix sparseMatrix = SparseMatrix();
	for (int i = 0;i < value.size();i++) {
		  sparseMatrix.value.push_back(value[i] + x);
		  sparseMatrix.row.push_back(row[i]);
		  sparseMatrix.column.push_back(column[i]);
	}
	return  sparseMatrix;
}

SparseMatrix SparseMatrix::multiplV(double x) {
	SparseMatrix sparseMatrix = SparseMatrix();
	for (int i = 0;i < value.size();i++) {
		sparseMatrix.value.push_back(value[i] * x);
		sparseMatrix.row.push_back(row[i]);
		sparseMatrix.column.push_back(column[i]);
	}
	return  sparseMatrix;
}

SparseMatrix SparseMatrix::minusV(double x) {
	SparseMatrix sparseMatrix = SparseMatrix();
	for (int i = 0;i < value.size();i++) {
		sparseMatrix.value.push_back(value[i] - x);
		sparseMatrix.row.push_back(row[i]);
		sparseMatrix.column.push_back(column[i]);
	}
	return  sparseMatrix;
}

SparseMatrix SparseMatrix::genIdentityMatrix(int size) {
	SparseMatrix sparseMatrix = SparseMatrix();
	for (int i = 0;i < size;i++) {
		sparseMatrix.value.push_back(1);
		sparseMatrix.row.push_back(i);
		sparseMatrix.column.push_back(i);
	}
	sparseMatrix.columnSize = size;
	sparseMatrix.rowSize = size;
	return sparseMatrix;
}

SparseMatrix SparseMatrix::genZeroMatrix(int size) {
	SparseMatrix sparseMatrix = SparseMatrix();
	sparseMatrix.columnSize = size;
	sparseMatrix.rowSize = size;
	return sparseMatrix;
}

void SparseMatrix::delRow(int rowNum) {
	if (rowNum >= this->rowSize) {
		throw new std::exception("out of range");
	}
	for (int i = 0; i <row.size();i++) {
		if (this->row[i] == rowNum) {
			this->value.erase(this->value.begin() + i);
			this->row.erase(this->row.begin() + i);
			this->column.erase(this->column.begin() + i);
		}
	}
}

void SparseMatrix::delColumn(int colNum) {
	if (colNum >= this->columnSize) {
		throw new std::exception("out of range");
	}
	for (int i = 0; i < row.size();i++) {
		if (this->column[i] == colNum) {
			this->value.erase(this->value.begin() + i);
			this->row.erase(this->row.begin() + i);
			this->column.erase(this->column.begin() + i);
		}
	}
}

void SparseMatrix::newRow(std::vector<double> newRow, int indx = 0) {
	if (indx >= rowSize || newRow.size() >= columnSize) {
		throw new std::exception("out of range");
	}
	delRow(indx);
	for (int i = 0;i < row.size();i++) {
		for (int j = 0; j < newRow.size();j++) {
			if (newRow[j] != 0) {
				if (row[i] == indx) {
					if (findIndex(indx, i) == -1) {
						row.push_back(indx);
						column.push_back(j);
						value.push_back(newRow[i]);
					}
					else {
						column[i] = j;
						value[i] = newRow[j];
					}
				}
				else {
					break;
				}
			}
		}
					
	}
}

void SparseMatrix::newColumn(std::vector<double> newColumn, int indx = 0) {
	if (indx >= columnSize || newColumn.size() >= columnSize) {
		throw new std::exception("out of range");
	}
	delColumn(indx);
	for (int i = 0;i < column.size();i++) {
		for (int j = 0; j < newColumn.size();j++) {
			if (newColumn[j] != 0) {
				if (column[i] == indx) {
					if (findIndex(i, indx) == -1) {
						row.push_back(j);
						column.push_back(indx);
						value.push_back(newColumn[i]);
					}
					else {
						row[i] = j;
						value[i] = newColumn[j];
					}
				}
				else {
					break;
				}
			}
		}

	}
}

void SparseMatrix::changeRow(int fstRow, int scndRow) {
	if (fstRow >= rowSize || scndRow >= rowSize) {
		throw new std::exception("out of range");
	}
	if (fstRow == scndRow) {
		return;
	}

	std::vector<double> row1, row2;
	row1 = getRow(fstRow);
	row2 = getRow(scndRow);
	newRow(row1, fstRow);
	newRow(row2, scndRow);

}

void SparseMatrix::changeColumn(int fstColumn, int scndColumn) {
	if (fstColumn >= rowSize || scndColumn >= columnSize) {
		throw new std::exception("out of range");
	}
	if (fstColumn == scndColumn) {
		return;
	}

	std::vector<double> row1, row2;
	row1 = getColumn(fstColumn);
	row2 = getColumn(scndColumn);
	newRow(row1, fstColumn);
	newRow(row2, scndColumn);
}


int SparseMatrix::maxRow() {
	int max = 0;
	for (int i = 0; i < rowSize;i++) {
		if (row[i] > max)
			max = row[i];
	}
	return max;
}

int SparseMatrix::minRow() {
	int min = row[0];
	for (int i = 0; i < rowSize;i++) {
		if (row[i] < min)
			min = row[i];
	}
	return min;
}

int SparseMatrix::maxColumn() {
	int max = 0;
	for (int i = 0; i < columnSize;i++) {
		if (column[i] > max)
			max = column[i];
	}
	return max;
}

int SparseMatrix::minColumn() {
	int min = column[0];
	for (int i = 0; i < columnSize;i++) {
		if (column[i] < min)
			min = column[i];
	}
	return min;
}

double SparseMatrix::getValue(int r, int c) {
	int indx = findIndex(r, c);
	if (r>this->rowSize || c>this->columnSize ) {
		throw new std::exception("out of range");
	}
	else if (indx == -1) {
		return 0;
	}
	else {
		return this->value[indx];
	}

}

std::vector<double> SparseMatrix::getRow(int indx) {
	std::vector<double> result;
	for (int i = 0; i < row.size(); i++) {
		int tmp = findIndex(indx, i);
		if (tmp == -1) {
			result.push_back(0);
		}
		else {
			result.push_back(this->value[tmp]);
		}
	}
	return result;
}
std::vector<double> SparseMatrix::getColumn(int indx) {
	std::vector<double> result;
	for (int i = 0; i < column.size(); i++) {
		int tmp = findIndex(i, indx);
		if (tmp == -1) {
			result.push_back(0);
		}
		else {
			result.push_back(this->value[tmp]);
		}
	}
	return result;
}

double SparseMatrix::multiplCells(std::vector<double> row, std::vector<double> column) {
	double result = 0;
	for (int i = 0;i < row.size(); i++) {
		result += row[i] * column[i];
	}
	return result;
}