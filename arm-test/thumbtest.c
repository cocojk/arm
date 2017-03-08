
void test ()
{
    int loop = 0; int sum = 0; 
    for (loop = 0; loop < 10; loop++)
    {
        sum = sum + loop;
        printf("%d\n",sum);
        if (sum > loop)
            break;
    }

    return;
}

