/*
	1)  intro (O)
	2)  �ʱ�ȭ (O)
	3)  �ݺ��� ���� (O)
	4)  �ൿ �� ���� ǥ�� (O)
	5)  �ൿ-�����θ��� (O)
	6)  �ൿ-���� (O)
	7)  �������� (O)
	8)  �ൿ-�𷡷κ��� (O)
	9)  �ൿ-������� (O)
	10) �ൿ-�������(2) (O)
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
	
	printf("==========���� ����===========\n");
	while (1) {
		printf("1. ���� !\n2. �� ������\n==============================\n");
		printf("\n���ǰ� �� �ൿ�� �����ϼ���(1 or 2) >>>> ");
		if (scanf("%d", &action) != 1 || (action != 1 && action != 2)) { // �Է°� ���� ó��
			printf("\n");
			getchar();
			printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n=========================\n");
			continue;
		}
		break;
	}

	switch (action) {
	case 1:

		printf("\n������ ���� : '���� ��!' x %d\n", (int)pow(2, luffy->state));

		crocodile->pre_hp = crocodile->hp;

		if (luffy->state > 0) {
			printf("���� atk : %d\n\n", luffy->atk);
			if (crocodile->state == 1) {
				crocodile->hp -= luffy->atk / 2;
				printf("ũ��Ŀ������ ���� �������� �ݰ��˴ϴ�...Damage : %d\n",luffy->atk/2);
				printf("ũ��Ŀ���� : %d - %d = %d\n\n", crocodile->pre_hp, luffy->atk / 2, (crocodile->hp < 0 ? 0 : crocodile->hp));
				crocodile->state = 0;
			}

			else {
				crocodile->hp -= luffy->atk;
				printf("ũ��Ŀ���� : %d - %d = %d\n\n", crocodile->pre_hp, luffy->atk, (crocodile->hp < 0 ? 0 : crocodile->hp));
			}

			luffy->state = 0;
			luffy->atk = luffy->pre_atk;
		}

		else {
			if (crocodile->state == 1) {
				crocodile->hp -= luffy->atk / 2;
				printf("ũ��Ŀ������ ���� �������� �ݰ��˴ϴ�.\n");
				printf("ũ��Ŀ���� : %d - %d = %d\n\n", crocodile->pre_hp, luffy->atk / 2, (crocodile->hp < 0 ? 0 : crocodile->hp));
				crocodile->state = 0;
			}

			else {
				crocodile->hp -= luffy->atk;
				printf("ũ��Ŀ���� : %d - %d = %d\n\n", crocodile->pre_hp, luffy->atk, (crocodile->hp < 0 ? 0 : crocodile->hp));
			}
		}	
		break;
			
	case 2:
		printf("\n���ǰ� �⸦ ������ �ֽ��ϴ�.....\n");
		luffy->state += 1;
		luffy->atk *= 2;
		printf("���� atk : %d\n\n", luffy->atk);

		break;
	}
	
}

int crocodile_turn(Player* luffy, Player* crocodile) {
	int action;
	
	//�������� �ൿ 1~3 �� ����
	
	action = RandomNumber(1, 3);

	crocodile->state = 0;
	
	printf("\n==========ũ��Ŀ���� ����==========\n");
	switch (action) {
	case 1:
		if (luffy->state > 0) {
			printf("ũ��Ŀ������ ����: '�縷�� ��ǳ!'\n\n");
			printf("���ǰ� �������� �޾Ƽ� ���ǰ� ��Ƶ� �Ⱑ ������ϴ�.\n");
			luffy->state = 0;
			luffy->atk = luffy->pre_atk;
			printf("���� atk = %d\n", luffy->atk);
			luffy->pre_hp = luffy->hp;
			luffy->hp -= crocodile->atk;
			printf("���� : %d - %d = %d\n\n", luffy->pre_hp, crocodile->atk, (luffy->hp < 0 ? 0 : luffy->hp));
		}
		else {
			printf("ũ��Ŀ������ ����: '�縷�� ��ǳ!'\n\n");
			luffy->pre_hp = luffy->hp;
			luffy->hp -= crocodile->atk;
			printf("���� : %d - %d = %d\n\n", luffy->pre_hp, crocodile->atk, (luffy->hp < 0 ? 0 : luffy->hp));
		}
		
		break;

	case 2:
		printf("ũ��Ŀ������ ���� �𷡷� �ٲߴϴ�.'\n\n");
		crocodile->state = 1;
		break;
	case 3:
		printf("ũ��Ŀ������ ������ �θ��ϴ�:'�ϰ� ĥ���ذ� ���� �˾�?!'\n\n");
		break;
	} 
}

int game(int turn, Player* luffy, Player* crocodile) {
	while (1) {
		//turn == 1 ���� �϶�
		if (turn == 1) {
			//���� �� �Լ� ����
			luffy_turn(luffy, crocodile);

			if (luffy->state != 0 && crocodile->state > 0) {
				printf("Luffy      HP: %d, �� %d��\n", (luffy->hp < 0 ? 0 : luffy->hp), (int)pow(2, luffy->state));
				printf("Crocodile  HP: %d, �𷡷� ����\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
			}

			else if (luffy->state != 0) {
				printf("Luffy      HP: %d, �� %d��\n", (luffy->hp < 0 ? 0 : luffy->hp), (int)pow(2, luffy->state));
				printf("Crocodile  HP: %d\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
			}

			else if (crocodile->state == 1) {
				printf("Luffy      HP: %d\n", (luffy->hp < 0 ? 0 : luffy->hp));
				printf("Crocodile  HP: %d, �𷡷� ����\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
			}

			else {
				printf("Luffy      HP: %d, �� %d��\n", (luffy->hp < 0 ? 0 : luffy->hp), (int)pow(2, luffy->state));
				printf("Crocodile  HP: %d\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
			}

			//ũ��Ŀ���� turn���� �ٲ�
			turn = 2;
		}
		// turn ==2 ũ��Ŀ���� �϶�
		else if (turn == 2) {
			//ũ��Ŀ���� �� �Լ� ����
			crocodile_turn(luffy, crocodile);

			
			if (crocodile->state > 0 && luffy->state != 0) {
				printf("Luffy      HP: %d, �� %d��\n", (luffy->hp < 0 ? 0 : luffy->hp), (int)pow(2, luffy->state));
				printf("Crocodile  HP: %d, �𷡷� ����\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
				
			}
			else if (luffy->state > 0) {
				printf("Luffy      HP: %d, �� %d��\n", (luffy->hp < 0 ? 0 : luffy->hp), (int)pow(2, luffy->state));
				printf("Crocodile  HP: %d\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
				
			}
			else if (crocodile->state == 1) {
				printf("Luffy      HP: %d\n", (luffy->hp < 0 ? 0 : luffy->hp));
				printf("Crocodile  HP: %d, �𷡷� ����\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
			}

			else {
				printf("Luffy      HP: %d, �� %d��\n", (luffy->hp < 0 ? 0 : luffy->hp), (int)pow(2, luffy->state));
				printf("Crocodile  HP: %d\n", (crocodile->hp < 0 ? 0 : crocodile->hp));
			}
			
			//���� turn���� �ٲ�
			turn = 1;
		}
	
		
		// �� ���� ü���� 0���� ���� ���
		if (luffy->hp <= 0 || crocodile->hp <= 0) {
			printf("\n");
			// ���� ���
			if (luffy->hp <= 0 && crocodile->hp <= 0) {
				printf("���º��Դϴ�!\n");
			}
			else if (luffy->hp <= 0) {
				printf("ĥ������ ���� �ʹ� ���Ҵ� �Ф� (���� ��)\n");
				
			}
			else if (crocodile->hp <= 0) {
				printf("���ǰ� ũ��Ŀ������ �����߷ȴ�!! (���� ��)\n");
				
			}
			printf("\n=======================================\n");
			return 0;
		}
	}
}


int main(void) {
	//intro
	printf("==========���ǽ� ����==========\n");
	printf("�������� �� �糪�� ���Ǵ� \n���� �޸�ȣ�� Ÿ�� ���� ������.\n\n�ٴٸ� ������ ��\nĥ���� ũ��Ŀ������ ���� ������ �������µ�...\n������ ���� ����!\n���� �̱� �� ���� ���ΰ�?\n�ε�!\n\n");

	//���� Enter �Է�
	printf("Press <Enter> to continue...\n\n");
	getchar();

	//����
	srand(time(NULL));

	//�÷��̾� ���� hp,atk 
	Player luffy = { RandomNumber(20, 40), RandomNumber(5,15) };
	Player crocodile = { RandomNumber(30, 50), RandomNumber(15,25) };
	printf("==============================\n");
	printf("Luffy      HP: %d, ���ݷ�: %d\n", luffy.hp, luffy.atk);
	printf("Crocodile  HP: %d, ���ݷ�: %d\n", crocodile.hp, crocodile.atk);


	int turn = 1;  //���� ��

	//���� ���� �Լ�
	game(turn,&luffy,&crocodile);

	//���� ���� �� �� ���� ����� ���� �Է¹ޱ�
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