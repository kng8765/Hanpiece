/*
	1)  intro (O)
	2)  초기화 (O)
	3)  반복과 행돟 (O)
	4)  행동 후 상태 표시 (O)
	5)  행동-여유부리기 (O)
	6)  행동-공격 (O)
	7)  게임종료 (O)
	8)  행동-모래로변신 (O)
	9)  행동-기모으기 (O)
	10) 행동-기모으기(2) (O)
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Player {
	int hp;
	int atk;
	int state;
	int pre_atk;
	int pre_hp;
}Player;

int RandomNumber(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}

int luffy_turn(Player* luffy, Player* crocodile) {
	int action;
	if (luffy->state == 0) {
		luffy->pre_atk = luffy->atk;
	}
	
	printf("==========루피 차례===========\n");
	while (1) {
		printf("1. 공격 !\n2. 기 모으기\n==============================\n");
		printf("\n루피가 할 행동을 선택하세요(1 or 2) >>>> ");
		if (scanf("%d", &action) != 1 || (action != 1 && action != 2)) { // 입력값 예외 처리
			printf("\n");
			getchar();
			printf("잘못된 입력입니다. 다시 입력하세요.\n=========================\n");
			continue;
		}
		break;
	}

	switch (action) {
	case 1:

		printf("\n루피의 공격 : '고무고무 총!' x %d\n", (int)pow(2, luffy->state));

		crocodile->pre_hp = crocodile->hp;

		if (luffy->state > 0) {
			printf("루피 atk : %d\n\n", luffy->atk);
			if (crocodile->state == 1) {
				crocodile->hp -= luffy->atk / 2;
				printf("크로커다일의 방어로 데미지가 반감됩니다...Damage : %d\n",luffy->atk/2);
				printf("크로커다일 : %d - %d = %d\n\n", crocodile->pre_hp, luffy->atk / 2, (crocodile->hp < 0 ? 0 : crocodile->hp));
				crocodile->state = 0;
			}

			else {
				crocodile->hp -= luffy->atk;
				printf("크로커다일 : %d - %d = %d\n\n", crocodile->pre_hp, luffy->atk, (crocodile->hp < 0 ? 0 : crocodile->hp));
			}

			luffy->state = 0;
			luffy->atk = luffy->pre_atk;
		}

		else {
			if (crocodile->state == 1) {
				crocodile->hp -= luffy->atk / 2;
				printf("크로커다일의 방어로 데미지가 반감됩니다.\n");
				printf("크로커다일 : %d - %d = %d\n\n", crocodile->pre_hp, luffy->atk / 2, (crocodile->hp < 0 ? 0 : crocodile->hp));
				crocodile->state = 0;
			}

			else {
				crocodile->hp -= luffy->atk;
				printf("크로커다일 : %d - %d = %d\n\n", crocodile->pre_hp, luffy->atk, (crocodile->hp < 0 ? 0 : crocodile->hp));
			}
		}	
		break;
			
	case 2:
		printf("\n루피가 기를 모으고 있습니다.....\n");
		luffy->state += 1;
		luffy->atk *= 2;
		printf("루피 atk : %d\n\n", luffy->atk);

		break;
	}
	
}

int crocodile_turn(Player* luffy, Player* crocodile) {
	int action;
	
	//랜덤으로 행동 1~3 중 생성
	
	action = RandomNumber(1, 3);

	crocodile->state = 0;
	
	printf("\n==========크로커다일 차례==========\n");
	switch (action) {
	case 1:
		if (luffy->state > 0) {
			printf("크로커다일의 공격: '사막의 폭풍!'\n\n");
			printf("루피가 데미지를 받아서 루피가 모아둔 기가 흩어집니다.\n");
			luffy->state = 0;
			luffy->atk = luffy->pre_atk;
			printf("루피 atk = %d\n", luffy->atk);
			luffy->pre_hp = luffy->hp;
			luffy->hp -= crocodile->atk;
			printf("루피 : %d - %d = %d\n\n", luffy->pre_hp, crocodile->atk, (luffy->hp < 0 ? 0 : luffy->hp));
		}
		else {
			printf("크로커다일의 공격: '사막의 폭풍!'\n\n");
			luffy->pre_hp = luffy->hp;
			luffy->hp -= crocodile->atk;
			printf("루피 : %d - %d = %d\n\n", luffy->pre_hp, crocodile->atk, (luffy->hp < 0 ? 0 : luffy->hp));
		}
		
		break;

	case 2:
		printf("크로커다일이 몸을 모래로 바꿉니다.'\n\n");
		crocodile->state = 1;
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

			if (luffy->state != 0 && crocodile->state > 0) {
				printf("Luffy      HP: %d, 기 %d배\n", (luffy->hp < 0 ? 0 : luffy->hp), (int)pow(2, luffy->state));
				printf("Crocodile  HP: %d, 모래로 변신\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
			}

			else if (luffy->state != 0) {
				printf("Luffy      HP: %d, 기 %d배\n", (luffy->hp < 0 ? 0 : luffy->hp), (int)pow(2, luffy->state));
				printf("Crocodile  HP: %d\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
			}

			else if (crocodile->state == 1) {
				printf("Luffy      HP: %d\n", (luffy->hp < 0 ? 0 : luffy->hp));
				printf("Crocodile  HP: %d, 모래로 변신\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
			}

			else {
				printf("Luffy      HP: %d, 기 %d배\n", (luffy->hp < 0 ? 0 : luffy->hp), (int)pow(2, luffy->state));
				printf("Crocodile  HP: %d\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
			}

			//크로커다일 turn으로 바뀜
			turn = 2;
		}
		// turn ==2 크로커다일 일때
		else if (turn == 2) {
			//크로커다일 턴 함수 실행
			crocodile_turn(luffy, crocodile);

			
			if (crocodile->state > 0 && luffy->state != 0) {
				printf("Luffy      HP: %d, 기 %d배\n", (luffy->hp < 0 ? 0 : luffy->hp), (int)pow(2, luffy->state));
				printf("Crocodile  HP: %d, 모래로 변신\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
				
			}
			else if (luffy->state > 0) {
				printf("Luffy      HP: %d, 기 %d배\n", (luffy->hp < 0 ? 0 : luffy->hp), (int)pow(2, luffy->state));
				printf("Crocodile  HP: %d\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
				
			}
			else if (crocodile->state == 1) {
				printf("Luffy      HP: %d\n", (luffy->hp < 0 ? 0 : luffy->hp));
				printf("Crocodile  HP: %d, 모래로 변신\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
			}

			else {
				printf("Luffy      HP: %d, 기 %d배\n", (luffy->hp < 0 ? 0 : luffy->hp), (int)pow(2, luffy->state));
				printf("Crocodile  HP: %d\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
			}
			
			//루피 turn으로 바뀜
			turn = 1;
		}
	
		
		// 한 명의 체력이 0보다 작은 경우
		if (luffy->hp <= 0 || crocodile->hp <= 0) {
			printf("\n");
			// 승패 출력
			if (luffy->hp <= 0 && crocodile->hp <= 0) {
				printf("무승부입니다!\n");
			}
			else if (luffy->hp <= 0) {
				printf("칠무해의 벽은 너무 높았다 ㅠㅠ (루피 패)\n");
				
			}
			else if (crocodile->hp <= 0) {
				printf("루피가 크로커다일을 쓰러뜨렸다!! (루피 승)\n");
				
			}
			printf("\n=======================================\n");
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
	getchar();

	//난수
	srand(time(NULL));

	//플레이어 랜덤 hp,atk 
	Player luffy = { RandomNumber(20, 40), RandomNumber(5,15) };
	Player crocodile = { RandomNumber(30, 50), RandomNumber(15,25) };
	printf("==============================\n");
	printf("Luffy      HP: %d, 공격력: %d\n", luffy.hp, luffy.atk);
	printf("Crocodile  HP: %d, 공격력: %d\n", crocodile.hp, crocodile.atk);


	int turn = 1;  //루피 턴

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