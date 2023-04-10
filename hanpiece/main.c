#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Player {
	int hp;
	int atk;
	int is_sand;
	int energy;
}Player;

int RandomNumber(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}

int luffy_turn(Player* luffy, Player* crocodile) {
	int action;

	printf("==========루피 차례==========\n");
	while (1) {
		printf("1. 공격 !\n2. 기 모으기\n=========================\n");
		printf("\n루피가 할 행동을 선택하세요(1 or 2) >>>> ");
		if (scanf("%d", &action) != 1 || (action != 1 && action != 2)) { // 입력값 예외 처리
			printf("\n");
			while (getchar() != '\n'); // 입력 버퍼 비우기
			printf("잘못된 입력입니다. 다시 입력하세요.\n");
			continue;
		}
		break;
	}
	int n = 2;

	switch (action) {
	case 1: // 크로커다일이 모래로 변신한 상태일때는 루피 공격력의 절반만큼 데미지를 입힌다.
		printf("\n루피의 공격 : '고무고무 총!'\n");
		if (crocodile->is_sand == 1) {
			printf("크로커다일: %d - %d = %d\n", crocodile->hp, luffy->atk / 2, crocodile->hp - luffy->atk / 2);
			crocodile->hp -= luffy->atk / 2;
			printf("Crocodile  HP: %d _크로커다일의 방어로 데미지가 반감됩니다.\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
			if (luffy->energy == 1) {
				luffy->energy = 0;
				break;
			}

		}
		//그게 아니라면 크로커다일 체력-루피 공격력
		else {
			crocodile->hp -= luffy->atk;
			if (luffy->energy == 1) {
				luffy->energy = 0;
				break;
			}
		}
		break;
	case 2:
		luffy->energy += 1;
		luffy->atk *= 2;
		printf("\n루피가 기를 모으고 있습니다.....\n");
		printf("루피 atk : %d, %d배\n", luffy->atk, (int)pow(2, luffy->energy));
		break;
	}
	
}

int crocodile_turn(Player* luffy, Player* crocodile) {
	int action;
	//모래로 변신한 크로커다일은 다음턴에 다시 모래로 변신할 수 없으며
	//모래로 변신한 상태를 기본상태로 바꿔준다.
	if (crocodile->is_sand == 1) {
		action = RandomNumber(1, 2) * 2 - 1; // 1 또는 2가 나오면 1, 3이 나오면 2
		crocodile->is_sand = 0;
	}
	//랜덤으로 행동 1~3 중 생성
	else {
		action = RandomNumber(1, 3);
	}
	
	printf("\n==========크로커다일 차례==========\n");
	switch (action) {
	case 1:
		printf("크로커다일의 공격: '사막의 폭풍!'\n\n");
		luffy->hp -= crocodile->atk;
		break;
	case 2:
		//크로커다일이 모래로 변신하면 is_sand=1
		printf("크로커다일이 몸을 모래로 바꿉니다.'\n\n");
		crocodile->is_sand = 1;
		break;
	case 3:
		printf("크로커다일은 여유를 부립니다:'니가 칠무해가 뭔지 알어?!'\n\n");
		break;
	} 
}

int game(int turn, Player* luffy, Player* crocodile) {
	while (1) {
		//turn == 1 루피 일때
		if (turn == 1) {
			//루피 턴 함수 실행
			luffy_turn(luffy, crocodile);
			if (luffy->energy > 0) {
				//크로커다일이 모래로 변신했을 때
				if (crocodile->is_sand == 1) {
					printf("Luffy      HP: %d, 기 %d배\n", (luffy->hp < 0 ? 0 : luffy->hp), (int)pow(2, luffy->energy));
				}
				else {
					printf("Luffy      HP: %d\n", (luffy->hp < 0 ? 0 : luffy->hp));
					printf("Crocodile  HP: %d\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
				}
				//크로커다일 turn으로 바뀜
				turn = 2;
			}
			// turn ==2 크로커다일 일때
			else if (turn == 2) {
				//크로커다일 턴 함수 실행
				crocodile_turn(luffy, crocodile);
				//크로커다일이 모래로 변신했을때
				if (crocodile->is_sand == 1) {
					printf("Luffy      HP: %d\n", (luffy->hp < 0 ? 0 : luffy->hp));
					printf("Crocodile  HP: %d, 모래로 변신\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
				}
				else {
					printf("Luffy      HP: %d\n", (luffy->hp < 0 ? 0 : luffy->hp));
					printf("Crocodile  HP: %d\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
				}
				//루피 turn으로 바뀜
				turn = 1;
			}
		}
		
		// 한 명의 체력이 0보다 작은 경우
		if (luffy->hp <= 0 || crocodile->hp <= 0) {
			printf("게임이 종료되었습니다.\n");

			// 승패 출력
			if (luffy->hp <= 0 && crocodile->hp <= 0) {
				printf("무승부입니다!\n");
			}
			else if (luffy->hp <= 0) {
				printf("루피가 패했습니다!\n");
				printf("크로커다일이 승리했습니다!\n");
			}
			else if (crocodile->hp <= 0) {
				printf("루피가 승리했습니다!\n");
				printf("크로커다일이 패했습니다!\n");
			}
			return 0;
		}
	}
}


int main(void) {
	//intro
	printf("==========한피스 시작==========\n");
	printf("해적왕이 될 사나이 루피는 \n고잉 메리호를 타고 길을 떠난다.\n\n바다를 떠돌던 중\n칠무해 크로커다일을 만나 전투가 벌어지는데...\n강적을 만난 루피!\n과연 이길 수 있을 것인가?\n두둥!\n\n");

	//시작 Enter 입력
	printf("Press <Enter> to continue...\n\n");
	while (getchar() != '\n');

	//난수
	srand(time(NULL));

	//플레이어 랜덤 hp,atk 
	Player luffy = { RandomNumber(20, 40), RandomNumber(5,15) };
	Player crocodile = { RandomNumber(30, 50), RandomNumber(15,25) };

	printf("Luffy      HP: %d, 공격력: %d\n", luffy.hp, luffy.atk);
	printf("Crocodile  HP: %d, 공격력: %d\n", crocodile.hp, crocodile.atk);

	//선공 선택
	int turn = 0;  // 1이면 루피 선공, 2이면 크로커다일 선공
	while (turn != 1 && turn != 2) {
		printf("\n선공을 선택하세요 (1: 루피, 2: 크로커다일): ");
		int res = scanf("%d", &turn);
		printf("\n");
		if (res != 1) {  // 정수가 아닌 값을 입력한 경우
			while (getchar() != '\n');  // 버퍼를 비우기 위해 입력된 문자들을 버림
			printf("잘못된 입력입니다. 다시 입력해주세요.\n");
			turn = 0;  // 입력값 초기화
		}
	}
	//게임 실행 함수
	game(turn,&luffy,&crocodile);

	//승패 결정 난 후 게임 재시작 여부 입력받기
	while (1) {
		printf("재시작하시겠습니까? (1: 재시작 / 0: 종료) >>> ");
		int restart;
		if (scanf("%d", &restart) != 1 || (restart != 0 && restart != 1)) { // 입력값 예외 처리
			printf("\n");
			while (getchar() != '\n'); // 입력 버퍼 비우기
			printf("잘못된 입력입니다. 다시 입력하세요.\n");
			continue;
		}
		else if (restart == 1) { // 다시 시작
			luffy.hp = 100;
			crocodile.hp = 100;
			turn = RandomNumber(1, 2);
			printf("게임을 다시 시작합니다.\n");
			main();
		}
		else { // 종료
			printf("게임을 종료합니다.\n");
			exit(0);
		}
	}

	return 0;
}