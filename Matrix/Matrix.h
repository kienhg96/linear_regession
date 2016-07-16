using namespace std;
int row, col, Row, Col;
double Coefficient;
//Input Ma
//Copy Pointer to Matrix
void CopyPointer(double(*Pointer)[9], double Matrix[9][9], int Row, int Col)
{
	for (row = 1; row <= Row; row++)
	for (col = 1; col <= Col; col++)
		Matrix[row][col] = Pointer[row][col];
}
//Copy Matrix to Matrix
void CopyMatrix(double MatrixInput[9][9], double MatrixTarget[9][9], int Row, int Col)
{
	for (row = 1; row <= Row; row++)
	for (col = 1; col <= Col; col++)
		MatrixTarget[row][col] = MatrixInput[row][col];
}
//Transpose of Matrix
double MatrixTran[9][9];
double(*(Transpose)(double MatrixInput[9][9], int Row, int Col))[9]
{
	for (row = 1; row <= Row; row++)
	for (col = 1; col <= Col; col++)
		MatrixTran[col][row] = MatrixInput[row][col];
	return MatrixTran;
}
//Matrix Addition
double MatrixAdd[9][9];
double(*(Addition)(double MatrixA[9][9], double MatrixB[9][9], int Row, int Col))[9]
{
	for (row = 1; row <= Row; row++)
	for (col = 1; col <= Col; col++)
		MatrixAdd[row][col] = MatrixA[row][col] + MatrixB[row][col];
	return MatrixAdd;
}
//Matrix Subtraction
double MatrixSub[9][9];
double(*(Subtraction)(double MatrixA[9][9], double MatrixB[9][9], int Row, int Col))[9]
{
	for (row = 1; row <= Row; row++)
	for (col = 1; col <= Col; col++)
		MatrixSub[row][col] = MatrixA[row][col] - MatrixB[row][col];
	return MatrixSub;
}
//Matrix Multiplication
int mRow, nCol, pCol, kcol;
double MatrixMult[9][9];
double(*(Multiplication)(double MatrixA[9][9], double MatrixB[9][9], int mRow, int nCol, int pCol))[9]
{
	for (row = 1; row <= mRow; row++)
	for (col = 1; col <= pCol; col++)
	{
		MatrixMult[row][col] = 0.0;
		for (kcol = 1; kcol <= nCol; kcol++)
			MatrixMult[row][col] += MatrixA[row][kcol] * MatrixB[kcol][col];
	}
	return MatrixMult;
}
//Interchange Two Rows
double RowTemp[9][9];
double MatrixInter[9][9];
double(*(InterchangeRow)(double MatrixInput[9][9], int Row, int Col, int iRow, int jRow))[9]
{
	CopyMatrix(MatrixInput, MatrixInter, Row, Col);
	for (col = 1; col <= Col; col++)
	{
		RowTemp[iRow][col] = MatrixInter[iRow][col];
		MatrixInter[iRow][col] = MatrixInter[jRow][col];
		MatrixInter[jRow][col] = RowTemp[iRow][col];
	}
	return MatrixInter;
}
//Pivote Downward
double MatrixDown[9][9];
double(*(PivoteDown)(double MatrixInput[9][9], int Row, int Col, int tRow, int tCol))[9]
{
	CopyMatrix(MatrixInput, MatrixDown, Row, Col);
	Coefficient = MatrixDown[tRow][tCol];
	if (Coefficient != 1.0)
	for (col = 1; col <= Col; col++)
		MatrixDown[tRow][col] /= Coefficient;
	if (tRow < Row)
	for (row = tRow + 1; row <= Row; row++)
	{
		Coefficient = MatrixDown[row][tCol];
		for (col = 1; col <= Col; col++)
			MatrixDown[row][col] -= Coefficient*MatrixDown[tRow][col];
	}
	return MatrixDown;
}
//Pivote Upward
double MatrixUp[9][9];
double(*(PivoteUp)(double MatrixInput[9][9], int Row, int Col, int tRow, int tCol))[9]
{
	CopyMatrix(MatrixInput, MatrixUp, Row, Col);
	Coefficient = MatrixUp[tRow][tCol];
	if (Coefficient != 1.0)
	for (col = 1; col <= Col; col++)
		MatrixUp[tRow][col] /= Coefficient;
	if (tRow > 1)
	for (row = tRow - 1; row >= 1; row--)
	{
		Coefficient = MatrixUp[row][tCol];
		for (col = 1; col <= Col; col++)
			MatrixUp[row][col] -= Coefficient*MatrixUp[tRow][col];
	}
	return MatrixUp;
}
//Pivote in Determinant
double MatrixPiv[9][9];
double(*(Pivote)(double MatrixInput[9][9], int Dim, int pTarget))[9]
{
	CopyMatrix(MatrixInput, MatrixPiv, Dim, Dim);
	for (row = pTarget + 1; row <= Dim; row++)
	{
		Coefficient = MatrixPiv[row][pTarget] / MatrixPiv[pTarget][pTarget];
		for (col = 1; col <= Dim; col++)
		{
			MatrixPiv[row][col] -= Coefficient*MatrixPiv[pTarget][col];
		}
	}
	return MatrixPiv;
}
//Determinant of Square Matrix
int dCounter, dRow;
double Det;
double MatrixDet[9][9];
double Determinant(double MatrixInput[9][9], int Dim)
{
	CopyMatrix(MatrixInput, MatrixDet, Dim, Dim);
	Det = 1.0;
	if (Dim > 1)
	{
		for (dRow = 1; dRow < Dim; dRow++)
		{
			dCounter = dRow;
			while ((MatrixDet[dRow][dRow] == 0.0)&(dCounter <= Dim))
			{
				dCounter++;
				Det *= -1.0;
				CopyPointer(InterchangeRow(MatrixDet, Dim, Dim, dRow, dCounter), MatrixDet, Dim, Dim);
			}
			if (MatrixDet[dRow][dRow] == 0)
			{
				Det = 0.0;
				break;
			}
			else
			{
				Det *= MatrixDet[dRow][dRow];
				CopyPointer(Pivote(MatrixDet, Dim, dRow), MatrixDet, Dim, Dim);
			}
		}
		Det *= MatrixDet[Dim][Dim];
	}
	else Det = MatrixDet[1][1];
	return Det;
}
//Matrix Identity
double MatrixIdent[9][9];
double(*(Identity)(int Dim))[9]
{
	for (row = 1; row <= Dim; row++)
	for (col = 1; col <= Dim; col++)
	if (row == col)
		MatrixIdent[row][col] = 1.0;
	else
		MatrixIdent[row][col] = 0.0;
	return MatrixIdent;
}
//Join Matrix to be Augmented Matrix
double MatrixJoin[9][9];
double(*(JoinMatrix)(double MatrixA[9][9], double MatrixB[9][9], int Row, int ColA, int ColB))[9]
{
	Col = ColA + ColB;
	for (row = 1; row <= Row; row++)
	for (col = 1; col <= Col; col++)
	if (col <= ColA)
		MatrixJoin[row][col] = MatrixA[row][col];
	else
		MatrixJoin[row][col] = MatrixB[row][col - ColA];
	return MatrixJoin;
}
//Inverse of Matrix
double(*Pointer)[9];
double IdentMatrix[9][9];
int Counter;
double MatrixAug[9][9];
double MatrixInv[9][9];
double(*(Inverse)(double MatrixInput[9][9], int Dim))[9]
{
	Row = Dim;
	Col = Dim + Dim;
	Pointer = Identity(Dim);
	CopyPointer(Pointer, IdentMatrix, Dim, Dim);
	Pointer = JoinMatrix(MatrixInput, IdentMatrix, Dim, Dim, Dim);
	CopyPointer(Pointer, MatrixAug, Row, Col);
	for (Counter = 1; Counter <= Dim; Counter++)
	{
		Pointer = PivoteDown(MatrixAug, Row, Col, Counter, Counter);
		CopyPointer(Pointer, MatrixAug, Row, Col);
	}
	for (Counter = Dim; Counter > 1; Counter--)
	{
		Pointer = PivoteUp(MatrixAug, Row, Col, Counter, Counter);
		CopyPointer(Pointer, MatrixAug, Row, Col);
	}
	for (row = 1; row <= Dim; row++)
	for (col = 1; col <= Dim; col++)
		MatrixInv[row][col] = MatrixAug[row][col + Dim];
	return MatrixInv;
}
//Gauss-Jordan Elemination
double MatrixGJ[9][9];
double VectorGJ[9][9];
double(*(GaussJordan)(double MatrixInput[9][9], double VectorInput[9][9], int Dim))[9]
{
	Row = Dim;
	Col = Dim + 1;
	Pointer = JoinMatrix(MatrixInput, VectorInput, Dim, Dim, 1);
	CopyPointer(Pointer, MatrixGJ, Row, Col);
	for (Counter = 1; Counter <= Dim; Counter++)
	{
		Pointer = PivoteDown(MatrixGJ, Row, Col, Counter, Counter);
		CopyPointer(Pointer, MatrixGJ, Row, Col);
	}
	for (Counter = Dim; Counter > 1; Counter--)
	{
		Pointer = PivoteUp(MatrixGJ, Row, Col, Counter, Counter);
		CopyPointer(Pointer, MatrixGJ, Row, Col);
	}
	for (row = 1; row <= Dim; row++)
	for (col = 1; col <= 1; col++)
		VectorGJ[row][col] = MatrixGJ[row][col + Dim];
	return VectorGJ;
}
//Generalized Gauss-Jordan Elemination
double MatrixGGJ[9][9];
double VectorGGJ[9][9];
double(*(GeneralizedGaussJordan)(double MatrixInput[9][9], double VectorInput[9][9], int Dim, int vCol))[9]
{
	Row = Dim;
	Col = Dim + vCol;
	Pointer = JoinMatrix(MatrixInput, VectorInput, Dim, Dim, vCol);
	CopyPointer(Pointer, MatrixGGJ, Row, Col);
	for (Counter = 1; Counter <= Dim; Counter++)
	{
		Pointer = PivoteDown(MatrixGGJ, Row, Col, Counter, Counter);
		CopyPointer(Pointer, MatrixGGJ, Row, Col);
	}
	for (Counter = Dim; Counter > 1; Counter--)
	{
		Pointer = PivoteUp(MatrixGGJ, Row, Col, Counter, Counter);
		CopyPointer(Pointer, MatrixGGJ, Row, Col);
	}
	for (row = 1; row <= Row; row++)
	for (col = 1; col <= vCol; col++)
		VectorGGJ[row][col] = MatrixGGJ[row][col + Dim];
	return VectorGGJ;
}
//Matrix Sparse, Three Diagonal Non-Zero Elements
double MatrixSpa[9][9];
double(*(Sparse)(int Dimension, double FirstElement, double SecondElement, double ThirdElement))[9]
{
	MatrixSpa[1][1] = SecondElement;
	MatrixSpa[1][2] = ThirdElement;
	MatrixSpa[Dimension][Dimension - 1] = FirstElement;
	MatrixSpa[Dimension][Dimension] = SecondElement;
	for (int Counter = 2; Counter < Dimension; Counter++)
	{
		MatrixSpa[Counter][Counter - 1] = FirstElement;
		MatrixSpa[Counter][Counter] = SecondElement;
		MatrixSpa[Counter][Counter + 1] = ThirdElement;
	}
	return MatrixSpa;
}