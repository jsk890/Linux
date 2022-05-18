#include <stdio.h>
#include <sys/wait.h>
#include <spawn.h>

extern char** environ;

int system(char* cmd) // posix_spawn()�Լ��� ���
{
	pid_t pid;
	int status;

	char* argv[] = { "sh", "-c", cmd, NULL };
	posix_spawn(&pid, "/bin/sh", NULL, NULL, argv, environ);
	waitpid(pid, &status, 0);

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
