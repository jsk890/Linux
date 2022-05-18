#include <stdio.h> /* ǥ�� ����� ��� */
#include <unistd.h>

static int g_var = 1; // data ������ �ʱ�ȭ�� ����
char str[] = "PID";

int main(int argc, char** argv)
{
	int var; // stack ������ ���� ����
	pid_t pid;

	var = 92;

	if ((pid = fork()) < 0) { // fork() �Լ��� ���� �� ó��
		perror("[ERROR]: fork()");
	}
	else if (pid == 0) { // �ڽ� ���μ����� ���� ó��
		g_var++; // ������ �� ����
		var++;
		printf("Parent %s from child Process(%d) : %d\n", str, getpid(), getppid());
	}
	else { // �θ� ���μ����� ���� ó��
		printf("Child %s from Parent Process(%d) : %d\n", str, getpid(), pid);
		sleep(1);
	}
	//������ ������ ���
	printf("pid = %d, Global var = %d, var = %d\n", getpid(), g_var, var);

	return 0;
}
