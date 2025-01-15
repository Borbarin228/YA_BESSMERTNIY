#include "sparseMatrix.h"

int main(){
	std::vector<std::vector<double>> matrix;
	matrix.push_back(*new std::vector<double>{ 0.1, 0, 0.2, 0, 0 });
	matrix.push_back(*new std::vector<double>{ 0, 0, 0.3, 0, 0 });
	matrix.push_back(*new std::vector<double>{ 0, 3.4, 0, 0, 0 });
	matrix.push_back(*new std::vector<double>{ 0, 0, 0, 0, 0 });
	matrix.push_back(*new std::vector<double>{ 0, 0, 0, 5.3, 0 });

	SparseMatrix* sparceMatrix = new SparseMatrix();
	sparceMatrix->transform(matrix);
	std::cout << *sparceMatrix;
	sparceMatrix->setRowSize(3);
	std::cout << *sparceMatrix;

	return 0;
}