#include "sparseMatrix.h"

int main(){
	std::vector<std::vector<double>> matrix;
	matrix.push_back(*new std::vector<double>{ 2, 0, 0, 0, 0 });
	matrix.push_back(*new std::vector<double>{ 0, 4, 0, 0, 0 });
	matrix.push_back(*new std::vector<double>{ 0, 0, 3, 0, 0 });
	matrix.push_back(*new std::vector<double>{ 0, 0, 0, 0, 0 });
	matrix.push_back(*new std::vector<double>{ 0, 0, 0, 0, 0 });

	SparseMatrix* sparseMatrix1 = new SparseMatrix();
	SparseMatrix* sparseMatrix2 = new SparseMatrix();

	sparseMatrix1->transform(matrix);
	sparseMatrix1->setRowSize(2);
	sparseMatrix1->setColumnSize(2);
	std::cout <<"simple matrix\n" << *sparseMatrix1;
	sparseMatrix2->transform(matrix);
	sparseMatrix2->setRowSize(2);
	sparseMatrix2->setColumnSize(2);
	std::cout <<"simple matrix\n" << *sparseMatrix2;
	auto result = sparseMatrix1->multiplM(sparseMatrix2);
	std::cout << "multiplM\n" << *result;
	result = sparseMatrix1->minusM(sparseMatrix2);
	std::cout << "minusM\n" << *result;
	result = sparseMatrix1->plusM(sparseMatrix2);
	std::cout << "plusM\n" << *result;
	result = sparseMatrix1->multiplV(3);
	std::cout << "multiplV\n" << *result;
	result = sparseMatrix1->minusV(4);
	std::cout << "minusV\n" << *result;
	result = sparseMatrix1->plusV(3);
	std::cout << "plusV\n" << *result;
	std::cout << "zero Matrix\n" << *(new SparseMatrix(5));
	result = result->genIdentityMatrix(5);
	std::cout << "Identity Matrix\n" << *result;
	sparseMatrix1->setRowSize(4);
	sparseMatrix1->setColumnSize(5);
	std::cout << *sparseMatrix1;
	std::vector<double> newRow = *new std::vector<double>{ 0, 4, 5, 0};
	sparseMatrix1->newRow(newRow, 3);
	std::cout << *sparseMatrix1;
	std::vector<double> newColumn = *new std::vector<double>{ 0, 4, 1, 0 };
	sparseMatrix1->newColumn(newColumn, 1);
	std::cout << *sparseMatrix1;
	sparseMatrix2->setRowSize(4);
	sparseMatrix2->setColumnSize(5);
	std::cout << *sparseMatrix2;
	result = sparseMatrix1->minusM(sparseMatrix2);
	std::cout << "minusM\n" << *result;
	std::cout << *sparseMatrix1;
	sparseMatrix1->delRow(3);
	std::cout << *sparseMatrix1;
	std::cout << "delete row\n" << *sparseMatrix1;
	std::cout<<"min Column "<< sparseMatrix1->minColumn() << std::endl;
	std::cout<<"max Column "<< sparseMatrix1->maxColumn() << std::endl;
	std::cout<<"min row "<< sparseMatrix1->minRow() << std::endl;
	std::cout<<"max row "<< sparseMatrix1->maxRow() << std::endl;
	std::cout << *sparseMatrix1;
	sparseMatrix1->changeColumn(0, 1);
	std::cout << *sparseMatrix1;
	return 0;
}