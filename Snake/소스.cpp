#include "Manager.h"

/*
시작일자 20'01.12
완성일자 20'01.14
수정일자 20'06.29~20'06.30
내역:
 코딩 스탠다드 적용
 참고 문서: https://docs.popekim.com/ko/coding-standards/cpp
 파일 분할
 코드 개선
made.SkyLakeARIS
*/
int main()
{
    system("mode con:cols=60 lines=30");

    Manager Game;
    Game.Run();

    gotoxy(9, 20);
    std::cout << "종료하려면 아무키나 누르세요.";
    _getch();
    return 0;
}