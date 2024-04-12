#define _CRT_SECURE_NO_WARNINGS

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "libraries/TV.h"

#define N 10

ssize_t writeToFile(int file, const void* value, size_t size){
    int cnt = write(file, value, size);
    //printf("Write %d bytes\n", cnt);
    return cnt;
}
//1 Задание
int func1(char pathname[]){
    int fd = open(pathname, O_WRONLY | O_CREAT | O_APPEND, S_IWRITE);
    if (fd == -1){ 
        printf("The file1 was not opened!");
        return -1;
    }
    close(fd);
    return 0;
}
//2 Задание
int func2(char pathname[]){
    int fd = open(pathname, O_CREAT | O_WRONLY, S_IRWXU);
    if(fd == -1) {
        printf("The file2 was not opened!");
        return -1;
    }
    int cnt;

    char c = 'A';
    cnt = writeToFile(fd, &c, sizeof(c));

    char ac[N] = "Big house";
    cnt = writeToFile(fd, ac, sizeof(ac));

    short s = __INT16_MAX__;
    cnt = writeToFile(fd, &s, sizeof(s));

    int i = __INT_MAX__;
    cnt = writeToFile(fd, &i, sizeof(i));
    
    int ai[N] = {0,1,2,3,4,5,6,7,8,9};
    cnt = writeToFile(fd, ai, sizeof(ai));

    float f = 3.14;
    cnt = writeToFile(fd, &f, sizeof(f));
    
    double d = 2.7182818284590;
    cnt = writeToFile(fd, &d, sizeof(d));

    close(fd);
    return 0;
}
//3 Задание
int func3(char pathname[]){
    int fd = open(pathname, O_RDONLY, S_IRWXU);

    int cnt;
    char c;
    cnt = read(fd, &c, sizeof(c));
    printf("Read %d bytes, value = %c\n",cnt, c);

    char ac[N];
    cnt = read(fd, &ac, sizeof(ac));
    printf("Read %d bytes, value = %s\n",cnt, ac);
    
    short s;
    cnt = read(fd, &s, sizeof(s));
    printf("Read %d bytes, value = %d\n",cnt, s);

    int i;
    cnt = read(fd, &i, sizeof(i));
    printf("Read %d bytes, value = %d\n",cnt, i);

    int ai[N];
    cnt = read(fd, &ai, sizeof(ai));
    printf("Read %d bytes, values = ", cnt);
    for (size_t i = 0; i < N; i++)
    {
        printf("%d ", ai[i]);
    }
    
    float f;
    cnt = read(fd, &f, sizeof(f));
    printf("\nRead %d bytes, value = %.2f\n", cnt, f);

    double d;
    cnt = read(fd, &d, sizeof(d));
    printf("Read %d bytes, value = %.13f\n", cnt, d);

    close(fd);    
    return 0;
}
//4 Задание
int func4(char pathname[]){
    int fd = open(pathname, O_RDWR, S_IRWXU);
    int cnt;
    lseek(fd, sizeof(char), SEEK_CUR);

    char ac[N];
    cnt = read(fd, &ac, sizeof(ac));
    printf("Read %d bytes, value = %s\n",cnt, ac);

    lseek(fd, sizeof(short), SEEK_CUR);

    int i;
    cnt = read(fd, &i, sizeof(i));
    printf("Read %d bytes, value = %d\n",cnt, i);
    
    lseek(fd, (sizeof(int)*N)+sizeof(float), SEEK_CUR);

    double d;
    cnt = read(fd, &d, sizeof(d));
    printf("Read %d bytes, value = %.13f\n", cnt, d);

    lseek(fd, sizeof(char) + 2*sizeof(char), SEEK_SET);

    char c = 't';
    cnt = write(fd, &c, sizeof(char));
    
    lseek(fd, sizeof(char) + sizeof(char)*N + sizeof(short) + 
    sizeof(int) + sizeof(int)*N, SEEK_SET);

    float f = 9.8;
    cnt = write(fd, &f, sizeof(f));

    char newac[N];
    lseek(fd, sizeof(char), SEEK_SET);
    cnt = read(fd, ac, sizeof(ac));
    for (size_t i = 0; i < N-1; i++)
    {
        newac[i] = ac[N-i-2];
    }
    newac[N-1] = '\0';

    lseek(fd, sizeof(char), SEEK_SET);
    cnt = write(fd, &newac, sizeof(newac));
    
    lseek(fd, sizeof(char), SEEK_SET);
    cnt = read(fd, &newac, sizeof(newac));
    printf("%s\n", newac);

    close(fd);
    return 0;
}
//5 Задание
int func5(char pathname[]){
    TV tv[N];
    for (size_t i = 0; i < N; i++)
    {
        Init(&tv[i]);
    }

    int fd = open(pathname, O_WRONLY, S_IRWXU);
    int cnt;
    cnt = write(fd, &tv, sizeof(tv));
    close(fd);
    
    TV tv1[N/2];
    fd = open(pathname, O_RDONLY, S_IRWXU);
    for (size_t i = 0; i < N/2; i++)
    {
        lseek(fd, sizeof(TV), SEEK_CUR);
        cnt = read(fd, &tv1[i], sizeof(TV));  
    }
    
    PrintTV(&tv1[2]);
    close(fd);

    return 0;
}

int main() {
    char pathname[] = "file.bin";
    int result = func1(pathname);
    if(result == -1)
        return -1;

    char pathname2[] = "file2.bin";
    result = func2(pathname2);
    if(result == -1)
        return -1;

    //result = func3(pathname2);
    result = func4(pathname2);

    result = func5(pathname2);
    return 0;
}