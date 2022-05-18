#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int system(const char* cmd) // fork(), exec(), watipid() �Լ��� ���
{
	pid_t pid;
	int status;

	if ((pid = fork()) < 0) { // fork() �Լ� ���� �� ������ �߻����� ���� ó��
		status = -1;
	}
	else if (pid == 0) { // �ڽ� ���μ����� ó��
		execl("/bin/sh", "sh", "-c", cmd, (char*)0);
		_exit(127); // execl() �Լ��� ��������
	}
	else { // �θ� ���μ����� ó��
		while (waitpid(pid, &status, 0) < 0) // �ڽ� ���μ����� ���� ���
			if (errno != EINTR) { // waitpid() �Լ����� EINTR�� �ƴ� ����� ó��
				status = -1;
				break;
			}
	}
	return status;
}

int main(int argc, char** argv, char** envp)
{
	while (*envp) // ȯ�� ������ ���
		printf("%s\n", *envp++);

	system("who"); // who ��ƿ��Ƽ ����
	system("nocommand"); // ���������� ����
	system("cal"); // cal ��ƿ��Ƽ ����
	return 0;
}
