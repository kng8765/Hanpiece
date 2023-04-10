#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Player {
	int hp;
	int atk;
	int is_sand;
}Player;

int RandomNumber(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}
int luffy_turn(Player* luffy, Player* crocodile) {
	int action;

	printf("==========���� ����==========\n");
	while (1) {
		printf("1. ���� !\n2. �� ������\n=========================\n");
		printf("\n���ǰ� �� �ൿ�� �����ϼ���(1 or 2) >>>> ");
		if (scanf("%d", &action) != 1 || (action != 1 && action != 2)) { // �Է°� ���� ó��
			printf("\n");
			while (getchar() != '\n'); // �Է� ���� ����
			printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
			continue;
		}
		break;
	}

	switch (action) {
	case 1:
		printf("\n������ ���� : '���� ��!'\n");
		if (crocodile->is_sand == 1) {
			crocodile->hp -= luffy->atk / 2;
		}
		else {
			crocodile->hp -= luffy->atk;
		}
		break;
	case 2:
		printf("\n���ǰ� �⸦ ������ �ֽ��ϴ�.....\n");
		break;
	}
	
}

int crocodile_turn(Player* luffy, Player* crocodile) {
	int action;

	if (crocodile->is_sand == 1) {
		action = RandomNumber(1, 2) * 2 - 1; // 1 �Ǵ� 2�� ������ 1, 3�� ������ 2
		crocodile->is_sand = 0;
	}
	else {
		action = RandomNumber(1, 3);
	}
	
	printf("\n==========ũ��Ŀ���� ����==========\n");
	switch (action) {
	case 1:
		printf("ũ��Ŀ������ ����: '�縷�� ��ǳ!'\n\n");
		luffy->hp -= crocodile->atk;
		break;
	case 2:
	
		printf("ũ��Ŀ������ ���� �𷡷� �ٲߴϴ�.'\n\n");
		crocodile->is_sand = 1;
		break;
	case 3:
		printf("ũ��Ŀ������ ������ �θ��ϴ�:'�ϰ� ĥ���ذ� ���� �˾�?!'\n\n");
		break;
	}
}

int game(int turn, Player* luffy, Player* crocodile) {
	while (1) {
		if (turn == 1) {
			luffy_turn(luffy, crocodile);
			if (crocodile->is_sand == 1) {
				printf("Luffy      HP: %d\n", (luffy->hp < 0 ? 0 : luffy->hp));
				printf("Crocodile  HP: %d _ũ��Ŀ������ ���� �������� �ݰ��˴ϴ�.\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
				//printf("ũ��Ŀ����: %d - %d = %d",)

			}
			else {
				printf("Luffy      HP: %d\n", (luffy->hp < 0 ? 0 : luffy->hp));
				printf("Crocodile  HP: %d\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
			}
			turn = 2;
		}
		else if (turn == 2) {
			crocodile_turn(luffy, crocodile);
			if (crocodile->is_sand == 1) {
				printf("Luffy      HP: %d\n", (luffy->hp < 0 ? 0 : luffy->hp));
				printf("Crocodile  HP: %d, �𷡷� ����\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
			}
			else {
				printf("Luffy      HP: %d\n", (luffy->hp < 0 ? 0 : luffy->hp));
				printf("Crocodile  HP: %d\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
			}
			turn = 1;
		}
		

		// �� ���� ü���� 0���� ���� ���
		if (luffy->hp <= 0 || crocodile->hp <= 0) {
			printf("������ ����Ǿ����ϴ�.\n");

			// ���� ���
			if (luffy->hp <= 0 && crocodile->hp <= 0) {
				printf("���º��Դϴ�!\n");
			}
			else if (luffy->hp <= 0) {
				printf("���ǰ� ���߽��ϴ�!\n");
				printf("ũ��Ŀ������ �¸��߽��ϴ�!\n");
			}
			else if (crocodile->hp <= 0) {
				printf("���ǰ� �¸��߽��ϴ�!\n");
				printf("ũ��Ŀ������ ���߽��ϴ�!\n");
			}
			return 0;
		}
	}
	
}


int main(void) {
	printf("�質��\n");
	printf("==========���ǽ� ����==========\n");
	printf("�������� �� �糪�� ���Ǵ� \n���� �޸�ȣ�� Ÿ�� ���� ������.\n\n�ٴٸ� ������ ��\nĥ���� ũ��Ŀ������ ���� ������ �������µ�...\n������ ���� ����!\n���� �̱� �� ���� ���ΰ�?\n�ε�!\n\n");

	printf("Press <Enter> to continue...\n\n");
	while (getchar() != '\n');

	srand(time(NULL));

	Player luffy = { RandomNumber(20, 40), RandomNumber(5,15) };
	Player crocodile = { RandomNumber(30, 50), RandomNumber(15,25) };

	printf("Luffy      HP: %d, ���ݷ�: %d\n", luffy.hp, luffy.atk);
	printf("Crocodile  HP: %d, ���ݷ�: %d\n", crocodile.hp, crocodile.atk);

	int turn = 0;  // 1�̸� ���� ����, 2�̸� ũ��Ŀ���� ����
	while (turn != 1 && turn != 2) {
		printf("\n������ �����ϼ��� (1: ����, 2: ũ��Ŀ����): ");
		int res = scanf("%d", &turn);
		printf("\n");
		if (res != 1) {  // ������ �ƴ� ���� �Է��� ���
			while (getchar() != '\n');  // ���۸� ���� ���� �Էµ� ���ڵ��� ����
			printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
			turn = 0;  // �Է°� �ʱ�ȭ
		}
	}

	game(turn,&luffy,&crocodile);

	while (1) {
		printf("������Ͻðڽ��ϱ�? (1: ����� / 0: ����) >>> ");
		int restart;
		if (scanf("%d", &restart) != 1 || (restart != 0 && restart != 1)) { // �Է°� ���� ó��
			printf("\n");
			while (getchar() != '\n'); // �Է� ���� ����
			printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
			continue;
		}
		else if (restart == 1) { // �ٽ� ����
			luffy.hp = 100;
			crocodile.hp = 100;
			turn = RandomNumber(1, 2);
			printf("������ �ٽ� �����մϴ�.\n");
			main();
		}
		else { // ����
			printf("������ �����մϴ�.\n");
			exit(0);
		}
	}


	return 0;
}