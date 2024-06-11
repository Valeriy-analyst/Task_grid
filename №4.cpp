// myvers.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>


int countSolution(int P, int N) {							   //Подсчёт числа К- Возможных решений при которых расставлено максимальное количество точек P=2*N
	int K = 0;
	if (P == 2 * N) {
		++K;
	}
	return K;
}

int countPoint(const std::vector<std::vector<bool>>& grid, int N) {	//Подсчёт числа P- Всего расставленных точек в узлах сетки
	int P = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (grid.at(i).at(j) == true) {
				++P;
			}
		}
	}
	return P;
}

void printGrid(const std::vector<std::vector<bool>>& grid, int N) {//Вывод сетки grid по точкам, 1- точка есть, 0-точки нет
	for (int ic = 0; ic < N; ++ic) {
		for (int jc = 0; jc < N; ++jc) {
			std::cout << grid.at(ic).at(jc) << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

std::vector<std::vector<bool>> calculate(int N, int i0, int j0) {//Метод расставления точек и дальнейшего перебора
	std::vector<std::vector <bool>> grid(N, std::vector <bool>(N));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (i == i0 && j == j0 || grid.at(i0).at(j0) == true) {
				continue;
			}

			bool flag = true;
			for (int i2 = 0; i2 < N; ++i2) {
				for (int j2 = 0; j2 < N; ++j2) {
					if (grid.at(i2).at(j2) == true) {
						int ii = (i - i2);
						int jj = (j - j2);
						int count = 0;
						if (ii == 0) {							//Условие для горизонтальных прямых
							for (int j3 = 0; j3 < N; j3++) {
								if (grid.at(i2).at(j3) == true) {
									++count;
									if (count == 2) {
										flag = false;
									}
								}
							}
						}
						if (jj == 0) {							//Условие для вертикальных прямых
							for (int i3 = 0; i3 < N; i3++) {
								if (grid.at(i3).at(j2) == true) {
									++count;
									if (count == 2) {
										flag = false;
									}
								}
							}
						}
						else {
							for (int x = 0; x < N; ++x) {
								for (int y = 0; y < N; ++y) {
									if (grid.at(x).at(y) == false || x == i2 && y == j2) {
										continue;				//Проверка наличия точки в узле и того что она не находится в одной точке
									}							//с другой проверяемой точкой
									if (y - j == 0) {			//Проверка условия что точки не стоят в одном столбце
										continue;
									}
									if ((x - static_cast<float>(i)) / (y - static_cast<float>(j)) == (i2 - static_cast<float>(i)) / (j2 - static_cast<float>(j))) {
										flag = false;           //Проверятся равенство уравнения прямой проходящей через 2 заданные точки 
									}							//Если равенство выполняется, значит точку ставить нельзя
								}
							}
						}
					}
				}
			}
			if (flag) {
				grid.at(i).at(j) = true;						//Если нет условий не позволяющих выставить точку то она выставляется
			}
		}
	}
	printGrid(grid, N);
	std::cout << std::endl;
	int P = countPoint(grid, N);
	int K = countSolution(P, N);
	std::cout << std::endl << "P=" << P << std::endl;
	std::cout << std::endl << "K=" << K << std::endl;
	return grid;

}



int main()
{
	int N;
	std::cout << "print NxN" << std::endl;
	std::cin >> N;
	std::vector<std::vector <bool>> grid(N, std::vector <bool>(N));
	grid = calculate(N, 0, N - 1);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (grid.at(i).at(j) == true) {
				grid.at(i).at(j) = false;
				calculate(N, i, j);
			}
		}
	}


}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > +"Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
