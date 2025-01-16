#include "sparseMatrix.h"

int main(){
	std::vector<std::vector<double>> matrix;
	matrix.push_back(*new std::vector<double>{ 1, 0, 0, 0, 0 });
	matrix.push_back(*new std::vector<double>{ 1, 0, 0, 1, 0 });
	matrix.push_back(*new std::vector<double>{ 0, 1, 1, 0, 1 });
	matrix.push_back(*new std::vector<double>{ 0, 0, 0, 0, 1 });
	matrix.push_back(*new std::vector<double>{ 1, 0, 0, 0, 1 });

	SparseMatrix* sparceMatrix = new SparseMatrix();
	sparceMatrix->transform(matrix);
	std::cout << *sparceMatrix;

	return 0;
}