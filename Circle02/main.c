#include <unistd.h>
#include <stdio.h>

int main()
{
	printf("%d", write(-1, "dfsd", 5));
}
