#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int max(int, int);

int problemFour(int p[], int n, int c)
{
    int r[n + 1];
    for (int i = 0; i < n + 1; i++)
    {
        r[i] = i;
    }

    for (int i = 1; i < n; i++)
    {
        int q = p[i];
        for (int j = 1; j < i - 1; j++)
        {
            q = max(1, p[i] + r[j - i] - c);
        }
        r[i] = q;
    }

    return r[n];
}

double findMedian(int A[], int n)
{
    if (n % 2 == 0)
    {
        return (A[n / 2] + A[n / 2 - 1]) / 2.0;
    }

    return A[n / 2];
}

int max(int a, int b)
{
    if (a < b)
    {
        return b;
    }

    return a;
}

int min(int a, int b)
{
    if (a > b)
    {
        return b;
    }

    return a;
}

double problemThree(int X[], int Y[], int n)
{
    if (n == 1)
    {
        return (X[0] + Y[0]) / 2.0;
    }

    if (n == 2)
    {
        return (max(X[0], Y[0]) + min(X[1], Y[1])) / 2.0;
    }

    int medianOne = findMedian(X, n);
    int medianTwo = findMedian(Y, n);

    if (medianOne == medianTwo)
    {
        return medianOne;
    }

    else if (medianOne < medianTwo)
    {
        if (n % 2 == 0)
        {
            return problemThree(X + n / 2 - 1, Y, n - n / 2 + 1);
        }

        return problemThree(X + n / 2, Y, n - n / 2);
    }

    else
    {
        if (n % 2 == 0)
        {
            return problemThree(Y + n / 2 - 1, X, n - n / 2 + 1);
        }

        return problemThree(Y + n / 2, X, n - n / 2);
    }
}

int randomizedPartition(int A[], int p, int r)
{
    int i = p + rand() % (r - p + 1);
    int x = A[i];

    int temp = A[i];
    A[i] = A[r];
    A[r] = temp;

    i = p - 1;
    for (int j = p; j <= r - 1; j++)
    {
        if (A[j] <= x)
        {
            i++;

            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }

    temp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = temp;

    return i + 1;
}

int randomizedSelect(int A[], int p, int r, int i)
{
    if (p == r)
    {
        return A[p];
    }

    int q = randomizedPartition(A, p, r);
    int k = q - p + 1;

    if (i == k)
    {
        return A[q];
    }

    else if (i < k)
    {
        return randomizedSelect(A, p, q - 1, i);
    }

    else
    {
        return randomizedSelect(A, q + 1, r, i - k);
    }
}

int * problemOne(int A[], int n, int k)
{
    int * kElements = calloc(k, sizeof(int));

    double median = 0;
    if (n % 2 == 1)
    {
        median = randomizedSelect(A, 0, n - 1, (n + 1) / 2);
    }

    else
    {
        median = (randomizedSelect(A, 0, n - 1, n / 2) + randomizedSelect(A, 0, n - 1, n / 2 + 1)) / 2.0;
    }

    printf("%f\n", median);

    double differences[n];
    for (int i = 0; i < n; i++)
    {
        differences[i] = A[i] - median;
    }

    if (k <= n / 2)
    {
        double min = LONG_LONG_MAX;
        int minIndex = -1;
        for (int i = 0; i < n; i++)
        {
            double num = fabs(differences[i]);
            if (num < min)
            {
                min = num;
                minIndex = i;
            }
        }

        kElements[0] = (int)(differences[minIndex] + median);
        differences[minIndex] = n;

        for (int i = 1; i < k; i++)
        {
            min = LONG_LONG_MAX;
            minIndex = -1;
            for (int j = 0; j < n; j++)
            {
                double num = fabs(differences[j]);
                if (num < min)
                {
                    min = num;
                    minIndex = j;
                }
            }

            kElements[i] = (int)(differences[minIndex] + median);
            differences[minIndex] = n;
        }
    }

    else
    {
        for (int i = 0; i < n - k; i++)
        {
            double max = LONG_LONG_MIN;
            int maxIndex = -1;

            for (int j = 0; j < n; j++)
            {
                double num = fabs(differences[j]);
                if (num > max)
                {
                    max = num;
                    maxIndex = j;
                }
            }

            for (int j = maxIndex; j < n; j++)
            {
                differences[j] = differences[j + 1];
            }
            differences[n - 1] = 0;
        }

        for (int i = 0; i < k; i++)
        {
            kElements[i] = (int)(differences[i] + median);
        }
    }

    return kElements;
}

int main()
{
    /// Question 1
    int n = 0, k = 0;
    printf("Enter a value for n\n");
    scanf("%d", &n);
    printf("Enter a value for k\n");
    scanf("%d", &k);

    int A[n];
    printf("Enter the values of A\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }

    int * array = problemOne(A, n, k);

    printf("The k closest elements to the median are: ");
    for (int i = 0; i < k; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n\n");

    /// Question 3
    printf("Enter a value for n\n");
    scanf("%d", &n);

    int X[n], Y[n];
    printf("Enter the values of X\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &X[i]);
    }
    printf("Enter the values of Y\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &Y[i]);
    }

    double median = problemThree(X, Y, n);
    printf("The median of the two arrays is: %f\n\n", median);

    /// Question 4
    int c = 0;
    printf("Enter a value for n\n");
    scanf("%d", &n);
    printf("Enter a value for c\n");
    scanf("%d", &c);

    int p[n];
    printf("Enter the values of p\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i]);
    }

    int revenue = problemFour(p, n, c);
    printf("The optimal value is: %d\n", revenue);

    return 0;
}
