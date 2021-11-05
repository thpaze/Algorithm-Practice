/*

DATE: 2021-11-05
AUTHOR: aspirantP

이 프로그램은 Floyd's Algorithm을 연습하기 위한 프로그램으로,
처음에 num(마디의 갯수)를 입력받고 두번째로 W matrix(인접행렬)을 입력받습니다.
명령인자 'array'일 경우 D matirx(최소 거리 행렬)과 P matrix(경로 행렬)을 출력하고,
명령인자 'path'일 경우 최소거리일 때 지나는 정점의 갯수와 경로를 출력합니다.

*/

#define MAXNUM 300

#include <stdio.h>
#include <string.h>

int num; // 마디(vertex)의 갯수또는 인접행렬(adj)의 크기
int W[MAXNUM + 1][MAXNUM + 1]; // 인접행렬 생성(Weight)
int D[MAXNUM + 1][MAXNUM + 1]; // 최단거리 행렬 생성(Distance)
int P[MAXNUM + 1][MAXNUM + 1]; // 경로 행렬 생성(Path)
int tmp[MAXNUM + 1]; // 최단거리의 경로를 저장하기 위한 행렬
int tmpIdx = 0; // 최단거리 경로 행렬의 주소

void floyd();
void path(int i, int j);
void pathPrint(int i, int j);

int main(int argc, char* argv[]) {
	int count = 0;

	// 인접행렬 입력
	scanf("%d", &num);
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			scanf("%d", &W[i][j]);
		}
	}

	floyd();

	// 명령인자 'array'에 대한 num, D matrix, P matirx 출력
	if (strcmp(argv[1], "array") == 0) {
		printf("%d\n", num);
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				printf("%d", D[i][j]);
			}
			printf("\n");
		}
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				printf("%d", P[i][j]);
			}
			printf("\n");
		}
	}

	// 명령인자 'path'에 대한 최소 이동거리와 해당 경로 출력
	else if (strcmp(argv[1], "path") == 0) {
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				pathPrint(i, j);
				printf("\n");
			}
		}
	}

	return 0;
}

// W matrix를 통해 D matrix와 P matrix를 계산하는 함수
void floyd() {

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			P[i][j] = 0;
		}
	}
	
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			D[i][j] = W[i][j];
		}
	}
	for (int k = 0; k < num; k++) {
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				if (D[i][k] + D[k][j] < D[i][j]) {
					P[i][j] = k + 1;
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}

}

void path(int i, int j) {
	if (P[i][j] != 0) {
		path(i, P[i][j] - 1);
		tmp[tmpIdx++] = P[i][j];
		path(P[i][j] - 1, j);
	}
}

// 최단 경로의 정점의 갯수와 각 경로를 출력하는 함수
// 입력: i과 j는 인접행렬의 행과 열의 주소이다.
void pathPrint(int i, int j) {
	path(i, j);

	printf("%d ", tmpIdx); // 최소 경로의 정점 개수 출력

	// 최소 경로 출력
	for (int i = 0; i < tmpIdx; i++) {
		printf("%d ", tmp[i]);
	}
	tmpIdx = 0;
}
