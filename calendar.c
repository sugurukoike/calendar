#include <stdio.h>
#include <stdlib.h>

void input();

int zeller_congruence();

void output();

int main()
{
    int year = 0, month = 0;
    int *p_year, *p_month;
    int first_day_of_week;

    p_year = &year;
    p_month = &month;

    /* 年月の入力 */
    input(p_year, p_month);

    /* ツェラーの公式 を用いて入力された年月の一日の曜日を計算 */
    first_day_of_week = zeller_congruence(year, month);

    /* カレンダーの描画 */
    output(year, month, first_day_of_week);

    return 0;
}

void input(int *year, int *month)
{
    char year_str[256], month_str[256];

    printf("年月を入力してください\n");
    printf("年: ");
    scanf("%[0-9]", year_str);
    printf("月: ");
    fflush(stdin);
    scanf("%[0-9]", month_str);

    *year = atoi(year_str);
    *month = atoi(month_str);
}

int zeller_congruence(int year, int month)
{
    int first_day_of_week;
    int year_last_two_digits;
    int gamma;
    int y;

    /* ツェラーの公式 を用いて入力された年月の一日（ついたち）の曜日を計算 */
    /* https://ja.wikipedia.org/wiki/%E3%83%84%E3%82%A7%E3%83%A9%E3%83%BC%E3%81%AE%E5%85%AC%E5%BC%8F */
    if (month == 1)
    {
        year -= 1;
        month = 13;
    }
    else if (month == 2)
    {
        year -= 1;
        month = 14;
    }

    year_last_two_digits = year / 100;

    if (year > 1582)
    {
        gamma = -2 * year_last_two_digits + year_last_two_digits / 4;
    }
    else if (year >= 4 || year <= 1582)
    {
        gamma = -1 * year_last_two_digits + 5;
    }

    y = year % 100;

    first_day_of_week = (1 + (26 * (month + 1) / 10) + y + (y / 4) + gamma) % 7;

    if (first_day_of_week < 0)
    {
        first_day_of_week += 7;
    }

    return first_day_of_week;
}

void output(int year, int month, int first_day_of_week)
{
    int day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int space = 0;
    int cnt = 0;

    /* うるう年の考慮 */
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        day[2] = 29;
    }

    printf("%d年%d月のカレンダー\n", year, month);
    printf(" 日 月 火 水 木 金 土\n");

    /* 一日（ついたち）までの空白がいくつあるか計算 */
    if (first_day_of_week != 0)
    {
        space = first_day_of_week - 1;
    }
    else
    {
        space = 6;
    }
    cnt += space;

    for (int i = 1; i <= space; i++)
    {
        /* 一日（ついたち）までの空白をいい感じに描画 */
        printf("   ");
    }
    for (int i = 1; i <= day[month]; i++)
    {
        /* 一日（ついたち）までの空白も計算に入れて、7日ごとに改行 */
        if (cnt % 7 == 0)
        {
            printf("\n");
        }

        /* カレンダーの見栄えが良くなるように 1~9日 は空白を1つ増やして描画 */
        if (i < 10)
        {
            printf("  %d", i);
        }
        else
        {
            printf(" %d", i);
        }

        cnt += 1;
    }
    printf("\n");
}
